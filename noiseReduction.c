#include <opencv2/opencv.hpp>
#include <iostream>
#include "noiseReduction.h"

using namespace cv;
using namespace std;

void adjustNoise(Mat& imageInput, int sliderValue) {
    // Map slider value from range 145-345 to 0-100
    double mappedValue = ((sliderValue - 145) / 400.0) * 100.0;

    // Ensure slider value is odd for kernel size
    int kernelSize = (mappedValue < 1) ? 1 : static_cast<int>(mappedValue);

    // Apply noise reduction filter
    Mat adjustedImage;
    blur(imageInput, adjustedImage, Size(kernelSize, kernelSize));

    // Update shared memory with adjusted image
    size_t imageSize = adjustedImage.total() * adjustedImage.elemSize();
    memcpy(ptr5, adjustedImage.data, imageSize);
}
