#include <cgra_exec.h>

int main(int argc, char **argv) {
    
    args::ArgumentParser parser("CGRA runtime program.", "");
    
    args::Group group(parser, "All parameters are required:", args::Group::Validators::AllChildGroups);
    
    args::Group group1(parser, "This parameter is only necessary for execution in the cgra:", args::Group::Validators::DontCare);
    
    args::HelpFlag help(group, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<std::string> run(group, "<cpu|cgra>", "Execute the dataflow on CPU or CGRA", {'r',"run"});
    args::ValueFlag<std::string> arch(group1, "JSON CGRA Architecture File", "File that specifies the CGRA architecture", {'a',"arch"});
    args::ValueFlag<std::string> df(group, "DataFlow JSON file", "JSON File specifies the DataFlow Graph", {'d',"dataflow"});
    args::ValueFlag<std::string> input(group, "JSON Input File", "File that specifies the input/output data of dataflow execution", {'i',"in"});
    args::ValueFlag<std::string> output(group, "JSON Output File", "File to write the output data of execution", {'o',"out"});
    
    try{
        parser.ParseCLI(argc, argv);    
    }
    catch (args::Help){
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e){
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e){
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    
    if(args::get(run) == "cpu"){
            exec_dataflow_cpu(args::get(df),args::get(input),args::get(output));
    }else if(args::get(run) == "cgra"){
            if(arch){
                exec_dataflow_cgra(args::get(arch),args::get(df),args::get(input),args::get(output));
            }else{
              std::cout << "Missing the arch parameter!" << std::endl;
              std::cout << parser;
              return 1;
            }
    }else{
           std::cout << "Parameter error: run" << argv[0] << " -h to help!" << std::endl;
    }
  return 0;
}

int exec_dataflow_cpu(std::string &df_file, std::string &input_data_file, std::string &output_data_file) {

    info_t info{};
    info.arch = "cpu";
    info.message = "success";
    info.config_time = 0;
    info.scheduling_time = 0;
    info.exec_time = 0;
    info.clock_cycles = 0;
    info.clock_cgra = 0;
    info.throughput = 0;
    info.approximate_throughput = 0;
    info.total_input_bytes = 0;
    info.total_output_bytes = 0;
    
    auto df = new DataFlow(0, "dataflow");
    df->fromJSON(df_file);

    auto input_map = read_input_data(input_data_file);
    auto output_map = read_output_data(input_data_file);
    double total_input_bytes = 0.0;
    double total_output_bytes = 0.0;

    for (auto dm:*input_map) {
        auto in = reinterpret_cast<InputStream *>(df->getOp(dm.first));
        in->setData(std::get<0>(dm.second), std::get<1>(dm.second));
        total_input_bytes += (double) in->getSize() * sizeof(in->getVal());
    }
    for (auto dm:*output_map) {
        auto out = reinterpret_cast<OutputStream *>(df->getOp(dm.first));
        out->setData(std::get<0>(dm.second), std::get<1>(dm.second));
        total_output_bytes += (double) out->getSize() * sizeof(out->getVal());
    }

    high_resolution_clock::time_point s;
    duration<double> diff{};
    s = high_resolution_clock::now();
    auto num_clock = clock();

    df->compute();

    num_clock = clock()-num_clock;
    diff = high_resolution_clock::now() - s;
    double timeExec  = diff.count();
    
    info.exec_time = timeExec;
    info.throughput = ((total_input_bytes+total_output_bytes)/(1024*1024))/(info.exec_time/1000);
    info.approximate_throughput = info.throughput;
    info.clock_cycles = num_clock;
    info.total_input_bytes = total_input_bytes;
    info.total_output_bytes = total_output_bytes;

    write_output_data(input_data_file, output_data_file, *output_map,info);

    for (auto dm:*input_map) {
        auto ptr = std::get<0>(dm.second);
        delete ptr;
    }
    for (auto dm:*output_map) {
        auto ptr = std::get<0>(dm.second);
        delete ptr;
    }
    delete input_map;
    delete output_map;
    delete df;
    return 0;
}

int exec_dataflow_cgra(std::string &arch_file,std::string &df_file, std::string &input_data_file, std::string &output_data_file) {
    
    auto arch = read_arch_file(arch_file);
    auto cgraArch = new CgraArch(arch);
    auto cgraHw = new Cgra();
    auto config_time = calc_conf_time(cgraHw,arch_file,df_file);    
    info_t info{};
    info.arch = "Real CGRA";
    info.message = "success";
    info.config_time = 0;
    info.scheduling_time = 0;
    info.exec_time = 0;
    info.clock_cycles = 0;
    info.throughput = 0;
    info.approximate_throughput = 0;
    info.total_input_bytes = 0;
    info.total_output_bytes = 0;
    
    Scheduler scheduler(cgraArch);
    std::vector<DataFlow *> dfs;
    int num_thread = cgraArch->getNumThreads();
    double total_input_bytes = 0.0;
    double total_output_bytes = 0.0;
    auto input_map = read_input_data(input_data_file);
    auto output_map = read_output_data(input_data_file);

    for (int i = 0; i < num_thread; ++i) {
        auto df = new DataFlow(i, "dataflow");
        df->fromJSON(df_file);
        dfs.push_back(df);
        scheduler.addDataFlow(df, i, 0);
    }
    int r, tries = 0;
    high_resolution_clock::time_point s;
    duration<double> diff{};
    s = high_resolution_clock::now();
    do {
        r = scheduler.scheduling();
        tries++;
    } while (r != SCHEDULE_SUCCESS && tries < 1000);

    diff = high_resolution_clock::now() - s;
    double scheduling_time  = diff.count();

    if (r == SCHEDULE_SUCCESS) {

        cgraHw->loadCgraProgram(cgraArch->getCgraProgram());

        for (auto dm:*input_map) {
            auto ptr = std::get<0>(dm.second);
            auto size = std::get<1>(dm.second);
            auto size_thread = (size / num_thread);
            auto size_thread_bytes = size_thread * sizeof(ptr[0]);
            for (int i = 0; i < num_thread; ++i) {
                if(i == num_thread-1){
                    size_thread_bytes += (size%num_thread)*sizeof(ptr[0]);
                }
                cgraHw->setCgraProgramInputStreamByID(i, dm.first, &ptr[i * size_thread], size_thread_bytes);
                total_input_bytes += size_thread_bytes;
            }
        }
        for (auto dm:*output_map) {
            auto ptr = std::get<0>(dm.second);
            auto size = std::get<1>(dm.second);
            auto size_thread = (size / num_thread);
            auto size_thread_bytes = size_thread * sizeof(ptr[0]);
            for (int i = 0; i < num_thread; ++i) {
                if(i == num_thread-1){
                    size_thread_bytes += (size%num_thread)*sizeof(ptr[0]);
                }
                cgraHw->setCgraProgramOutputStreamByID(i, dm.first, &ptr[i * size_thread], size_thread_bytes);
                total_output_bytes += size_thread_bytes;
            }
        }
        auto total_mb = (total_input_bytes+total_output_bytes)/(1024.0*1024.0);
        auto exec_time_by_clock = cgraHw->getTotalCycles()*cgraHw->getCycleTime(); 
        auto exec_time_sec = cgraHw->getTimeExec()/1000.0;
        auto is_sim = cgraHw->syncExecute(0);
        info.clock_cgra = 1.0/(cgraHw->getCycleTime()*1000000.0);
        info.scheduling_time = scheduling_time;
        info.clock_cycles = cgraHw->getTotalCycles();
        info.exec_time = cgraHw->getTimeExec();
        info.throughput = total_mb/exec_time_sec;
        info.approximate_throughput = total_mb/exec_time_by_clock;
        info.total_input_bytes = total_input_bytes;
        info.total_output_bytes = total_output_bytes;
        info.config_time = config_time;
        if (is_sim) {
            info.arch = "Simulated CGRA"; 
        }
    }
    info.message = scheduler.getMessageError(r);
    write_output_data(input_data_file, output_data_file, *output_map,info);

    for (auto dm:*input_map) {
        auto ptr = std::get<0>(dm.second);
        delete[]ptr;
    }
    for (auto dm:*output_map) {
        auto ptr = std::get<0>(dm.second);
        delete[]ptr;
    }
    delete cgraArch;
    delete cgraHw;
    delete input_map;
    delete output_map;
    for (auto df:dfs) {
        delete df;
    }
    return 0;
}

arch_t read_arch_file(std::string &arch_file){
    arch_t arch={};
    Json::Value data;
    std::ifstream ifs;
    ifs.open(arch_file);
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &data, &errs)) {
        std::cout << errs << std::endl;
        return arch;
    }
    arch.id = data["id"].asInt();
    arch.num_pe =  data["num_pe"].asInt();
    arch.num_in =  data["num_in"].asInt();
    arch.num_out =  data["num_out"].asInt();
    arch.net_radix =  data["net_radix"].asInt();
    arch.net_extra_stagies =  data["net_extra_stagies"].asInt();
    arch.word_size =  data["word_size"].asInt();

    ifs.close();
    return arch;
}

std::map<int, std::pair<short *, int>> *read_input_data(std::string &data_file) {

    auto data_map = new std::map<int, std::pair<short *, int>>();

    Json::Value data;
    std::ifstream ifs;
    ifs.open(data_file);

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, ifs, &data, &errs)) {
        std::cout << errs << std::endl;
        return data_map;
    }
    for (auto d:data) {
        if (d["type"] == "input") {
            auto size = d["size"].asInt();
            auto in = new short[size];
            auto key = d["id"].asInt();
            auto val = std::pair<short *, int>(in, size);
            data_map->insert(std::pair<int, std::pair<short *, int>>(key, val));
            int idx = 0;
            for (const auto &dd:d["data"]) {
                in[idx++] = dd.asInt();
            }
        }
    }
    ifs.close();
    return data_map;
}

std::map<int, std::pair<short *, int>> *read_output_data(std::string &data_file) {

    auto data_map = new std::map<int, std::pair<short *, int>>();

    Json::Value data;
    std::ifstream ifs;
    ifs.open(data_file);

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, ifs, &data, &errs)) {
        std::cout << errs << std::endl;
        return data_map;
    }

    for (auto d:data) {
        if (d["type"] == "output") {
            auto size = d["size"].asInt();
            auto out = new short[size];
            auto key = d["id"].asInt();
            auto val = std::pair<short *, int>(out, size);
            data_map->insert(std::pair<int, std::pair<short *, int>>(key, val));
        }
    }
    ifs.close();
    return data_map;
}

void write_output_data(std::string &input_data_file, std::string &output_data_file,
                       std::map<int, std::pair<short *, int>> &data_map,const info_t& info) {

    Json::Value data;
    std::ifstream ifs;
    ifs.open(input_data_file);

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, ifs, &data, &errs)) {
        std::cout << errs << std::endl;
        return;
    }
    auto n = data.size();
    for (int i = 0; i < n; ++i) {
        if (data[i]["type"] == "output") {
            auto id = data[i]["id"].asInt();
            auto val = data_map[id];
            auto ptr = val.first;
            auto size = val.second;
            for (int j = 0; j < size; ++j) {
                data[i]["data"].append(Json::Value(ptr[j]));
            }
        }
    }

    std::ostringstream exec_time;
    exec_time << std::fixed << std::setprecision(6);
    exec_time << info.exec_time << "ms";
    std::ostringstream config_time;
    config_time << std::fixed << std::setprecision(6);
    config_time << info.config_time << "ms";
    std::ostringstream scheduling_time;
    scheduling_time << std::fixed<< std::setprecision(6);
    scheduling_time << info.scheduling_time << "ms";
    std::ostringstream throughput;
    throughput << std::fixed<< std::setprecision(6);
    throughput << info.throughput << "MB/s";
    std::ostringstream approximate_throughput;
    approximate_throughput << std::fixed << std::setprecision(6);
    approximate_throughput << info.approximate_throughput << "MB/s";
    std::ostringstream total_input_bytes;
    total_input_bytes << std::fixed << std::setprecision(6);
    total_input_bytes << info.total_input_bytes;
    std::ostringstream total_output_bytes;
    total_output_bytes << std::fixed << std::setprecision(6);
    total_output_bytes << info.total_output_bytes;
    std::ostringstream clock_cgra;
    clock_cgra << std::fixed << std::setprecision(1);
    clock_cgra << info.clock_cgra;
    
    data[n]["type"] = Json::Value("info");
    data[n]["arch"] = Json::Value(info.arch);
    data[n]["message"] = Json::Value(info.message);
    data[n]["exec_time"] = Json::Value(exec_time.str());
    data[n]["config_time"] = Json::Value(config_time.str());
    data[n]["scheduling_time"] = Json::Value(scheduling_time.str());
    data[n]["clock_cycles"] = Json::Value(info.clock_cycles);
    data[n]["throughput"] = Json::Value(throughput.str());
    data[n]["approximate_throughput"] = Json::Value(approximate_throughput.str());
    data[n]["total_input_bytes"] = Json::Value(total_input_bytes.str());
    data[n]["total_output_bytes"] = Json::Value(total_output_bytes.str());
    data[n]["clock_cgra"] = Json::Value(clock_cgra.str());
    

    ifs.close();

    Json::StreamWriterBuilder wbuilder;
    wbuilder["indentation"] = "";
    std::string document = Json::writeString(wbuilder, data);
    std::ofstream ofs;
    ofs.open(output_data_file);
    ofs << document;
    ofs.close();
}
double calc_conf_time(Cgra *cgraHw, std::string &arch_file,std::string &df_file) {

    auto arch = read_arch_file(arch_file);
    auto cgraArch = new CgraArch(arch);
    
    Scheduler scheduler(cgraArch);
    std::vector<DataFlow *> dfs;
    int num_thread = cgraArch->getNumThreads();

    for (int i = 0; i < num_thread; ++i) {
        auto df = new DataFlow(i, "dataflow");
        df->fromJSON(df_file);
        dfs.push_back(df);
        scheduler.addDataFlow(df, i, 0);
    }
    int r, tries = 0;
    do {
        r = scheduler.scheduling();
        tries++;
    } while (r != SCHEDULE_SUCCESS && tries < 100);

    if (r == SCHEDULE_SUCCESS) {

        cgraHw->loadCgraProgram(cgraArch->getCgraProgram());
        auto inputs = dfs[0]->getInputIds();
        auto outputs = dfs[0]->getOutputIds();
        unsigned short a = 0;
        for(auto in : inputs){
             for (int i = 0; i < num_thread; ++i) {
                cgraHw->setCgraProgramInputStreamByID(i, in, &a, 1);
            }
        }
        for(auto out : outputs){
             for (int i = 0; i < num_thread; ++i) {
                 cgraHw->setCgraProgramOutputStreamByID(i, out, &a, 1);
            }
        }
        cgraHw->syncExecute(0);
    }
    
    double time = cgraHw->getTimeExec();
   
    delete cgraArch;
    for (auto df:dfs) {
        delete df;
    }
    return time;
}
