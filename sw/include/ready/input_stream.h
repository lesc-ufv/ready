#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/cgra_arch_defs.h>
#include <ready/params.h>
#include <iostream>

class InputStream : public Operator {
private:
    int index;
    int *data;
    int size;
 
public:
    explicit InputStream(int id, int *data, int size) : Operator(id, OP_PASS_A, OP_IN,"input"),
                                                        index(0),                                            data(data),
                                                        size(size){}
        
    static Operator * create(Params params) { 
        return new InputStream(params.id,params.data,params.size);
    }
    
    void setData(int *data,int size){
        InputStream::data = data;
        InputStream::size = size;
    }
    
    void reset(){
        InputStream::index = 0;
        Operator::setIsEnd(false);
    }

    void compute() override {
        if(data){
            if (InputStream::index < InputStream::size) {
                auto v = InputStream::data[InputStream::index++];
                Operator::setVal(v);
            } else {
                Operator::setIsEnd(true);
            }
        }
        else{
            Operator::setIsEnd(true);    
        }
    }
};

#endif //INPUTSTREAM_H
