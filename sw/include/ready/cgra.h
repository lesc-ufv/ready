#ifndef CGRA_H
#define CGRA_H

#include <map>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <fstream>

#include <ready/cgra_defs.h>
#include <ready/input_stream.h>
#include <ready/output_stream.h>

#include <fdam/acc/acc_management.h>

using namespace std::chrono;
using namespace std;

class Cgra {

private:
    double timeExecCgra;
    long total_clocks;
    double cycleTime;
    
    // key = Input ID, Value = key = ThreadID value =  ( Pointer Data, Size Data)
    std::map<int, std::map<int, std::pair<unsigned char *, size_t >>> input_queue;
    // key = Output ID, Value = key = ThreadID value =  ( Pointer Data, Size Data)
    std::map<int, std::map<int, std::pair<unsigned char *, size_t >>> output_queue;

    cgra_program_t *cgra_program;

    AccManagement *accManagement;

    int intlog(double x, double base);

    bool readProgramFile(const std::string &filePath);

    std::map<int, int> makeListPe(int num_pe, int num_pe_in, int num_pe_out);

    cgra_program_t *makeCopy(cgra_program_t cp);

    void freeProgram(cgra_program_t *cp);

public:
    explicit Cgra();

    ~Cgra();

    bool loadCgraProgram(const std::string &filePath);

    bool loadCgraProgram(cgra_program_t cp);

    bool setCgraProgramInputStreamByOp(InputStream *op);
    
    bool setCgraProgramInputStreamByID(int dataFlowID, int inputStreamID, const void *inputStreamData, size_t size);

    bool
    setCgraProgramInputStreamByName(const std::string &dataFlowName, int inputStreamID, const void *inputStreamData,
                                    size_t size);

    bool setCgraProgramOutputStreamByOp(OutputStream *op);
    
    bool setCgraProgramOutputStreamByID(int dataFlowID, int outputStreamID, void *outputStreamData, size_t size);

    bool
    setCgraProgramOutputStreamByName(const std::string &dataFlowName, int outputStreamID, const void *outputStreamData,
                                     size_t size);

    void syncExecute(long waitTime);

    cgra_program_t *getCgraProgram();

    AccManagement *getAccManagement();

    double getTimeExec();
    
    long getTotalCycles();
    
    double getCycleTime();
};

#endif //CGRA_H
