#include <fstream>
#include "KernelGpu.cuh"
#include "BatchNormalization.h"


void BatchNormalization::WeightLoad(CpuGpuMat* weightName, std::string& weightFilename)
{
	float* cpuFloatP = (float*)weightName->CpuP;
	std::ifstream file;
	file.open(weightFilename);
	std::string value;

	for (size_t i = 0; i < weightName->Size; i++) {
		file >> value;
		cpuFloatP[i] = std::stof(value);
	}

	file.close();
}

BatchNormalization::BatchNormalization(int resultRows, int resultCols, bool useBias)
{
	beta.Rows = resultRows;
	beta.Cols = useBias ? resultCols - 1 : resultCols;
	beta.Size = beta.Rows * beta.Cols;

	gamma.Rows = resultRows;
	gamma.Cols = useBias ? resultCols - 1 : resultCols;
	gamma.Size = gamma.Rows * gamma.Cols;

	movingMean.Rows = resultRows;
	movingMean.Cols = useBias ? resultCols - 1 : resultCols;
	movingMean.Size = movingMean.Rows * movingMean.Cols;

	movingVariance.Rows = resultRows;
	movingVariance.Cols = useBias ? resultCols - 1 : resultCols;
	movingVariance.Size = movingVariance.Rows * movingVariance.Cols;


	beta.CpuGpuAlloc();				
	gamma.CpuGpuAlloc();
	movingMean.CpuGpuAlloc();
	movingVariance.CpuGpuAlloc();
}

BatchNormalization::BatchNormalization(CpuGpuMat& result, bool isEndLayer, bool isMemPin)
{
	bool useBias = !isEndLayer;

	beta.Rows = result.Rows;
	beta.Cols = useBias ? result.Cols - 1 : result.Cols;
	beta.Size = beta.Rows * beta.Cols;
	beta.MemPinned = isMemPin;

	gamma.Rows = result.Rows;
	gamma.Cols = useBias ? result.Cols - 1 : result.Cols;
	gamma.Size = gamma.Rows * gamma.Cols;
	gamma.MemPinned = isMemPin;

	movingMean.Rows = result.Rows;
	movingMean.Cols = useBias ? result.Cols - 1 : result.Cols;
	movingMean.Size = movingMean.Rows * movingMean.Cols;
	movingMean.MemPinned = isMemPin;

	movingVariance.Rows = result.Rows;
	movingVariance.Cols = useBias ? result.Cols - 1 : result.Cols;
	movingVariance.Size = movingVariance.Rows * movingVariance.Cols;
	movingVariance.MemPinned = isMemPin;


	beta.CpuGpuAlloc();
	gamma.CpuGpuAlloc();
	movingMean.CpuGpuAlloc();
	movingVariance.CpuGpuAlloc();
}

void BatchNormalization::Load(std::string& betaFilename, std::string& gammaFilename, std::string& movMeanFilename, std::string& movVarFilename)
{
	WeightLoad(&beta, betaFilename);
	WeightLoad(&gamma, gammaFilename);
	WeightLoad(&movingMean, movMeanFilename);
	WeightLoad(&movingVariance, movVarFilename);
}

void BatchNormalization::Apply(CpuGpuMat* resultMat) {

	gpuBatchNormalization(resultMat, &beta, &gamma, &movingMean, &movingVariance, epsilon);
}

void BatchNormalization::Host2Device()
{
	beta.Host2Device();
	gamma.Host2Device();
	movingMean.Host2Device();
	movingVariance.Host2Device();
}
