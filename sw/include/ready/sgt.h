#ifndef SGT_H
#define SGT_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Sgt : public Operator {
public:
    explicit Sgt(int id) : Operator(id, OP_SGT, OP_BASIC, "sgt") {}

    static Operator *create(Params params) {
        return new Sgt(params.id);
    }

    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() > Operator::getSrcB()->getVal() ? 1 : 0;
            Operator::setVal(v);
        }
    }
};

class Sgti : public Operator {
public:
    explicit Sgti(int id, int constant) : Operator(id, OP_SGT, OP_IMMEDIATE, "sgti", constant) {}

    static Operator *create(Params params) {
        return new Sgti(params.id, params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() > Operator::getConst() ? 1 : 0;
            Operator::setVal(v);
        }
    }
};


#endif //SGT_H
