//
// Created by lucas on 22/05/19.
//

#ifndef CHEBYSHEV_CHEBYSHEV_H
#define CHEBYSHEV_CHEBYSHEV_H

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include <ready/ready.h>

using namespace std;
using namespace std::chrono;

#define DATA_SIZE (1 << 26)
#define NUM_THREAD (8)
#define SAMPLES (10)

int chebyshev(int idx);

int chebyshev_openmp(int idx);

int chebyshev_cgra(int idx, int copies);

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //CHEBYSHEV_CHEBYSHEV_H
