//
// Created by lucas on 22/05/19.
//

#ifndef POLY5_POLY5_H
#define POLY5_POLY5_H

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

int poly5(int idx);

int poly5_openmp(int idx);

int poly5_cgra(int idx,int copies);

DataFlow *createDataFlow(int id, int copies);

int main(int argc, char *argv[]);

#endif //POLY5_POLY5_H
