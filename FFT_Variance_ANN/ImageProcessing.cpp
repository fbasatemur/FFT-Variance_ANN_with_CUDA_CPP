#include "ImageProcessing.h"

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include <cmath>

using namespace cv;
using namespace std;

float averageFFT(const cv::Mat& fourierMag32F, int maskRow, int maskCol) {

	float totalValue = 0.0F;

	int columnStart = (fourierMag32F.cols - maskCol) / 2;
	int columnEnd = (fourierMag32F.cols + maskCol) / 2;

	int rowStart = (fourierMag32F.rows - maskRow) / 2;
	int rowEnd = (fourierMag32F.rows + maskRow) / 2;

	for (uint row = rowStart; row < rowEnd; row++) {
		for (uint col = columnStart; col < columnEnd; col++) {

			totalValue += fourierMag32F.at<float>(row, col);
		}
	}
	return totalValue / (maskRow * maskCol);
}

float averageGray(const cv::Mat& matGray, int maskRow, int maskCol) {

	float totalValue = 0.0F;

	int columnStart = (matGray.cols - maskCol) / 2;
	int columnEnd = (matGray.cols + maskCol) / 2;

	int rowStart = (matGray.rows - maskRow) / 2;
	int rowEnd = (matGray.rows + maskRow) / 2;

	for (uint row = rowStart; row < rowEnd; row++) {
		for (uint col = columnStart; col < columnEnd; col++) {

			totalValue += matGray.at<uchar>(row, col);
		}
	}
	return totalValue / (maskRow * maskCol);
}

float variance(const cv::Mat& matGray, int maskRow, int maskCol) {

	float total = 0;

	int columnStart = (matGray.cols - maskCol) / 2;
	int columnEnd = (matGray.cols + maskCol) / 2;

	int rowStart = (matGray.rows - maskRow) / 2;
	int rowEnd = (matGray.rows + maskRow) / 2;

	double average = averageGray(matGray, maskRow, maskCol);

	for (uint row = rowStart; row < rowEnd; row++) {
		for (uint col = columnStart; col < columnEnd; col++) {

			total += pow((matGray.at<uchar>(row, col) - average), 2);
		}
	}

	return total / (maskRow * maskCol);
}

cv::Mat openCVFFT(const cv::Mat& grayImage) {

	Mat padded;
	int m = getOptimalDFTSize(grayImage.rows);
	int n = getOptimalDFTSize(grayImage.cols);
	copyMakeBorder(grayImage, padded, 0, m - grayImage.rows, 0, n - grayImage.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);
	dft(complexI, complexI);

	// => log(1 + sqrt(Re(DFT(Image))^2 + Im(DFT(Image))^2))
	split(complexI, planes);                    // planes[0] = Re(DFT(Image), planes[1] = Im(DFT(Image))
	magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
	Mat magImage_32F = planes[0];
	magImage_32F += Scalar::all(1);
	log(magImage_32F, magImage_32F);

	magImage_32F = magImage_32F(Rect(0, 0, magImage_32F.cols & -2, magImage_32F.rows & -2));

	int cx = magImage_32F.cols / 2;
	int cy = magImage_32F.rows / 2;
	Mat q0(magImage_32F, Rect(0, 0, cx, cy));
	Mat q1(magImage_32F, Rect(cx, 0, cx, cy));
	Mat q2(magImage_32F, Rect(0, cy, cx, cy));
	Mat q3(magImage_32F, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	// normalize(magImage_32F, magImage_32F, 0, 1, NORM_MINMAX);	// 0 - 1 arasinda normalize edilmistir ( imshow() bunu destekler )
	// normalize(magImage_32F, magImage_32F, 0, 255, NORM_MINMAX);		// 0 - 255 arasinda normalize edilmistir

	for (int row = 0; row < magImage_32F.rows; row++)
		for (int col = 0; col < magImage_32F.cols; col++)
			magImage_32F.at<float>(row, col) = magImage_32F.at<float>(row, col) * 20.0F;

	return magImage_32F;											// magImage_32F, CV_32F yani float degerleri depolar, deger erisimi .at<float>(r,c) 	
}

System::Drawing::Bitmap^ fftMat2Bitmap(const cv::Mat& matImage, float* inputCpuP) {

	System::Drawing::Bitmap^ bitmapImage = gcnew System::Drawing::Bitmap(matImage.cols, matImage.rows);
	System::Drawing::Color color;
	float pixelValue = 0.0F;

	double min;
	double max;

	cv::minMaxLoc(matImage, &min, &max);

	for (int row = 0; row < matImage.rows; row++) {
		for (int col = 0; col < matImage.cols; col++) {

			pixelValue = matImage.at<float>(row, col);						// pixelValue => 0 - max arasinda 

			inputCpuP[row * matImage.cols + col] = (float)(pixelValue / max);		// normalize value

			color = System::Drawing::Color::FromArgb((int)(pixelValue) % 255, (int)(pixelValue) % 255, (int)(pixelValue) % 255);
			bitmapImage->SetPixel(col, row, color);
		}
	}
	return bitmapImage;
}

