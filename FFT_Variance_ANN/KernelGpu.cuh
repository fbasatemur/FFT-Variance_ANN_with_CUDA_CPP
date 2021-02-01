#pragma once
#include "CpuGpuMat.h"

#ifdef __cplusplus								// nvcc'in compile edebilmesi icin C dosyasi oldugunu belirt
extern "C"
#endif // __cplusplus

// __global__ prefixli, yani GPU fonksiyonlarini, kullanan fonksiyonlar burada tanimlanir

void gpuMatrixMultiplication(CpuGpuMat* Mat1, CpuGpuMat* Mat2, CpuGpuMat* Mat3, int inStartIndex, int resStartIndex);		
void gpuNormalizeAndShift(CpuGpuMat* Mat, float mean, float variance, float epsilon, float beta, float gama);
void gpuRelu(CpuGpuMat* Mat);
void gpuSigmoid(CpuGpuMat* Mat, int startIndex);
void gpuBatchNormalization(CpuGpuMat* result, CpuGpuMat* beta, CpuGpuMat* gamma, CpuGpuMat* movingMean, CpuGpuMat* movingVariance, float epsilon);