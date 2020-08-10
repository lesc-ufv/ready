#ifndef POLY8_POLY8_H
#define POLY8_POLY8_H

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

int poly8(int idx);

int poly8_openmp(int idx);

int poly8_cgra(int idx, int copies);

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //POLY8_POLY8_H
