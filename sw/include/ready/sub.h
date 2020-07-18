#ifndef SUB_H
#define SUB_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Sub : public Operator {
public:
    explicit Sub(int id) : Operator(id, OP_SUB, OP_BASIC, "sub") {}

    static Operator *create(Params params) {
        return new Sub(params.id);
    }

    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() - Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Subi : public Operator {
public:
    Subi(int id, int constant) : Operator(id, OP_SUB, OP_IMMEDIATE, "subi", constant) {}

    static Operator *create(Params params) {
        return new Subi(params.id, params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() - Operator::getConst();
            Operator::setVal(v);
        }
    }
};

#endif //SUB_H
