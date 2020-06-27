#ifndef PAETH_PAETH_H
#define PAETH_PAETH_H

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include <ready/ready.h>

using namespace std;
using namespace std::chrono;

#define DATA_SIZE (1 << 6)
#define NUM_THREAD (8)
#define SAMPLES (1)

int paeth(int idx);

int paeth_openmp(int idx);

int paeth_cgra(int idx, int copies);

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //PAETH_PAETH_H
