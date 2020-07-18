#ifndef MAX_H
#define MAX_H

#include <ready/data_flow_defs.h>
#include <ready/operator.h>
#include <ready/params.h>

class Max : public Operator {
public:
    explicit Max(int id) : Operator(id, OP_MAX, OP_BASIC, "max") {}

    static Operator *create(Params params) {
        return new Max(params.id);
    }

    void compute() override {
        if (Operator::getSrcA() && Operator::getSrcB()) {
            if (Operator::getSrcA()->getVal() > Operator::getSrcB()->getVal()) {
                auto v = Operator::getSrcA()->getVal();
                Operator::setVal(v);
            } else {
                auto v = Operator::getSrcB()->getVal();
                Operator::setVal(v);
            }
        }
    }
};

class Maxi : public Operator {
public:
    Maxi(int id, int constant) : Operator(id, OP_MAX, OP_IMMEDIATE, "maxi", constant) {}

    static Operator *create(Params params) {
        return new Maxi(params.id, params.constant);
    }

    void compute() override {
        if (Operator::getSrcA()) {
            if (Operator::getSrcA()->getVal() > Operator::getConst()) {
                auto v = Operator::getSrcA()->getVal();
                Operator::setVal(v);
            } else {
                auto v = Operator::getConst();
                Operator::setVal(v);
            }
        }
    }
};


#endif //MAX_H
