#pragma once
#include<windows.h>
#include <atlstr.h>		
#include <Windows.h>
#include "Image.h"
#include "Process.h"

#include<iostream>
#include <cuda_runtime_api.h>						// cudaDeviceSynchronize()
#include <time.h>
#include <string.h>

#include "CpuGpuMat.h"
#include "KernelGpu.cuh"
#include "Dense.h"
#include "BatchNormalization.h"

namespace Form_Empty {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the confilePathStructor code here
			//


			std::string denseKernel = ".\\model_save_weight.h5_to_txt\\dense_9\\kernel.txt";
			std::string denseBias = ".\\model_save_weight.h5_to_txt\\dense_9\\bias.txt";

			std::string dense1Kernel = ".\\model_save_weight.h5_to_txt\\dense_10\\kernel.txt";
			std::string dense1Bias = ".\\model_save_weight.h5_to_txt\\dense_10\\bias.txt";

			std::string dense2Kernel = ".\\model_save_weight.h5_to_txt\\dense_11\\kernel.txt";
			std::string dense2Bias = ".\\model_save_weight.h5_to_txt\\dense_11\\bias.txt";

			std::string dense3Kernel = ".\\model_save_weight.h5_to_txt\\dense_12\\kernel.txt";
			std::string dense3Bias = ".\\model_save_weight.h5_to_txt\\dense_12\\bias.txt";

			std::string dense4Kernel = ".\\model_save_weight.h5_to_txt\\dense_13\\kernel.txt";
			std::string dense4Bias = ".\\model_save_weight.h5_to_txt\\dense_13\\bias.txt";

			std::string dense5Kernel = ".\\model_save_weight.h5_to_txt\\dense_14\\kernel.txt";
			std::string dense5Bias = ".\\model_save_weight.h5_to_txt\\dense_14\\bias.txt";

			std::string dense6Kernel = ".\\model_save_weight.h5_to_txt\\dense_15\\kernel.txt";
			std::string dense6Bias = ".\\model_save_weight.h5_to_txt\\dense_15\\bias.txt";

			std::string dense7Kernel = ".\\model_save_weight.h5_to_txt\\dense_16\\kernel.txt";
			std::string dense7Bias = ".\\model_save_weight.h5_to_txt\\dense_16\\bias.txt";

			std::string dense8Kernel = ".\\model_save_weight.h5_to_txt\\dense_17\\kernel.txt";
			std::string dense8Bias = ".\\model_save_weight.h5_to_txt\\dense_17\\bias.txt";

			dense = new Dense(100, 1, 625);
			dense1 = new Dense(100, dense->Result);
			dense2 = new Dense(100, dense1->Result);
			dense3 = new Dense(100, dense2->Result);
			dense4 = new Dense(100, dense3->Result);
			dense5 = new Dense(100, dense4->Result);
			dense6 = new Dense(100, dense5->Result);
			dense7 = new Dense(20, dense6->Result);
			dense8 = new Dense(1, dense7->Result, true);

			// Load kernel and bias weights to ram

			dense->Load(denseKernel, denseBias);
			dense1->Load(dense1Kernel, dense1Bias);
			dense2->Load(dense2Kernel, dense2Bias);
			dense3->Load(dense3Kernel, dense3Bias);
			dense4->Load(dense4Kernel, dense4Bias);
			dense5->Load(dense5Kernel, dense5Bias);
			dense6->Load(dense6Kernel, dense6Bias);
			dense7->Load(dense7Kernel, dense7Bias);
			dense8->Load(dense8Kernel, dense8Bias);

			std::string batchNormBeta = ".\\model_save_weight.h5_to_txt\\batch_normalization_8\\beta.txt";
			std::string batchNormGamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_8\\gamma.txt";
			std::string batchNormMovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_8\\moving_mean.txt";
			std::string batchNormMovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_8\\moving_variance.txt";

			std::string batchNorm1Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_9\\beta.txt";
			std::string batchNorm1Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_9\\gamma.txt";
			std::string batchNorm1MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_9\\moving_mean.txt";
			std::string batchNorm1MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_9\\moving_variance.txt";

			std::string batchNorm2Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_10\\beta.txt";
			std::string batchNorm2Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_10\\gamma.txt";
			std::string batchNorm2MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_10\\moving_mean.txt";
			std::string batchNorm2MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_10\\moving_variance.txt";

			std::string batchNorm3Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_11\\beta.txt";
			std::string batchNorm3Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_11\\gamma.txt";
			std::string batchNorm3MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_11\\moving_mean.txt";
			std::string batchNorm3MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_11\\moving_variance.txt";

			std::string batchNorm4Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_12\\beta.txt";
			std::string batchNorm4Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_12\\gamma.txt";
			std::string batchNorm4MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_12\\moving_mean.txt";
			std::string batchNorm4MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_12\\moving_variance.txt";

			std::string batchNorm5Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_13\\beta.txt";
			std::string batchNorm5Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_13\\gamma.txt";
			std::string batchNorm5MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_13\\moving_mean.txt";
			std::string batchNorm5MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_13\\moving_variance.txt";

			std::string batchNorm6Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_14\\beta.txt";
			std::string batchNorm6Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_14\\gamma.txt";
			std::string batchNorm6MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_14\\moving_mean.txt";
			std::string batchNorm6MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_14\\moving_variance.txt";

			std::string batchNorm7Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_15\\beta.txt";
			std::string batchNorm7Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_15\\gamma.txt";
			std::string batchNorm7MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_15\\moving_mean.txt";
			std::string batchNorm7MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_15\\moving_variance.txt";

			// gamma = 1.0F, beta = 0.0F, epsilon = 0.001F 

			batchNorm = new BatchNormalization(dense->Result);
			batchNorm1 = new BatchNormalization(dense1->Result);
			batchNorm2 = new BatchNormalization(dense2->Result);
			batchNorm3 = new BatchNormalization(dense3->Result);
			batchNorm4 = new BatchNormalization(dense4->Result);
			batchNorm5 = new BatchNormalization(dense5->Result);
			batchNorm6 = new BatchNormalization(dense6->Result);
			batchNorm7 = new BatchNormalization(dense7->Result);

			// Load batchnormalization layer weights to ram

			batchNorm->Load(batchNormBeta, batchNormGamma, batchNormMovingMean, batchNormMovingVariance);
			batchNorm1->Load(batchNorm1Beta, batchNorm1Gamma, batchNorm1MovingMean, batchNorm1MovingVariance);
			batchNorm2->Load(batchNorm2Beta, batchNorm2Gamma, batchNorm2MovingMean, batchNorm2MovingVariance);
			batchNorm3->Load(batchNorm3Beta, batchNorm3Gamma, batchNorm3MovingMean, batchNorm3MovingVariance);
			batchNorm4->Load(batchNorm4Beta, batchNorm4Gamma, batchNorm4MovingMean, batchNorm4MovingVariance);
			batchNorm5->Load(batchNorm5Beta, batchNorm5Gamma, batchNorm5MovingMean, batchNorm5MovingVariance);
			batchNorm6->Load(batchNorm6Beta, batchNorm6Gamma, batchNorm6MovingMean, batchNorm6MovingVariance);
			batchNorm7->Load(batchNorm7Beta, batchNorm7Gamma, batchNorm7MovingMean, batchNorm7MovingVariance);

			// copy to graphic card memory from ram

			dense->Host2Device();
			dense1->Host2Device();
			dense2->Host2Device();
			dense3->Host2Device();
			dense4->Host2Device();
			dense5->Host2Device();
			dense6->Host2Device();
			dense7->Host2Device();
			dense8->Host2Device();

			batchNorm->Host2Device();
			batchNorm1->Host2Device();
			batchNorm2->Host2Device();
			batchNorm3->Host2Device();
			batchNorm4->Host2Device();
			batchNorm5->Host2Device();
			batchNorm6->Host2Device();
			batchNorm7->Host2Device();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ TotalTimeLbl;

	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ VarianceLbl;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ imagePathLbl;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

		Dense* dense;
		Dense* dense1;
		Dense* dense2;
		Dense* dense3;
		Dense* dense4;
		Dense* dense5;
		Dense* dense6;
		Dense* dense7;
		Dense* dense8;

		BatchNormalization* batchNorm;
		BatchNormalization* batchNorm1;
		BatchNormalization* batchNorm2;
		BatchNormalization* batchNorm3;
		BatchNormalization* batchNorm4;
		BatchNormalization* batchNorm5;
		BatchNormalization* batchNorm6;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ TotalTransferLbl;
	private: System::Windows::Forms::Label^ TotalPredictLbl;


	private: System::Windows::Forms::Label^ label6;
		   BatchNormalization* batchNorm7;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>

		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->TotalTimeLbl = (gcnew System::Windows::Forms::Label());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->VarianceLbl = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->imagePathLbl = (gcnew System::Windows::Forms::Label());
			   this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->TotalTransferLbl = (gcnew System::Windows::Forms::Label());
			   this->TotalPredictLbl = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->menuStrip1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(1728, 30);
			   this->menuStrip1->TabIndex = 0;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // fileToolStripMenuItem
			   // 
			   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			   this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 26);
			   this->fileToolStripMenuItem->Text = L"File";
			   // 
			   // openToolStripMenuItem
			   // 
			   this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			   this->openToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			   this->openToolStripMenuItem->Text = L"Open";
			   this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   this->openFileDialog1->Filter = L"bmp files (*.bmp)|*.bmp";
			   this->openFileDialog1->Multiselect = true;
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(12, 71);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(520, 520);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pictureBox1->TabIndex = 1;
			   this->pictureBox1->TabStop = false;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(1073, 36);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(75, 17);
			   this->label1->TabIndex = 12;
			   this->label1->Text = L"Total Time";
			   // 
			   // TotalTimeLbl
			   // 
			   this->TotalTimeLbl->AutoSize = true;
			   this->TotalTimeLbl->Location = System::Drawing::Point(1076, 67);
			   this->TotalTimeLbl->Name = L"TotalTimeLbl";
			   this->TotalTimeLbl->Size = System::Drawing::Size(20, 17);
			   this->TotalTimeLbl->TabIndex = 13;
			   this->TotalTimeLbl->Text = L"...";
			   // 
			   // pictureBox2
			   // 
			   this->pictureBox2->Location = System::Drawing::Point(538, 71);
			   this->pictureBox2->Name = L"pictureBox2";
			   this->pictureBox2->Size = System::Drawing::Size(520, 520);
			   this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pictureBox2->TabIndex = 14;
			   this->pictureBox2->TabStop = false;
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(1073, 117);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(116, 17);
			   this->label2->TabIndex = 15;
			   this->label2->Text = L"Variance Predict:";
			   // 
			   // VarianceLbl
			   // 
			   this->VarianceLbl->AutoSize = true;
			   this->VarianceLbl->Location = System::Drawing::Point(1073, 147);
			   this->VarianceLbl->Name = L"VarianceLbl";
			   this->VarianceLbl->Size = System::Drawing::Size(20, 17);
			   this->VarianceLbl->TabIndex = 16;
			   this->VarianceLbl->Text = L"...";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(12, 36);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(83, 17);
			   this->label3->TabIndex = 17;
			   this->label3->Text = L"Image Path:";
			   // 
			   // imagePathLbl
			   // 
			   this->imagePathLbl->AutoSize = true;
			   this->imagePathLbl->Location = System::Drawing::Point(102, 36);
			   this->imagePathLbl->Name = L"imagePathLbl";
			   this->imagePathLbl->Size = System::Drawing::Size(20, 17);
			   this->imagePathLbl->TabIndex = 18;
			   this->imagePathLbl->Text = L"...";
			   // 
			   // chart1
			   // 
			   chartArea2->Name = L"ChartArea1";
			   this->chart1->ChartAreas->Add(chartArea2);
			   legend2->Name = L"Legend1";
			   this->chart1->Legends->Add(legend2);
			   this->chart1->Location = System::Drawing::Point(1073, 189);
			   this->chart1->Name = L"chart1";
			   series2->ChartArea = L"ChartArea1";
			   series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			   series2->Legend = L"Legend1";
			   series2->Name = L"Variance";
			   this->chart1->Series->Add(series2);
			   this->chart1->Size = System::Drawing::Size(641, 402);
			   this->chart1->TabIndex = 19;
			   this->chart1->Text = L"chart1";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(1238, 36);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(133, 17);
			   this->label4->TabIndex = 20;
			   this->label4->Text = L"Total Transfer Time";
			   // 
			   // TotalTransferLbl
			   // 
			   this->TotalTransferLbl->AutoSize = true;
			   this->TotalTransferLbl->Location = System::Drawing::Point(1238, 67);
			   this->TotalTransferLbl->Name = L"TotalTransferLbl";
			   this->TotalTransferLbl->Size = System::Drawing::Size(20, 17);
			   this->TotalTransferLbl->TabIndex = 21;
			   this->TotalTransferLbl->Text = L"...";
			   // 
			   // TotalPredictLbl
			   // 
			   this->TotalPredictLbl->AutoSize = true;
			   this->TotalPredictLbl->Location = System::Drawing::Point(1414, 67);
			   this->TotalPredictLbl->Name = L"TotalPredictLbl";
			   this->TotalPredictLbl->Size = System::Drawing::Size(20, 17);
			   this->TotalPredictLbl->TabIndex = 23;
			   this->TotalPredictLbl->Text = L"...";
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(1414, 36);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(123, 17);
			   this->label6->TabIndex = 22;
			   this->label6->Text = L"Total Predict Time";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1728, 603);
			   this->Controls->Add(this->TotalPredictLbl);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->TotalTransferLbl);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->chart1);
			   this->Controls->Add(this->imagePathLbl);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->VarianceLbl);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->pictureBox2);
			   this->Controls->Add(this->TotalTimeLbl);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Margin = System::Windows::Forms::Padding(4);
			   this->Name = L"MyForm";
			   this->Text = L"Variance Predict - GPU";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {


	}
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{

			long size;
			int width, height;
			BYTE* buffer, * raw_intensity;

			int cutRawWidth = 100;												// image size cut out from center
			int cutRawHeight = 100;

			double* Real_part = new double[cutRawWidth * cutRawHeight];			// FFT Reals
			double* Im_part = new double[cutRawWidth * cutRawHeight];			// FFT imaginary
			double* image = new double[cutRawWidth * cutRawHeight];				// FFT magnitude values

			const int cutFFTWidth = 25;
			const int cutFFTHeight = 25;
			double* cutFFT = new double[cutFFTWidth * cutFFTHeight];			// 25 * 25 FFT mag values
			double* fourier = new double[cutFFTWidth * cutFFTHeight];			// 25 * 25 FFT normalize (0-1) values

			int beginRow, beginCol;
			int setRow, setCol;


			chart1->Series["Variance"]->Points->Clear();

			clock_t totalTransferTime = 0;
			clock_t totalPredictTime = 0;
			clock_t startPredict;
			clock_t start;

			int selectedImages = openFileDialog1->FileNames->GetLength(0);

			// ANN input values pointer
			int inputSize = cutFFTWidth * cutFFTHeight;
			float* inputs = new float[inputSize * selectedImages];

			for (int imageIndex = 0; imageIndex < selectedImages; imageIndex++)
			{

				imagePathLbl->Text = openFileDialog1->FileNames[imageIndex];
				pictureBox1->ImageLocation = openFileDialog1->FileNames[imageIndex];
				CString str = openFileDialog1->FileNames[imageIndex];

				// read BMP image
				buffer = LoadBMP(width, height, size, (LPCTSTR)str);
				raw_intensity = ConvertBMPToIntensity(buffer, width, height);

				beginRow = (height - cutRawHeight) / 2;
				beginCol = (width - cutRawWidth) / 2;

				// image is cut 100 *100 size from center of raw_intensity
				// Gri seviyeyedeki image frekans domeninde ortalanmasi icin (-1)^(x+y) ile carpiliyor
				for (int i = beginRow; i < beginRow + 100; i++)
					for (int j = beginCol; j < beginCol + 100; j++)
						image[(i - beginRow) * cutRawWidth + (j - beginCol)] = double(raw_intensity[i * width + j]) * pow(-1, (i + j));


				// calculate 100 * 100 size FFT image
				FFT2D(image, Real_part, Im_part, cutRawWidth, cutRawHeight);

				double fftValue;
				double maks1 = -1000000000;
				double min1 = 1000000000;

				// 25 * 25 pixels FFT image cut 
				for (int i = 25; i < 50; i++) {
					for (int j = 25; j < 50; j++) {

						setRow = (i - cutFFTHeight);
						setCol = (j - cutFFTWidth);
						fftValue = log(0.05 + sqrt(Real_part[i * cutRawWidth + j] * Real_part[i * cutRawWidth + j] + Im_part[i * cutRawWidth + j] * Im_part[i * cutRawWidth + j]));
						cutFFT[setRow * cutFFTWidth + setCol] = fftValue;

						if (fftValue > maks1)
							maks1 = fftValue;
						if (fftValue < min1)
							min1 = fftValue;
					}
				}

				// 25 * 25 FFT image 0-1 normalize
				for (int i = 0; i < cutFFTHeight; i++)
					for (int j = 0; j < cutFFTWidth; j++)
						fourier[i * cutFFTWidth + j] = (cutFFT[i * cutFFTWidth + j] - min1) / (maks1 - min1);


				// ANN input values is setted
				for (int i = 0; i < inputSize; i++)
					inputs[inputSize * imageIndex + i] = (float)fourier[i];

				delete[] buffer;
				delete[] raw_intensity;
			}

			Bitmap^ surface = gcnew Bitmap(cutFFTWidth, cutFFTHeight);
			pictureBox2->Image = surface;
			Color c;
			// display in pictureBox 
			for (int row = 0; row < cutFFTHeight; row++)
				for (int col = 0; col < cutFFTWidth; col++) {

					c = Color::FromArgb(BYTE(fourier[row * cutFFTWidth + col] * 255.0), BYTE(fourier[row * cutFFTWidth + col] * 255.0), BYTE(fourier[row * cutFFTWidth + col] * 255.0));
					surface->SetPixel(col, row, c);
				}


			CpuGpuMat inputBuffer(inputs, 1, 625, selectedImages, true);
			CpuGpuMat outputBuffer(dense8->Result, selectedImages);

			/*
				Host => ram
				Device => graphics memory
			*/

			start = clock();
			inputBuffer.Host2Device();
			totalTransferTime += (clock() - start);

			for (int i = 0; i < openFileDialog1->FileNames->GetLength(0); i++)
			{
				startPredict = clock();

				dense->Apply(&inputBuffer, i);
				gpuRelu(&dense->Result);
				batchNorm->Apply(&dense->Result);

				dense1->Apply(&dense->Result);
				gpuRelu(&dense1->Result);
				batchNorm1->Apply(&dense1->Result);

				dense2->Apply(&dense1->Result);
				gpuRelu(&dense2->Result);
				batchNorm2->Apply(&dense2->Result);

				dense3->Apply(&dense2->Result);
				gpuRelu(&dense3->Result);
				batchNorm3->Apply(&dense3->Result);

				dense4->Apply(&dense3->Result);
				gpuRelu(&dense4->Result);
				batchNorm4->Apply(&dense4->Result);

				dense5->Apply(&dense4->Result);
				gpuRelu(&dense5->Result);
				batchNorm5->Apply(&dense5->Result);

				dense6->Apply(&dense5->Result);
				gpuRelu(&dense6->Result);
				batchNorm6->Apply(&dense6->Result);

				dense7->Apply(&dense6->Result);
				gpuRelu(&dense7->Result);
				batchNorm7->Apply(&dense7->Result);

				dense8->Apply(&dense7->Result, 0, i);
				gpuSigmoid(&dense8->Result, i);

				totalPredictTime += (clock() - startPredict);
			}

			start = clock();
			outputBuffer.Device2Host();
			totalTransferTime += (clock() - start);

			TotalTimeLbl->Text = ((float)(totalTransferTime + totalPredictTime) / CLOCKS_PER_SEC).ToString() + " sec";
			TotalTransferLbl->Text = ((float)(totalTransferTime) / CLOCKS_PER_SEC).ToString() + " sec";
			TotalPredictLbl->Text = ((float)(totalPredictTime) / CLOCKS_PER_SEC).ToString() + " sec";

			float* predicts = (float*)outputBuffer.CpuP;

			for (int i = 0; i < outputBuffer.Size; i++)
			{
				VarianceLbl->Text = predicts[i].ToString();
				chart1->Series["Variance"]->Points->AddXY(i, predicts[i]);
			}


			delete[] Real_part;
			delete[] Im_part;
			delete[] image;
			delete[] fourier;
			delete[] cutFFT;
			delete[] inputs;
		}
	}
	};
}