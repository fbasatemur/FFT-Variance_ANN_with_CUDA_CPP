# FFT-Variance_ANN_with_CUDA_CPP

Keras model weights are used in the CPP environment.

### Requirements
* Windows or Linux
* **CUDA == 10.2**: https://developer.nvidia.com/cuda-toolkit-archive
* **cuDNN == v8.0.2**: https://developer.nvidia.com/rdp/cudnn-archive
* **GPU with CC >= 3.0**: https://en.wikipedia.org/wiki/CUDA#GPUs_supported
* **on Linux GCC or Clang, on Windows MSVC 2017/2019**

### Features of the Keras model
* Dense Layer
* ReLu Activation
* Bach Normalization
* Sigmoid Activation

### ANN Model Design
![alt text](https://github.com/fbasatemur/FFT-Variance_ANN_with_CUDA_CPP/blob/master/doc/model_ANN.jpg)


Keras model consists of 9 Dense layers and 8 Batch Normalization layers. </br>
The model takes the vector of the Fast Fourier Transform image of 25x25 = 625 from the input. </br>
Output Layer consists of 1 neuron and returns the variance value.
```ini

dense = new Dense(100, 1, 625);                 // Dense(neurons, inputVector.Rows, inputVector.Cols, isEndlayer = false, isMemPin = false)
dense1 = new Dense(100, dense->Result);         // Each layer gets the result values of the previous layer
dense2 = new Dense(100, dense1->Result);
dense3 = new Dense(100, dense2->Result);
dense4 = new Dense(100, dense3->Result);
dense5 = new Dense(100, dense4->Result);
dense6 = new Dense(100, dense5->Result);
dense7 = new Dense(20, dense6->Result);
dense8 = new Dense(1, dense7->Result, true);   // Yeaaap, dense8 is end layer
```

The size of the layer input depends on the output size of the previous layer. Batch Normalization layers are then created.
```ini
batchNorm = new BatchNormalization(dense->Result);
batchNorm1 = new BatchNormalization(dense1->Result);
batchNorm2 = new BatchNormalization(dense2->Result);
batchNorm3 = new BatchNormalization(dense3->Result);
batchNorm4 = new BatchNormalization(dense4->Result);
batchNorm5 = new BatchNormalization(dense5->Result);
batchNorm6 = new BatchNormalization(dense6->Result);
batchNorm7 = new BatchNormalization(dense7->Result); 
```

Batch Normalization layers are dependent on the output size of the dense layers to be applied. </br>
Then the weights of the dense and batchnormalization layers are loaded.
``` ini
std::string denseKernel = ".\\model_save_weight.h5_to_txt\\dense\\kernel.txt";
std::string denseBias = ".\\model_save_weight.h5_to_txt\\dense\\bias.txt";
...
std::string dense8Kernel = ".\\model_save_weight.h5_to_txt\\dense_8\\kernel.txt";
std::string dense8Bias = ".\\model_save_weight.h5_to_txt\\dense_8\\bias.txt";

dense->Load(denseKernel, denseBias);
...
dense8->Load(dense8Kernel, dense8Bias);

```
``` ini
std::string batchNormBeta = ".\\model_save_weight.h5_to_txt\\batch_normalization\\beta.txt";
std::string batchNormGamma = ".\\model_save_weight.h5_to_txt\\batch_normalization\\gamma.txt";
std::string batchNormMovingMean = ".\\model_save_weight.h5_to_txt\\batch_normalization\\moving_mean.txt";
std::string batchNormMovingVariance = ".\\model_save_weight.h5_to_txt\\batch_normalization\\moving_variance.txt";
...
batchNorm.load(batchNormBeta, batchNormGamma, batchNormMovingMean, batchNormMovingVariance);
...
```

The then, ram memory is copied into the graphics card memory.
```ini
dense->Host2Device();
...

batchNorm->Host2Device();
...

```

After the inputs to be given to ANN are determined, the inputs should be given to ANN. </br>
The inputs must be of type CpuGpuMat to be able to export to ANN. </br>
Result variable of the last layer must be given in order to get the predict results.
```ini
CpuGpuMat inputBuffer(inputs, 1, 625, number_of_samples, true);     // (neurons, inputVector.Rows, inputVector.Cols, isMemPin = true)
CpuGpuMat outputBuffer(dense8->Result, number_of_samples);
```
Memory pinning (isMemPin = true) speeds up memory transfer. However, 1 MB or more is recommended. You can look [**here**](https://developer.nvidia.com/blog/how-optimize-data-transfers-cuda-cc/) for more.
inputs to ANN will be given using "inputBuffer"; outputs will be taken using "outputBuffer". </br>
Next, ANN is created. Iteration is made as much as the "number_of_samples" to be given to ANN.
```ini
dense->Apply(&inputBuffer, i);       // In every iteration "i" must be increased by one
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

dense8->Apply(&dense7->Result, 0, i);   // In every iteration "i" must be increased by one
gpuSigmoid(&dense8->Result, i);         
```

"outputBuffer" is copied to ram memory so that you can see the result.
```ini
outputBuffer.Device2Host();
```

Finally the result value is read. There output value as much as "number_of_samples"
```ini
float* predicts = (float*)outputBuffer.CpuP;
VarianceLbl->Text = predicts[0].ToString();
```

### How to use Keras model weights in the C environment ?
Keras weights are in hdf5 file format. I assume you got the model record as .json and .h5. 

```ini
# keras library import  for Saving and loading model and weights

from keras.models import model_from_json
from keras.models import load_model

# serialize model to JSON
#  the keras model which is trained is defined as 'model' in this example
model_json = model.to_json()

with open("model_save_json.json", "w") as json_file:
    json_file.write(model_json)

# serialize weights to HDF5
model.save_weights("model_save_weight.h5")
```

It is converted to a text file for use with the C environment. You can do it as follows:

```ini
python h5_file_to_txt.py model_save_weight.h5
```

Each layer in the model will be saved in a folder and their weight in it. The text files will then be loaded into the model layers.

## Results

### Blurry

![alt text](https://github.com/fbasatemur/FFT-Variance_ANN_with_CUDA_CPP/blob/master/doc/ss_blurry.jpg)

### Clear

![alt text](https://github.com/fbasatemur/FFT-Variance_ANN_with_CUDA_CPP/blob/master/doc/ss_clear.jpg)

### Multiple Images
**The values predicted by the model for more than one image can be observed from the graph.**

![alt text](https://github.com/fbasatemur/FFT-Variance_ANN_with_CUDA_CPP/blob/master/doc/ss_multi_1.jpg)

### Multiple Images

![alt text](https://github.com/fbasatemur/FFT-Variance_ANN_with_CUDA_CPP/blob/master/doc/ss_multi_2.jpg)
