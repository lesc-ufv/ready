#ifndef SLT_H
#define SLT_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Slt : public Operator {
public:
    explicit Slt(int id) : Operator(id, OP_SLT, OP_BASIC,"slt") {}
    
    static Operator * create(Params params) { 
        return new Slt(params.id);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() < Operator::getSrcB()->getVal() ? 1 : 0;
            Operator::setVal(v);
        }
    }
};

class Slti : public Operator {
public:
    explicit Slti(int id, int constant) : Operator(id, OP_SLT, OP_IMMEDIATE,"slti", constant) {}
    
    static Operator * create(Params params) { 
        return new Slti(params.id,params.constant);
    }
    
    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() < Operator::getConst() ? 1 : 0;
            Operator::setVal(v);
        }
    }
};


#endif //SLT_H
