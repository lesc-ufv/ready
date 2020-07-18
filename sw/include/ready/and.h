#ifndef AND_H
#define AND_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class And : public Operator {
public:
    explicit And(int id) : Operator(id, OP_AND, OP_BASIC,"and") {}
    
    static Operator * create(Params params) { 
        return new And(params.id);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() & Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Andi : public Operator {
public:
    Andi(int id, int constant) : Operator(id, OP_AND, OP_IMMEDIATE,"andi", constant) {}
    
    static Operator * create(Params params) { 
        return new Andi(params.id,params.constant);
    }
    
    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() & Operator::getConst();
            Operator::setVal(v);
        }
    }
};


#endif //AND_H
