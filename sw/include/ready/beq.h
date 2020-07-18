#ifndef BEQ_H
#define BEQ_H

#include <ready/data_flow_defs.h>
#include <ready/operator.h>
#include <ready/params.h>

class Beq : public Operator {
public:
    explicit Beq(int id) : Operator(id, OP_BEQ, OP_BASIC,"beq") {}

    static Operator * create(Params params) { 
        return new Beq(params.id);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() == Operator::getSrcB()->getVal() ? 1 : 0;
            Operator::setVal(v);
        }
    }
};

class Beqi : public Operator {
public:
    Beqi(int id, int constant) : Operator(id, OP_BEQ, OP_IMMEDIATE, "beqi", constant) {}

    static Operator * create(Params params) { 
        return new Beqi(params.id,params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() == Operator::getConst() ? 1 : 0;
            Operator::setVal(v);
        }
    }
};

#endif //BEQ_H
