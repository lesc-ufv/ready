//
// Created by lucas on 18/01/19.
//

#ifndef MAIN_OUTPUTSTREAM_H
#define MAIN_OUTPUTSTREAM_H


#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/cgra_arch_defs.h>

class OutputStream : public Operator {
public:
    explicit OutputStream(int id) : Operator(id, OP_PASS_A, OP_OUT,"output") {}

};


#endif //MAIN_OUTPUTSTREAM_H
