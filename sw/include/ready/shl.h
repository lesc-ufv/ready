#ifndef SHL_H
#define SHL_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Shl : public Operator {
public:
    explicit Shl(int id) : Operator(id, OP_SHL, OP_BASIC, "shl") {}

    static Operator *create(Params params) {
        return new Shl(params.id);
    }

    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() << Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Shli : public Operator {
public:
    explicit Shli(int id, int constant) : Operator(id, OP_SHL, OP_IMMEDIATE, "shli", constant) {}

    static Operator *create(Params params) {
        return new Shli(params.id, params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() << Operator::getConst();
            Operator::setVal(v);
        }
    }
};


#endif //SHL_H
