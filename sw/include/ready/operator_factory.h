#ifndef CGRASCHEDULER_OPERATOR_H
#define CGRASCHEDULER_OPERATOR_H

#include <string>
#include <unordered_map>
#include <ready/operator.h>
#include <ready/params.h>
#include <ready/abs.h>
#include <ready/add.h>
#include <ready/and.h>
#include <ready/beq.h>
#include <ready/bne.h>
#include <ready/input_stream.h>
#include <ready/max.h>
#include <ready/min.h>
#include <ready/mult.h>
#include <ready/mux.h>
#include <ready/not.h>
#include <ready/or.h>
#include <ready/output_stream.h>
#include <ready/pass_a.h>
#include <ready/pass_b.h>
#include <ready/sgt.h>
#include <ready/shl.h>
#include <ready/shr.h>
#include <ready/slt.h>
#include <ready/sub.h>
#include <ready/xor.h>

typedef Operator *(*pfnCreate_t)(Params); // function pointer type

class OperatorFactory {
private:
    OperatorFactory();

    OperatorFactory(const OperatorFactory &) {}

    OperatorFactory &operator=(const OperatorFactory &) { return *this; }

    typedef std::unordered_map<std::string, pfnCreate_t> FactoryMap;
    FactoryMap m_FactoryMap;

public:
    ~OperatorFactory() { m_FactoryMap.clear(); }

    static OperatorFactory *Get() {
        static OperatorFactory instance;
        return &instance;
    }

    void Register(const std::string &operatorName, pfnCreate_t pfnCreate);

    Operator *CreateOperator(const std::string &operatorName, Params &params);
};

#endif //CGRASCHEDULER_OPERATOR_H
