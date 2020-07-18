#ifndef QSPLINE_QSPLINE_H
#define QSPLINE_QSPLINE_H

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include <ready/ready.h>

using namespace std;
using namespace std::chrono;

#define DATA_SIZE (1 << 23)
#define NUM_THREAD (8)
#define SAMPLES (1)

int qspline(int idx);

int qspline_openmp(int idx);

int qspline_cgra(int idx, int copies);

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //QSPLINE_QSPLINE_H
