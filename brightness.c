#include <opencv2/opencv.hpp>
#include <iostream>
#include "brightness.h"

using namespace cv;
using namespace std;

void adjustBrightness(Mat& imageInput, int sliderValue, int previous) {
	// Calculate image size
	cout << "previous: " << sliderValue << endl; 
	size_t imageSize = imageInput.total() * imageInput.elemSize();
    	double brightnessFactor = static_cast<double>(sliderValue - previous) / 100.0;

    	cout << "Brightness Factor: " << brightnessFactor << endl; // Debug print
    	Mat adjustedImage;
   	imageInput.convertTo(adjustedImage, -1, 1.0 + brightnessFactor, 0);
    	// Update shared memory with adjusted image
    	memcpy(ptr5, adjustedImage.data, imageSize);
}

void adjustBrightnessPreset(int sliderValue, int previous) {
	size_t imageSize = copyPresetImage.total() * copyPresetImage.elemSize();
    	double brightnessFactor = static_cast<double>(sliderValue - previous) / 100.0;

    	cout << "Brightness Factor: " << brightnessFactor << endl; // Debug print
   	copyPresetImage.convertTo(copyPresetImage, -1, 1.0 + brightnessFactor, 0);
}
