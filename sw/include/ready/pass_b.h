#ifndef PASSB_H
#define PASSB_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class PassB : public Operator {
public:
    explicit PassB(int id) : Operator(id, OP_PASS_B, OP_BASIC, "pass_b") {}

    static Operator *create(Params params) {
        return new PassB(params.id);
    }

    void compute() override {
        if (Operator::getSrcB()) {
            auto v = Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class PassBi : public Operator {
public:
    explicit PassBi(int id, int constant) : Operator(id, OP_PASS_B, OP_IMMEDIATE, "pass_bi", constant) {}

    static Operator *create(Params params) {
        return new PassBi(params.id, params.constant);
    }

    void compute() override {
        auto v = Operator::getConst();
        Operator::setVal(v);
    }
};

#endif //PASSB_H
