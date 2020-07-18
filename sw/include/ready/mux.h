#ifndef MUX_H
#define MUX_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Mux : public Operator {
public:
    explicit Mux(int id) : Operator(id, OP_MUX, OP_BASIC,"mux") {}

    static Operator * create(Params params) { 
        return new Mux(params.id);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB() && Operator::getBranchIn()) {
            auto v = Operator::getBranchIn()->getVal() ? Operator::getSrcA()->getVal()
                                                          : Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }   
};

class Muxi : public Operator {
public:
    Muxi(int id, int constant) : Operator(id, OP_MUX, OP_IMMEDIATE, "muxi", constant) {}

    static Operator * create(Params params) { 
        return new Muxi(params.id,params.constant);
    }
    
    void compute() override {
        if (Operator::getSrcA() && Operator::getBranchIn()) {
            auto v = Operator::getBranchIn()->getVal() ? Operator::getSrcA()->getVal() : Operator::getConst();
            Operator::setVal(v);
        }
    }
};

#endif //MAIN_MUX_H
