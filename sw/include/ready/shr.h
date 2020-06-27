//
// Created by lucas on 18/01/19.
//

#ifndef MAIN_SHR_H
#define MAIN_SHR_H


#include <ready/operator.h>
#include <ready/data_flow_defs.h>

class Shr : public Operator {
public:
    explicit Shr(int id) : Operator(id, OP_SHR, OP_BASIC,"shr") {}
};

class Shri : public Operator {
public:
    explicit Shri(int id, int constant) : Operator(id, OP_SHR, OP_IMMEDIATE,"shri", constant) {}
};

#endif //MAIN_SHR_H
