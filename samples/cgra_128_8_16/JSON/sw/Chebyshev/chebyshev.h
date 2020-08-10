#ifndef CHEBYSHEV_H
#define CHEBYSHEV_H

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include <ready/ready.h>

using namespace std;
using namespace std::chrono;

#define DATA_SIZE (1 << 6)
#define NUM_THREAD (1)
#define SAMPLES (1)

int chebyshev(int idx);

int chebyshev_openmp(int idx);

int chebyshev_cgra(int idx, int copies);

void chebyshev_dataflow_cpu();

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //CHEBYSHEV_CHEBYSHEV_H
