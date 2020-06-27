//
// Created by lucas on 18/01/19.
//

#ifndef MAIN_MULT_H
#define MAIN_MULT_H


#include <ready/operator.h>
#include <ready/data_flow_defs.h>

class Mult : public Operator {
public:
    explicit Mult(int id) : Operator(id, OP_MULT, OP_BASIC, "mult") {}
};

class Multi : public Operator {
public:
    Multi(int id, int constant) : Operator(id, OP_MULT, OP_IMMEDIATE, "multi", constant) {}
};


#endif //MAIN_MULT_H
