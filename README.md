# FFT-Variance_ANN_with_CUDA_CPP

Keras model weights are used in the CPP environment.

### Requirements
* Windows or Linux
* **CUDA == 10.2**: https://developer.nvidia.com/cuda-toolkit-archive
* **OpenCV == 4.1.1**: https://opencv.org/releases
* **cuDNN == v8.0.2**: https://developer.nvidia.com/rdp/cudnn-archive
* **GPU with CC >= 3.0**: https://en.wikipedia.org/wiki/CUDA#GPUs_supported
* **on Linux GCC or Clang, on Windows MSVC 2017/2019**

### Features of the Keras model
* Dense Layer
* ReLu Activation
* Bach Normalization
* Sigmoid Activation

Keras model consists of 9 Dense layers and 8 Batch Normalization layers. The model takes the vector of the Fast Fourier Transform image of 25x25 = 625 from the input.
Output Layer consists of 1 neuron and returns the variance value.

```ini
CpuGpuMat inputImage(1, 625);   // CpuGpuMat inputVector(1, cols, bias=true)

Dense dense(100, inputImage.Rows, inputImage.Cols);               // Dense dense(neurons, inputVector.Rows, inputVector.Cols, bias=true)
Dense dense1(100, dense.Result.Rows, dense.Result.Cols);
Dense dense2(100, dense1.Result.Rows, dense1.Result.Cols);
Dense dense3(100, dense2.Result.Rows, dense2.Result.Cols);
Dense dense4(100, dense3.Result.Rows, dense3.Result.Cols);
Dense dense5(100, dense4.Result.Rows, dense4.Result.Cols);
Dense dense6(100, dense5.Result.Rows, dense5.Result.Cols);
Dense dense7(20, dense6.Result.Rows, dense6.Result.Cols);
Dense dense8(1, dense7.Result.Rows, dense7.Result.Cols, false);   // Bias value cannot be added to the output result in the last layer.
```

The size of the layer input depends on the output size of the previous layer. Batch Normalization layers are then created.

```ini
BatchNormalization batchNorm(dense.Result.Rows, dense.Result.Cols);
BatchNormalization batchNorm1(dense1.Result.Rows, dense1.Result.Cols);
BatchNormalization batchNorm2(dense2.Result.Rows, dense2.Result.Cols);
BatchNormalization batchNorm3(dense3.Result.Rows, dense3.Result.Cols);
BatchNormalization batchNorm4(dense4.Result.Rows, dense4.Result.Cols);
BatchNormalization batchNorm5(dense5.Result.Rows, dense5.Result.Cols);
BatchNormalization batchNorm6(dense6.Result.Rows, dense6.Result.Cols);
BatchNormalization batchNorm7(dense7.Result.Rows, dense7.Result.Cols);  
```

Batch Normalization layers are dependent on the output size of the dense layers to be applied. Then the weights of the dense and batchnormalization layers are loaded.
``` ini
std::string denseKernel = ".\\model_save_weight.h5_to_txt\\dense\\kernel.txt";
std::string denseBias = ".\\model_save_weight.h5_to_txt\\dense\\bias.txt";

dense.load(denseKernel, denseBias);
```
``` ini
std::string batchNormBeta = ".\\model_save_weight.h5_to_txt\\batch_normalization\\beta.txt";
std::string batchNormGamma = ".\\model_save_weight.h5_to_txt\\batch_normalization\\gamma.txt";
std::string batchNormMovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization\\moving_mean.txt";
std::string batchNormMovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization\\moving_variance.txt";

batchNorm.load(batchNormBeta, batchNormGamma, batchNormMovingMean, batchNormMovingVariance);
```
The then, ram memory is copied into the graphics card memory.
```ini
dense.host2Device();
...

batchNorm.host2Device();
...

inputImage.host2Device();
```

Next, ANN is created.

```ini
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
dense8.Result.device2Host();    // The output of the last layer is copied to ram memory so that you can see the result.
```

Finally the result value is read

```ini
float* variancePredict = (float*)dense8.Result.CpuP;
VarianceLbl->Text = variancePredict[0].ToString();
```

### How to use Keras model weights in the C environment ?
Keras weights are in hdf5 file format. It is converted to a text file for use with the C environment. You can do it as follows:

```ini
python h5_file_to_txt.py model_save_weight.h5
```

Each layer in the model will be saved in a folder and their weight in it. The text files will then be loaded into the model layers.

### Results

