#ifndef CGRASCHEDULER_DATAFLOW_H
#define CGRASCHEDULER_DATAFLOW_H

#include <queue>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>

#include <ready/data_flow_defs.h>
#include <ready/cgra_arch_defs.h>
#include <ready/operator.h>
#include <ready/operator_factory.h>
#include <ready/params.h>


class DataFlow {

private:
    int id;
    std::string name;
    std::map<int, Operator *> op_array;
    std::map<int, std::vector<int>> graph;
    int num_op_in;
    int num_op_out;
    int num_op;
    int num_level;

    void addOperator(Operator *op);

public:

    explicit DataFlow(int id, std::string name);

    ~DataFlow();

    Operator *removeOperator(int op_id);

    void compute();

    const std::map<int, Operator *> &getOpArray() const;

    Operator *getOp(int id);

    void toDOT(std::string fileNamePath);

    void toJSON(const std::string &fileNamePath);

    void fromJSON(const std::string &fileNamePath);

    void connect(Operator *src, Operator *dst, int dstPort);

    void updateOpLevel();

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    const std::map<int, std::vector<int>> &getGraph() const;

    int getNumOpIn() const;

    int getNumOpOut() const;

    int getNumOp() const;

    int getNumEdges() const;

    int getNumLevel() const;
};


#endif //CGRASCHEDULER_DATAFLOW_H
