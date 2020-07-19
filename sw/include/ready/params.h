#ifndef PARAMS_H
#define PARAMS_H

class Params {
public:
    int id;
    int constant;
    short *data;
    int size;

    explicit Params(int id) : id(id),
                     constant(0),
                     data(nullptr),
                     size(0) {}

    Params(int id, int constant) : id(id),
                                   constant(constant),
                                   data(nullptr),
                                   size(0) {}

    Params(int id, int constant, short *data, int size) : id(id),
                                                        constant(constant),
                                                        data(data),
                                                        size(size) {}

    ~Params() = default;
};

#endif //PARAMS_H
