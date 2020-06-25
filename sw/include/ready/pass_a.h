//
// Created by lucas on 18/01/19.
//

#ifndef MAIN_PASSA_H
#define MAIN_PASSA_H


#include <ready/operator.h>
#include <ready/data_flow_defs.h>

class PassA : public Operator {
public:
    explicit PassA(int id) : Operator(id, OP_PASS_A, OP_BASIC) {}
};

#endif //MAIN_PASSA_H
