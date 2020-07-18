#ifndef OR_H
#define OR_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Or : public Operator {
public:
    explicit Or(int id) : Operator(id, OP_OR, OP_BASIC,"or") {}

    static Operator * create(Params params) { 
        return new Or(params.id);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() | Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Ori : public Operator {
public:
    explicit Ori(int id, int constant) : Operator(id, OP_OR, OP_IMMEDIATE,"ori", constant) {}
    
    static Operator * create(Params params) { 
        return new Ori(params.id,params.constant);
    }
    
    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() | Operator::getConst();
            Operator::setVal(v);
        }
    }
};

#endif //OR_H
