#ifndef ADD_H
#define ADD_H

#include <ready/data_flow_defs.h>
#include <ready/operator.h>
#include <ready/params.h>

class Add : public Operator {
public:
    explicit Add(int id) : Operator(id, OP_ADD, OP_BASIC,"add") {}
    
    static Operator * create(Params params) { 
        return new Add(params.id);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() + Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Addi : public Operator {
public:
    Addi(int id, int constant) : Operator(id, OP_ADD, OP_IMMEDIATE,"addi", constant) {}
    
    static Operator * create(Params params) { 
        return new Addi(params.id,params.constant);
    }
    
    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() + Operator::getConst();
            Operator::setVal(v);
        }
    }
};

#endif //ADD_H
