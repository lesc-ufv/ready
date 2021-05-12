#include <ready/data_flow.h>

DataFlow::DataFlow(int id, std::string name) :
        id(id),
        name(std::move(name)),
        num_op_in(0),
        num_op_out(0),
        num_op(0),
        num_level(0) {}

DataFlow::~DataFlow() {
    for(auto op:op_array){
        delete op.second;
    }
    DataFlow::op_array.clear();
    for (auto g:DataFlow::graph) {
        g.second.clear();
    }
    DataFlow::graph.clear();
}

void DataFlow::addOperator(Operator *op) {
    if (op->getDataFlowId() == -1) {
        op->setDataFlowId(DataFlow::id);
        DataFlow::op_array[op->getId()] = op;
        DataFlow::num_op++;
        if (op->getType() == OP_IN) {
            DataFlow::num_op_in++;
            DataFlow::input_op_ids.push_back(op->getId());
        }
        if (op->getType() == OP_OUT) {
            DataFlow::num_op_out++;
            DataFlow::output_op_ids.push_back(op->getId());
        }
    }
}

Operator *DataFlow::removeOperator(int op_id) {
    Operator *r = DataFlow::op_array[op_id];
    DataFlow::op_array.erase(op_id);
    r->setDataFlowId(-1);
    return r;
}

void DataFlow::compute() {

    auto n = DataFlow::getNumLevel();
    int allIsEnd = 0;
    
    while (allIsEnd != DataFlow::getNumOpIn()) {
        allIsEnd = 0;
        for (int i = 0; i <= n; ++i) {
            for (auto item:DataFlow::getOpArray()) {
                auto op = item.second;
                if (op->getLevel() == i) {
                    op->compute();
                    if (op->getType() == OP_IN && op->getIsEnd()) {
                        allIsEnd++;
                    }
                }
            }
            if (allIsEnd == DataFlow::getNumOpIn()) {
                break;
            }
        }
    }
}

const std::map<int, Operator *> &DataFlow::getOpArray() const {
    return op_array;
}

Operator *DataFlow::getOp(int id) {
    if (DataFlow::op_array.find(id) != DataFlow::op_array.end()) {
        return DataFlow::op_array[id];
    }
    return nullptr;
}

void DataFlow::toDOT(std::string fileNamePath) {
    std::ofstream myfile;
    myfile.open(fileNamePath);
    myfile << "digraph " << DataFlow::name << "{" << std::endl;
    for (auto op:DataFlow::op_array) {

        if (op.second->getType() == OP_IN) {
            myfile << " " << op.first << " [ label = input" << op.second->getId() << " ]" << std::endl;
        } else if (op.second->getType() == OP_OUT) {
            myfile << " " << op.first << " [ label = output" << op.second->getId() << " ]" << std::endl;
        } else if (op.second->getType() == OP_IMMEDIATE) {
            myfile << " " << op.first;
            myfile << " [ label = " << op_label[op.second->getOpCode()] << "i";
            myfile << ", VALUE = " << op.second->getConst();
            myfile << "]" << std::endl;
            myfile << " \"" << op.first << "." << op.second->getConst() << "\"[ label = " << op.second->getConst()
                   << " ]" << std::endl;

        } else {
            myfile << " " << op.first << " [ label = " << op_label[op.second->getOpCode()] << "]" << std::endl;
        }

    }
    for (auto op:DataFlow::op_array) {
        if (op.second->getType() == OP_IMMEDIATE) {
            myfile << " \"" << op.first << "." << op.second->getConst() << "\" -> " << op.first << std::endl;
        }
        for (auto op_dst:op.second->getDst()) {
            myfile << " " << op.first << " -> " << op_dst->getId() << std::endl;
        }
    }
    myfile << "}" << std::endl;
    myfile.close();
}

void DataFlow::toJSON(const std::string &fileNamePath) {
    std::ofstream myfile;
    myfile.open(fileNamePath);
    myfile << "[" << std::endl;

    char str_node[] = R"({"data":{"id":%d,"type":"%s","value":%d},"group":"nodes"})";
    char str_edge[] = R"({"data":{"id":%d,"source":%d,"target":%d, "port":%d},"group":"edges"})";

    char buf[256];
    int numEdge = DataFlow::getNumEdges();
    int cnt = 0;
    int max_id = 0;
    int id_edges = 0;
    for (auto item:DataFlow::op_array) {
        cnt++;
        auto op = item.second;
        sprintf(buf, str_node, op->getId(), op->getLabel().c_str(), op->getConst());
        if (op->getId() > max_id) {
            max_id = op->getId();
        }
        myfile << buf << "," << std::endl;
    }
    id_edges = max_id + 1;
    cnt = 0;
    int port;         //src,dst,port
    std::map<std::tuple<int,int,int>,bool> map_port;

    for (auto item:DataFlow::op_array) {
        auto op = item.second;
        for (auto neighbor:op->getDst()) {
            cnt++;
            port = -1;
            if(neighbor->getSrcA()) {
                if (neighbor->getSrcA()->getId() == op->getId()) {
                    auto key = std::tuple<int,int,int>(op->getId(),neighbor->getId(),0);
                    if(map_port.find(key) == map_port.end()){
                        port = 0;
                        map_port[key] = true;
                    }
                }
            }
            if(neighbor->getSrcB() && port == -1) {
                if (neighbor->getSrcB()->getId() == op->getId()) {
                    auto key = std::tuple<int,int,int>(op->getId(),neighbor->getId(),1);
                    if(map_port.find(key) == map_port.end()){
                        port = 1;
                        map_port[key] = true;
                    }
                }
            }
            if(neighbor->getBranchIn()) {
                if (neighbor->getBranchIn()->getId() == op->getId()) {
                    port = 2;
                }
            }
            sprintf(buf, str_edge, id_edges++, op->getId(), neighbor->getId(), port);
            if (cnt < numEdge)
                myfile << buf << "," << std::endl;
            else
                myfile << buf << std::endl;
        }
    }
    myfile << "]";
    myfile.close();
}

void DataFlow::fromJSON(const std::string &fileNamePath) {
    Json::Value df;
    Json::Value map_op;

    const auto str_map_op_length = static_cast<int>(str_map_op.length());

    std::ifstream ifs;
    ifs.open(fileNamePath);

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, ifs, &df, &errs)) {
        std::cout << errs << std::endl;
        return;
    }
    ifs.close();
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(str_map_op.c_str(), str_map_op.c_str() + str_map_op_length, &map_op, &errs)) {
        std::cout << errs << std::endl;
        return;
    }

    for (auto e:df) {
        if (e["group"] == "nodes") {
            int id = e["data"]["id"].asInt();
            std::string label = e["data"]["type"].asString();
            int constant = e["data"]["value"].asInt();
            auto params = Params(id, constant, nullptr, 0);
            auto op = OperatorFactory::Get()->CreateOperator(label, params);
            DataFlow::addOperator(op);
        }
    }
    for (auto e:df) {
        if (e["group"] == "edges") {
            auto src = e["data"]["source"].asInt();
            auto dst = e["data"]["target"].asInt();
            auto port = e["data"]["port"].asInt();
            auto op_src = DataFlow::op_array[src];
            auto op_dst = DataFlow::op_array[dst];
            DataFlow::connect(op_src, op_dst, port);
        }
    }

}

void DataFlow::connect(Operator *src, Operator *dst, int dstPort) {

    DataFlow::addOperator(src);
    DataFlow::addOperator(dst);
    DataFlow::graph[src->getId()].push_back(dst->getId());

    src->getDst().push_back(dst);

    if (dstPort == PORT_A) {
        dst->setSrcA(src);
    } else if (dstPort == PORT_B) {
        dst->setSrcB(src);
    } else if (dstPort == PORT_BRANCH) {
        dst->setBranchIn(src);
    }
    DataFlow::updateOpLevel();
}

void DataFlow::updateOpLevel() {
    std::queue<int> q;
    int parent;
    for (auto op:DataFlow::op_array) {
        if (op.second->getType() == OP_IN) {
            q.push(op.first);
            while (!q.empty()) {
                parent = q.front();
                q.pop();
                for (auto child:DataFlow::graph[parent]) {
                    int lp = DataFlow::op_array[parent]->getLevel();
                    int lc = DataFlow::op_array[child]->getLevel();
                    if (lp >= lc) {
                        DataFlow::op_array[child]->setLevel(lp + 1);
                    }
                    q.push(child);
                }
            }
        }
    }
    for (auto op:DataFlow::op_array) {
        if (op.second->getType() == OP_IN) {
            int level = 0;
            for (auto child:DataFlow::graph[op.first]) {
                if (DataFlow::op_array[child]->getLevel() > level) {
                    level = DataFlow::op_array[child]->getLevel();
                }
            }
            if (level > 0)
                level = level - 1;
            op.second->setLevel(level);
        }
    }
    for (auto op:DataFlow::op_array) {
        if (op.second->getLevel() > DataFlow::num_level) {
            DataFlow::num_level = op.second->getLevel();
        }
    }
}


int DataFlow::getId() const {
    return id;
}

const std::string &DataFlow::getName() const {
    return name;
}

const std::map<int, std::vector<int>> &DataFlow::getGraph() const {
    return graph;
}

int DataFlow::getNumOpIn() const {
    return num_op_in;
}

int DataFlow::getNumOpOut() const {
    return num_op_out;
}

int DataFlow::getNumOp() const {
    return num_op;
}

void DataFlow::setId(int id) {
    DataFlow::id = id;
}

int DataFlow::getNumEdges() const {
    int num_edges = 0;
    for (const auto &v:DataFlow::graph) {
        num_edges += v.second.size();
    }
    return num_edges;
}

int DataFlow::getNumLevel() const {
    return DataFlow::num_level;
}
std::vector<int> &DataFlow::getInputIds(){
    return DataFlow::input_op_ids;
}
    
std::vector<int> &DataFlow::getOutputIds(){
    return DataFlow::output_op_ids;
}
