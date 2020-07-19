#include <cgra_exec.h>

int main(int argc, char *argv[]) {

    std::string s1("../cgra_arch.json");
    std::string s2("../chebyshev.json");
    std::string s3("../data.json");
    std::string s4("../data_out_cpu.json");
    std::string s5("../data_out_cgra.json");

    exec_dataflow_cpu(s2, s3, s4);

    //exec_dataflow_cgra(s1,s2, s3,s5);

    return 0;
}

int exec_dataflow_cpu(std::string &df_file, std::string &input_data_file, std::string &output_data_file) {

    auto df = new DataFlow(0, "dataflow");
    df->fromJSON(df_file);

    auto input_map = read_input_data(input_data_file);
    auto output_map = read_output_data(input_data_file);

    for (auto dm:*input_map) {
        auto in = reinterpret_cast<InputStream *>(df->getOp(dm.first));
        in->setData(std::get<0>(dm.second), std::get<1>(dm.second));
    }
    for (auto dm:*output_map) {
        auto out = reinterpret_cast<OutputStream *>(df->getOp(dm.first));
        out->setData(std::get<0>(dm.second), std::get<1>(dm.second));
    }

    df->compute();
    write_output_data(input_data_file, output_data_file, *output_map);

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
    Scheduler scheduler(cgraArch);
    std::vector<DataFlow *> dfs;
    int num_thread = cgraArch->getNumThreads();

    auto input_map = read_input_data(input_data_file);
    auto output_map = read_output_data(input_data_file);

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
            }
        }
    }

    cgraHw->syncExecute(0);

    write_output_data(input_data_file, output_data_file, *output_map);

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
                       std::map<int, std::pair<short *, int>> &data_map) {

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
    ifs.close();

    Json::StreamWriterBuilder wbuilder;
    std::string document = Json::writeString(wbuilder, data);
    std::ofstream ofs;
    ofs.open(output_data_file);
    ofs << document;
    ofs.close();
}

