#ifndef BNE_H
#define BNE_H

#include <ready/data_flow_defs.h>
#include <ready/operator.h>
#include <ready/params.h>

class Bne : public Operator {
public:
    explicit Bne(int id) : Operator(id, OP_BNE, OP_BASIC, "bne") {}

    static Operator *create(Params params) {
        return new Bne(params.id);
    }

    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() != Operator::getSrcB()->getVal() ? 1 : 0;
            Operator::setVal(v);
        }
    }

};

class Bnei : public Operator {
public:
    Bnei(int id, int constant) : Operator(id, OP_BNE, OP_IMMEDIATE, "bnei", constant) {}

    static Operator *create(Params params) {
        return new Bnei(params.id, params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() != Operator::getConst() ? 1 : 0;
            Operator::setVal(v);
        }
    }
};

#endif //BNE_H
