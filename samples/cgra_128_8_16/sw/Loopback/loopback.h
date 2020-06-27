//
// Created by lucas on 22/05/19.
//

#ifndef LOOPBACK_LOOPBACK_H
#define LOOPBACK_LOOPBACK_H

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include <ready/ready.h>

using namespace std;
using namespace std::chrono;

#define DATA_SIZE (1 << 5)
#define NUM_THREAD (8)
#define SAMPLES (1)

int loopback(int idx);

int loopback_openmp(int idx);

int loopback_cgra(int idx, int copies);

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //LOOPBACK__H
