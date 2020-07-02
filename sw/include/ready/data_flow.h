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
#include <ready/abs.h>
#include <ready/add.h>
#include <ready/and.h>
#include <ready/beq.h>
#include <ready/bne.h>
#include <ready/input_stream.h>
#include <ready/max.h>
#include <ready/min.h>
#include <ready/mult.h>
#include <ready/mux.h>
#include <ready/not.h>
#include <ready/or.h>
#include <ready/output_stream.h>
#include <ready/pass_a.h>
#include <ready/pass_b.h>
#include <ready/sgt.h>
#include <ready/shl.h>
#include <ready/shr.h>
#include <ready/slt.h>
#include <ready/sub.h>
#include <ready/xor.h>


class DataFlow {

private:
    int id;
    std::string name;
    std::map<int, Operator *> op_array;
    std::map<int, std::vector<int>> graph;
    int num_op_in;
    int num_op_out;
    int num_op;

    void addOperator(Operator *op);

public:

    explicit DataFlow(int id, std::string name);

    ~DataFlow();

    Operator *removeOperator(int op_id);

    void compute();

    const std::map<int, Operator *> &getOpArray() const;

    Operator *getOp(int id);

    void toDot(std::string fileNamePath);
    
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
};


#endif //CGRASCHEDULER_DATAFLOW_H
