#pragma once
#include<windows.h>
#include <atlstr.h>		

#include<iostream>
#include <cuda_runtime_api.h>						// cudaDeviceSynchronize()
#include <time.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal.h>
#include <string.h>

#include "CpuGpuMat.h"
#include "KernelGpu.cuh"
#include "ImageProcessing.h"
#include "Dense.h"
#include "BatchNormalization.h"
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

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
	private: System::Windows::Forms::Label^ MultTimeLbl;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ VarianceLbl;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ imagePathLbl;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>

		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->MultTimeLbl = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->VarianceLbl = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->imagePathLbl = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1241, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
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
			this->label1->Location = System::Drawing::Point(1070, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(168, 17);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Parallel Processing Time:";
			// 
			// MultTimeLbl
			// 
			this->MultTimeLbl->AutoSize = true;
			this->MultTimeLbl->Location = System::Drawing::Point(1070, 67);
			this->MultTimeLbl->Name = L"MultTimeLbl";
			this->MultTimeLbl->Size = System::Drawing::Size(20, 17);
			this->MultTimeLbl->TabIndex = 13;
			this->MultTimeLbl->Text = L"...";
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1241, 603);
			this->Controls->Add(this->imagePathLbl);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->VarianceLbl);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->MultTimeLbl);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"Variance Predict";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {


	}
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

		CpuGpuMat inputImage(1, 625);

		std::string denseKernel = ".\\model_save_weight.h5_to_txt\\dense\\kernel.txt";
		std::string denseBias = ".\\model_save_weight.h5_to_txt\\dense\\bias.txt";

		std::string dense1Kernel = ".\\model_save_weight.h5_to_txt\\dense_1\\kernel.txt";
		std::string dense1Bias = ".\\model_save_weight.h5_to_txt\\dense_1\\bias.txt";

		std::string dense2Kernel = ".\\model_save_weight.h5_to_txt\\dense_2\\kernel.txt";
		std::string dense2Bias = ".\\model_save_weight.h5_to_txt\\dense_2\\bias.txt";

		std::string dense3Kernel = ".\\model_save_weight.h5_to_txt\\dense_3\\kernel.txt";
		std::string dense3Bias = ".\\model_save_weight.h5_to_txt\\dense_3\\bias.txt";

		std::string dense4Kernel = ".\\model_save_weight.h5_to_txt\\dense_4\\kernel.txt";
		std::string dense4Bias = ".\\model_save_weight.h5_to_txt\\dense_4\\bias.txt";

		std::string dense5Kernel = ".\\model_save_weight.h5_to_txt\\dense_5\\kernel.txt";
		std::string dense5Bias = ".\\model_save_weight.h5_to_txt\\dense_5\\bias.txt";

		std::string dense6Kernel = ".\\model_save_weight.h5_to_txt\\dense_6\\kernel.txt";
		std::string dense6Bias = ".\\model_save_weight.h5_to_txt\\dense_6\\bias.txt";

		std::string dense7Kernel = ".\\model_save_weight.h5_to_txt\\dense_7\\kernel.txt";
		std::string dense7Bias = ".\\model_save_weight.h5_to_txt\\dense_7\\bias.txt";

		std::string dense8Kernel = ".\\model_save_weight.h5_to_txt\\dense_8\\kernel.txt";
		std::string dense8Bias = ".\\model_save_weight.h5_to_txt\\dense_8\\bias.txt";

		Dense dense(100, inputImage.Rows, inputImage.Cols);
		Dense dense1(100, dense.Result.Rows, dense.Result.Cols);
		Dense dense2(100, dense1.Result.Rows, dense1.Result.Cols);
		Dense dense3(100, dense2.Result.Rows, dense2.Result.Cols);
		Dense dense4(100, dense3.Result.Rows, dense3.Result.Cols);
		Dense dense5(100, dense4.Result.Rows, dense4.Result.Cols);
		Dense dense6(100, dense5.Result.Rows, dense5.Result.Cols);
		Dense dense7(20, dense6.Result.Rows, dense6.Result.Cols);
		Dense dense8(1, dense7.Result.Rows, dense7.Result.Cols, false);

		// load kernel and bias weights to ram

		dense.load(denseKernel, denseBias);				
		dense1.load(dense1Kernel, dense1Bias);
		dense2.load(dense2Kernel, dense2Bias);
		dense3.load(dense3Kernel, dense3Bias);
		dense4.load(dense4Kernel, dense4Bias);
		dense5.load(dense5Kernel, dense5Bias);
		dense6.load(dense6Kernel, dense6Bias);
		dense7.load(dense7Kernel, dense7Bias);
		dense8.load(dense8Kernel, dense8Bias);

		std::string batchNormBeta = ".\\model_save_weight.h5_to_txt\\batch_normalization\\beta.txt";
		std::string batchNormGamma = ".\\model_save_weight.h5_to_txt\\batch_normalization\\gamma.txt";
		std::string batchNormMovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization\\moving_mean.txt";
		std::string batchNormMovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization\\moving_variance.txt";

		std::string batchNorm1Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_1\\beta.txt";
		std::string batchNorm1Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_1\\gamma.txt";
		std::string batchNorm1MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_1\\moving_mean.txt";
		std::string batchNorm1MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_1\\moving_variance.txt";

		std::string batchNorm2Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_2\\beta.txt";
		std::string batchNorm2Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_2\\gamma.txt";
		std::string batchNorm2MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_2\\moving_mean.txt";
		std::string batchNorm2MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_2\\moving_variance.txt";

		std::string batchNorm3Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_3\\beta.txt";
		std::string batchNorm3Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_3\\gamma.txt";
		std::string batchNorm3MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_3\\moving_mean.txt";
		std::string batchNorm3MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_3\\moving_variance.txt";

		std::string batchNorm4Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_4\\beta.txt";
		std::string batchNorm4Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_4\\gamma.txt";
		std::string batchNorm4MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_4\\moving_mean.txt";
		std::string batchNorm4MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_4\\moving_variance.txt";

		std::string batchNorm5Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_5\\beta.txt";
		std::string batchNorm5Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_5\\gamma.txt";
		std::string batchNorm5MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_5\\moving_mean.txt";
		std::string batchNorm5MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_5\\moving_variance.txt";

		std::string batchNorm6Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_6\\beta.txt";
		std::string batchNorm6Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_6\\gamma.txt";
		std::string batchNorm6MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_6\\moving_mean.txt";
		std::string batchNorm6MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_6\\moving_variance.txt";

		std::string batchNorm7Beta = ".\\model_save_weight.h5_to_txt\\batch_normalization_7\\beta.txt";
		std::string batchNorm7Gamma = ".\\model_save_weight.h5_to_txt\\batch_normalization_7\\gamma.txt";
		std::string batchNorm7MovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization_7\\moving_mean.txt";
		std::string batchNorm7MovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization_7\\moving_variance.txt";

		// gamma = 1.0F, beta = 0.0F, epsilon = 0.001F 

		BatchNormalization batchNorm(dense.Result.Rows, dense.Result.Cols);
		BatchNormalization batchNorm1(dense1.Result.Rows, dense1.Result.Cols);
		BatchNormalization batchNorm2(dense2.Result.Rows, dense2.Result.Cols);
		BatchNormalization batchNorm3(dense3.Result.Rows, dense3.Result.Cols);
		BatchNormalization batchNorm4(dense4.Result.Rows, dense4.Result.Cols);
		BatchNormalization batchNorm5(dense5.Result.Rows, dense5.Result.Cols);
		BatchNormalization batchNorm6(dense6.Result.Rows, dense6.Result.Cols);
		BatchNormalization batchNorm7(dense7.Result.Rows, dense7.Result.Cols);

		// load batchnormalization layer weights to ram

		batchNorm.load(batchNormBeta, batchNormGamma, batchNormMovingMean, batchNormMovingVariance);
		batchNorm1.load(batchNorm1Beta, batchNorm1Gamma, batchNorm1MovingMean, batchNorm1MovingVariance);
		batchNorm2.load(batchNorm2Beta, batchNorm2Gamma, batchNorm2MovingMean, batchNorm2MovingVariance);
		batchNorm3.load(batchNorm3Beta, batchNorm3Gamma, batchNorm3MovingMean, batchNorm3MovingVariance);
		batchNorm4.load(batchNorm4Beta, batchNorm4Gamma, batchNorm4MovingMean, batchNorm4MovingVariance);
		batchNorm5.load(batchNorm5Beta, batchNorm5Gamma, batchNorm5MovingMean, batchNorm5MovingVariance);
		batchNorm6.load(batchNorm6Beta, batchNorm6Gamma, batchNorm6MovingMean, batchNorm6MovingVariance);
		batchNorm7.load(batchNorm7Beta, batchNorm7Gamma, batchNorm7MovingMean, batchNorm7MovingVariance);

		// copy to graphic card memory from ram

		dense.host2Device();
		dense1.host2Device();
		dense2.host2Device();
		dense3.host2Device();
		dense4.host2Device();
		dense5.host2Device();
		dense6.host2Device();
		dense7.host2Device();
		dense8.host2Device();

		batchNorm.host2Device();
		batchNorm1.host2Device();
		batchNorm2.host2Device();
		batchNorm3.host2Device();
		batchNorm4.host2Device();
		batchNorm5.host2Device();
		batchNorm6.host2Device();
		batchNorm7.host2Device();

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			pictureBox1->ImageLocation = openFileDialog1->FileName;
			imagePathLbl->Text = openFileDialog1->FileName;

			msclr::interop::marshal_context context;
			cv::Mat grayImage = cv::imread(context.marshal_as<cv::String>(openFileDialog1->FileName), cv::IMREAD_GRAYSCALE);

			cv::Rect cropSizeImage(grayImage.cols / 2 - 51, grayImage.rows / 2 - 51, 100, 100);
			cv::Mat cutGrayImage = grayImage(cropSizeImage);


			cv::Mat fftImage = openCVFFT(cutGrayImage);
			cv::Rect cropSizeFFT(24, 24, 25, 25);
			cv::Mat cutFFT = fftImage(cropSizeFFT);

			pictureBox2->Image = fftMat2Bitmap(cutFFT, (float*)inputImage.CpuP);	// set cutFFT values to inputImage
			
			/*
				Host => ram
				Device => graphics memory
			*/

			inputImage.host2Device();


			clock_t start = clock();

			dense.apply(&inputImage);
			gpuRelu(&dense.Result);
			batchNorm.apply(&dense.Result);

			dense1.apply(&dense.Result);
			gpuRelu(&dense1.Result);
			batchNorm1.apply(&dense1.Result);

			dense2.apply(&dense1.Result);
			gpuRelu(&dense2.Result);
			batchNorm2.apply(&dense2.Result);

			dense3.apply(&dense2.Result);
			gpuRelu(&dense3.Result);
			batchNorm3.apply(&dense3.Result);

			dense4.apply(&dense3.Result);
			gpuRelu(&dense4.Result);
			batchNorm4.apply(&dense4.Result);

			dense5.apply(&dense4.Result);
			gpuRelu(&dense5.Result);
			batchNorm5.apply(&dense5.Result);

			dense6.apply(&dense5.Result);
			gpuRelu(&dense6.Result);
			batchNorm6.apply(&dense6.Result);

			dense7.apply(&dense6.Result);
			gpuRelu(&dense7.Result);
			batchNorm7.apply(&dense7.Result);

			dense8.apply(&dense7.Result);
			gpuSigmoid(&dense8.Result);
			dense8.Result.device2Host();

			clock_t end = clock();
			MultTimeLbl->Text = ((float)(end - start) / CLOCKS_PER_SEC).ToString() + " sec";

			float* variancePredict = (float*)dense8.Result.CpuP;
			VarianceLbl->Text = variancePredict[0].ToString();

		}
	}
	};
}
