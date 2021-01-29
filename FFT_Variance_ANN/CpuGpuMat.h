#pragma once

class CpuGpuMat {

public:
	void* CpuP;		// ram pointer
	void* GpuP;		// graphic memory pointer
	int Rows;
	int Cols;
	int Size;		// rows * cols
	bool isMemPinned = false;

	CpuGpuMat();
	CpuGpuMat(const int& rows, const int& cols, bool useBias = true, bool useMemPin = false);
	~CpuGpuMat();			// memory free
	void host2Device();
	void device2Host();
	void cpuGpuAlloc();		// memory allocation

private:
	int getAllocationSize();
};

