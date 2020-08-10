//
// Created by lucas on 22/05/19.
//

#ifndef FIR_FIR_H
#define FIR_FIR_H

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
#define TAPS 64


int fir(int idx, unsigned short *coef, int taps);

int fir_openmp(int idx, unsigned short *coef, int taps);

int fir_cgra(int idx, int copies, unsigned short *coef, int taps);

DataFlow *createDataFlow(int id, int copies, unsigned short *coef, int taps);

int main(int argc, char *argv[]);

#endif //FIR_FIR_H
