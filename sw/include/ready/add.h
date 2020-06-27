//
// Created by lucas on 18/01/19.
//

#ifndef MAIN_ADD_H
#define MAIN_ADD_H


#include <ready/data_flow_defs.h>
#include <ready/operator.h>

class Add : public Operator {
public:
    explicit Add(int id) : Operator(id, OP_ADD, OP_BASIC,"add") {}
};

class Addi : public Operator {
public:
    Addi(int id, int constant) : Operator(id, OP_ADD, OP_IMMEDIATE,"addi", constant) {}
};

#endif //MAIN_ADD_H
