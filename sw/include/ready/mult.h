#ifndef MULT_H
#define MULT_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Mult : public Operator {
public:
    explicit Mult(int id) : Operator(id, OP_MULT, OP_BASIC, "mult") {}

    static Operator * create(Params params) { 
        return new Mult(params.id);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() * Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Multi : public Operator {
public:
    Multi(int id, int constant) : Operator(id, OP_MULT, OP_IMMEDIATE, "multi", constant) {}
    
    static Operator * create(Params params) { 
        return new Multi(params.id,params.constant);
    }
    
    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() * Operator::getConst();
            Operator::setVal(v);
        }
    }
};


#endif //MULT_H
