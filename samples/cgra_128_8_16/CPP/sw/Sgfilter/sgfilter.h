#ifndef SGFILTER_SGFILTER_H
#define SGFILTER_SGFILTER_H

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include <ready/ready.h>

using namespace std;
using namespace std::chrono;

#define DATA_SIZE (1 << 25)
#define NUM_THREAD (8)
#define SAMPLES (1)

int sgfilter(int idx);

int sgfilter_openmp(int idx);

int sgfilter_cgra(int idx, int copies);

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //SGFILTER_SGFILTER_H
