#ifndef CGRASCHEDULER_SCHELUDER_H
#define CGRASCHEDULER_SCHELUDER_H

#include <queue>
#include <ready/data_flow.h>
#include <ready/cgra_arch.h>
#include <ready/global.h>
#include <ready/scheduler_defs.h>

class Scheduler {

private:
    std::map<int, DataFlow *> dataflows;

    std::map<int, int> dataflow_group;

    std::map<int, std::vector<int>> data_flow_mapping;

    CgraArch *cgraArch;

    int mapAndRoute(int ThreadId);

    int placeAndRoute(std::vector<int> &mapping, int threadID);

public:
    explicit Scheduler(CgraArch *cgra);

    Scheduler();

    ~Scheduler();

    bool addDataFlow(DataFlow *df, int threadID, int groupID);

    void setCgra(CgraArch *cgra);

    CgraArch *getCgra();

    int scheduling();

    void reset();

    std::vector<int> getMapping(int dataFlowId, int threadID);
};


#endif //CGRASCHEDULER_SCHELUDER_H
