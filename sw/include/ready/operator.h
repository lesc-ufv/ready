#ifndef OPERATOR_H
#define OPERATOR_H

#include <vector>
#include <string>
#include <ready/cgra_arch_defs.h>

class Operator {

private:
    int id;
    int level;
    int opCode;
    int type;
    int val;
    int constant;
    Operator *srcA;
    Operator *srcB;
    Operator *branchIn;
    std::vector<Operator *> dst;
    int dataFlowId;
    std::string label;
    bool isEnd;

public:
    Operator(int id, int op_code, int type, std::string label);

    Operator(int id, int op_code, int type, std::string label, int constant);

    ~Operator();

    int getId() const;

    void setId(int id);

    int getOpCode() const;

    void setOpCode(int op_code);

    int getType() const;

    void setType(int type);

    int getVal() const;

    void setVal(int val);

    Operator *getSrcA() const;

    void setSrcA(Operator *srcA);

    Operator *getSrcB() const;

    void setSrcB(Operator *srcB);

    Operator *getBranchIn() const;

    void setBranchIn(Operator *branchIn);

    std::vector<Operator *> &getDst();

    int getConst() const;

    void setConst(int constant);

    void setLevel(int level);

    int getLevel();

    void setDataFlowId(int dataFlowId);

    int getDataFlowId();

    int getPortA();

    int getPortB();

    int getPortBranch();

    const std::string &getLabel() const;

    virtual void compute() = 0;

    int getIsEnd() const;

    void setIsEnd(bool isEnd);
};

#endif //OPERATOR_H
