#pragma once
#include<windows.h>
#include "opencv2/imgproc.hpp"
#include "CpuGpuMat.h"


cv::Mat openCVFFT(const cv::Mat& grayImage);
System::Drawing::Bitmap^ fftMat2Bitmap(const cv::Mat& matImage, float* inputCpuP);
float averageFFT(const cv::Mat& fourierMag32F, int maskRow, int maskCol);
float variance(const cv::Mat& matGray, int maskRow, int maskCol);