#include <ready/data_flow.h>


DataFlow::DataFlow(int id, std::string name) : id(id), name(std::move(name)), num_op_in(0), num_op_out(0), num_op(0) {}

DataFlow::~DataFlow() {
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
        }
        if (op->getType() == OP_OUT) {
            DataFlow::num_op_out++;
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

void DataFlow::toDot(std::string fileNamePath) {
    std::ofstream myfile;
    myfile.open(fileNamePath);
    myfile << "digraph " << DataFlow::name << "{" << std::endl;
    for (auto op:DataFlow::op_array) {
        if (op.second->getType() == OP_IN) {
            myfile << " " << op.first << " [ label = IN" << op.second->getId() << " ]" << std::endl;
        } else if (op.second->getType() == OP_OUT) {
            myfile << " " << op.first << " [ label = OUT" << op.second->getId() << " ]" << std::endl;
        } else if (op.second->getType() == OP_IMMEDIATE) {
            myfile << " " << op.first;
            myfile << " [ label = " << op_label[op.second->getOpCode()] << "i";
            myfile << ", VALUE = " << op.second->getConstant();
            myfile << "]" << std::endl;
            myfile << " \"" << op.first << "." << op.second->getConstant() << "\"[ label = " << op.second->getConstant()
                   << " ]" << std::endl;

        } else {
            myfile << " " << op.first << " [ label = " << op_label[op.second->getOpCode()] << "]" << std::endl;
        }

    }
    for (auto op:DataFlow::op_array) {
        if (op.second->getType() == OP_IMMEDIATE) {
            myfile << " \"" << op.first << "." << op.second->getConstant() << "\" -> " << op.first << std::endl;
        }
        for (auto op_dst:op.second->getDst()) {
            myfile << " " << op.first << " -> " << op_dst << std::endl;
        }
    }
    myfile << "}" << std::endl;
    myfile.close();
}

void DataFlow::toJSON(const std::string &fileNamePath) {
        std::ofstream myfile;
        myfile.open(fileNamePath);
        myfile << "[" << std::endl;
        
        char str_node_sub[] = R"({"data":{"id":"%d","op1":"%d","op2":"%d","type":"sub"},"group":"nodes"})";
        char str_node[] = R"({"data":{"id":"%d","type":"%s"},"group":"nodes"})";
        char str_edge[] = R"({"data":{"id":"%d","source":"%d","target":"%d"},"group":"edges"})";
        
        char buf[256];
        int numOp = DataFlow::getNumOp();
        int numEdge = DataFlow::getNumEdges();
        int cnt = 0;
        int max_id = 0;
        int id_edges = 0;
        for (auto item:DataFlow::op_array) {
            cnt++;
            auto op = item.second;
            if(op->getLabel() == "sub"){
                 sprintf(buf, str_node_sub, op->getId(),op->getSrcA(),op->getSrcB(), op->getLabel().c_str());
            }else{
                sprintf(buf, str_node, op->getId(), op->getLabel().c_str()); 
            }
            if (op->getId() > max_id) {
                max_id = op->getId();
            }
            myfile << buf << "," << std::endl;
        }
        id_edges = max_id + 1;
        cnt = 0;
        for (auto item:DataFlow::op_array) {
            auto op = item.second;
            for (auto neighbor:op->getDst()) {
                cnt++;
                sprintf(buf, str_edge, id_edges++, op->getId(), neighbor);
                if (cnt < numEdge)
                    myfile << buf << "," << std::endl;
                else
                    myfile << buf << std::endl;
            }
        }
        myfile << "]";
        myfile.close();
}

void DataFlow::connect(Operator *src, Operator *dst, int dstPort) {

    DataFlow::addOperator(src);
    DataFlow::addOperator(dst);
    DataFlow::graph[src->getId()].push_back(dst->getId());

    src->getDst().push_back(dst->getId());

    if (dstPort == PORT_A) {
        dst->setSrcA(src->getId());
    } else if (dstPort == PORT_B) {
        dst->setSrcB(src->getId());
    } else if (dstPort == PORT_BRANCH) {
        dst->setBranchIn(src->getId());
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
    for(const auto &v:DataFlow::graph){
        num_edges+=v.second.size();
    }
    return num_edges;
}
