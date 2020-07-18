#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

#include <ready/operator.h>
#include <ready/data_flow_defs.h>
#include <ready/cgra_arch_defs.h>
#include <ready/params.h>

class OutputStream : public Operator {
private:
    int index;
    int *data;
    int size;
public:
    explicit OutputStream(int id, int *data, int size) : Operator(id, OP_PASS_A, OP_OUT,"output"),
                                                         index(0),
                                                         data(data),
                                                         size(size){}
    
    static Operator * create(Params params) { 
        return new OutputStream(params.id,params.data,params.size);
    }                                                      
    
    void setData(int *data, int size){
        OutputStream::data = data;
        OutputStream::size = size;
    }
    
    void reset(){
        OutputStream::index = 0;
        Operator::setIsEnd(false);
    }
    
    void compute() override {
        if (Operator::getSrcA()) {
            auto v = Operator::getSrcA()->getVal();
            Operator::setVal(v);
        }
        else if(Operator::getSrcB()) {
            auto v = Operator::getSrcB()->getVal();
            Operator::setVal(v);
        }
        if(data){
            if (OutputStream::index < OutputStream::size) {
                OutputStream::data[OutputStream::index++] = Operator::getVal();
            } else {
                Operator::setIsEnd(true);
            }
        }
        else{
            Operator::setIsEnd(true);    
        }
    }
};


#endif //OUTPUTSTREAM_H
