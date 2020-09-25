
#include "device_launch_parameters.h"
#include "CpuGpuMat.h"
#include "KernelGpu.cuh"
#include <math.h>
// #include <stdio.h>

/*
	 __global__ prefix'i vscc tarafindan anlasilmaz ve bu fonksiyonlari nvcc compile edecektir
	 nvcc'in compile edecegi metodlar "KernelGpu.cuh" icerisinde declare edilir ve burada tanimlanmalidir
 */

__global__ void gpuMatrixMult(float* gpuMat1, float* gpuMat2, float* gpuMat3, int m1Rows, int m1Cols, int m2Cols)
{
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	float sum = 0.0;

	// printf("BIY:%d BDY:%d TIY:%d BIX:%d BDX:%d TIX:%d r:%d c:%d \n", blockIdx.y, blockDim.y, threadIdx.y, blockIdx.x, blockDim.x, threadIdx.x, row, col);

	if (row < m1Rows && col < m2Cols) {
		for (int i = 0; i < m1Cols; i++) {

			sum += gpuMat1[row * m1Cols + i] * gpuMat2[i * m2Cols + col];
		}
		/*printf("%f\n", sum);*/
		gpuMat3[row * m2Cols + col] = sum;
	}
}

__global__ void gpuNormAndShift(float* GpuP, int size, float mean, float variance, float epsilon, float beta, float gamma)
{
	int id = blockIdx.x * blockDim.x + threadIdx.x;

	if (id < size) {
		GpuP[id] = (GpuP[id] - mean) / sqrt(variance + epsilon) * gamma + beta;
	}
}

__global__ void gpuReluActivation(float* GpuP, int size)
{
	int id = blockIdx.x * blockDim.x + threadIdx.x;

	if (id < size) {
		GpuP[id] = GpuP[id] > 0 ? GpuP[id] : 0;
	}
}
__global__ void gpuSigmoidActivation(float* GpuP, int size)
{
	int id = blockIdx.x * blockDim.x + threadIdx.x;

	if (id < size) {
		GpuP[id] = (float)(1.0 / (1.0 + exp(-1.0 * (double)GpuP[id])));
	}
}

__global__ void gpuBatchNorm(float* gpuResult, float* gpuBeta, float* gpuGamma, float* gpuMovingMean, float* gpuMovingVar, float epsilon, int size)
{
	int id = blockIdx.x * blockDim.x + threadIdx.x;

	if (id < size) {
		gpuResult[id] = (gpuResult[id] - gpuMovingMean[id]) / sqrt(gpuMovingVar[id] + epsilon) * gpuGamma[id] + gpuBeta[id];
	}
}


/*
	"gpuMatrixMult" fonksiyonunu yalnizca .cu uzantili dosyada cagirabiliriz.
	Sebebi bu fonksiyonlari vscc degil de nvcc in compile etmesini saglamak icindir.
	vscc gpuMatrixMult'e kadar compile eder; gpuMatrixMult fonksiyonunu ise nvcc compile eder ve paralel kosar.
*/

void gpuMatrixMultiplication(CpuGpuMat* Mat1, CpuGpuMat* Mat2, CpuGpuMat* Mat3)
{
	//vscc
	int threadsPerBlock = 32;

	int gridCols = ceil(double(Mat2->Cols) / double(threadsPerBlock));
	int gridRows = ceil(double(Mat1->Rows) / double(threadsPerBlock));

	dim3 gridDim(gridCols, gridRows);
	dim3 blockDim(threadsPerBlock, threadsPerBlock);

	//nvcc
	gpuMatrixMult << < gridDim, blockDim >> > ((float*)Mat1->GpuP, (float*)Mat2->GpuP, (float*)Mat3->GpuP, Mat1->Rows, Mat1->Cols, Mat2->Cols);
}


void gpuNormalizeAndShift(CpuGpuMat* Mat, float mean, float variance, float epsilon, float beta, float gama)
{
	int threadsPerBlock = 32;
	int blocksPerGrid = ceil(double(Mat->Size) / double(threadsPerBlock));

	gpuNormAndShift << < blocksPerGrid, threadsPerBlock >> > ((float*)Mat->GpuP, Mat->Size, mean, variance, epsilon, beta, gama);
}

void gpuRelu(CpuGpuMat* Mat)
{
	int threadsPerBlock = 32;
	int blocksPerGrid = ceil(double(Mat->Size) / double(threadsPerBlock));

	gpuReluActivation << < blocksPerGrid, threadsPerBlock >> > ((float*)Mat->GpuP, Mat->Size);
}

void gpuSigmoid(CpuGpuMat* Mat) {

	int threadsPerBlock = 32;
	int blocksPerGrid = ceil(double(Mat->Size) / double(threadsPerBlock));

	gpuSigmoidActivation << < blocksPerGrid, threadsPerBlock >> > ((float*)Mat->GpuP, Mat->Size);
}

void gpuBatchNormalization(CpuGpuMat* result, CpuGpuMat* beta, CpuGpuMat* gamma, CpuGpuMat* movingMean, CpuGpuMat* movingVariance, float epsilon) {

	int threadsPerBlock = 32;
	int blocksPerGrid = ceil(double(beta->Size) / double(threadsPerBlock));

	gpuBatchNorm << < blocksPerGrid, threadsPerBlock >> > ((float*)result->GpuP, (float*)beta->GpuP, (float*)gamma->GpuP, (float*)movingMean->GpuP, (float*)movingVariance->GpuP, epsilon, beta->Size);
}