//
// Created by lucas on 18/01/19.
//

#ifndef MAIN_SLT_H
#define MAIN_SLT_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>

class Slt : public Operator {
public:
    explicit Slt(int id) : Operator(id, OP_SLT, OP_BASIC,"slt") {}
};

class Slti : public Operator {
public:
    explicit Slti(int id, int constant) : Operator(id, OP_SLT, OP_IMMEDIATE,"slti", constant) {}
};


#endif //MAIN_SLT_H
