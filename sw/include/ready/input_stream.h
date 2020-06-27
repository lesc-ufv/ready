//
// Created by lucas on 18/01/19.
//

#ifndef MAIN_INPUTSTREAM_H
#define MAIN_INPUTSTREAM_H


#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/cgra_arch_defs.h>

class InputStream : public Operator {
public:
    explicit InputStream(int id) : Operator(id, OP_PASS_A, OP_IN,"input") {}
};


#endif //MAIN_INPUTSTREAM_H
