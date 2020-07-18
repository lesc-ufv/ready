#ifndef SHR_H
#define SHR_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Shr : public Operator {
public:
    explicit Shr(int id) : Operator(id, OP_SHR, OP_BASIC, "shr") {}

    static Operator *create(Params params) {
        return new Shr(params.id);
    }

    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() >> Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Shri : public Operator {
public:
    explicit Shri(int id, int constant) : Operator(id, OP_SHR, OP_IMMEDIATE, "shri", constant) {}

    static Operator *create(Params params) {
        return new Shri(params.id, params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() >> Operator::getConst();
            Operator::setVal(v);
        }
    }
};

#endif //MAIN_SHR_H
