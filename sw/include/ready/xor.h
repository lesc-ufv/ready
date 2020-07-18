#ifndef XOR_H
#define XOR_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/params.h>

class Xor : public Operator {
public:
    explicit Xor(int id) : Operator(id, OP_XOR, OP_BASIC, "xor") {}

    static Operator *create(Params params) {
        return new Xor(params.id);
    }

    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            auto v = Operator::getSrcA()->getVal() ^Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
    }
};

class Xori : public Operator {
public:
    Xori(int id, int constant) : Operator(id, OP_XOR, OP_IMMEDIATE, "xori", constant) {}

    static Operator *create(Params params) {
        return new Xori(params.id, params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal() ^Operator::getConst();
            Operator::setVal(v);
        }
    }
};

#endif //XOR_H
