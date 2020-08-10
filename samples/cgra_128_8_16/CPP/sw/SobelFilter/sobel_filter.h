#ifndef SOBEL_FILTER_SOBEL_FILTER_H
#define SOBEL_FILTER_SOBEL_FILTER_H

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include <ready/ready.h>

using namespace std;
using namespace std::chrono;

#define DATA_SIZE (16*16)
#define NUM_THREAD (8)
#define SAMPLES (1)
#define SOBEL_OP_SIZE 9
#define pow2(x) (x)*(x)

typedef int byte;

int sobel_filter(int idx);

int sobel_filter_openmp(int idx);

int sobel_filter_cgra(int idx, int copies);

DataFlow *createDataFlow(int id, int copies);

void itConv(byte *buffer, int buffer_size, int width, byte *op, byte *res);

byte convolution(const byte *X, const byte *Y, int c_size);

void makeOpMemCPU(const byte *buffer, int buffer_size, int width, int cindex, byte *op_mem);

void makeOpMemCGRA(const byte *buffer, int buffer_size, int width, short **op_mem);

void contour(const byte *sobel_h, const byte *sobel_v, int gray_size, byte *contour_img);

int main(int argc, char *argv[]);

#endif //SOBEL_FILTER_SOBEL_FILTER_H
