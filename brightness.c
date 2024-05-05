#include <opencv2/opencv.hpp>
#include <iostream>
#include "brightness.h"

using namespace cv;
using namespace std;

void adjustBrightness(Mat& imageInput, int sliderValue, int previous) {
	// Calculate image size
	cout << "previous: " << sliderValue << endl; 
	size_t imageSize = imageInput.total() * imageInput.elemSize(); //every element * the size of the individual elements
    	double brightnessFactor = static_cast<double>(sliderValue - previous) / 100.0; //factor to get value of slider

    	cout << "Brightness Factor: " << brightnessFactor << endl; // Debug print
    	Mat adjustedImage; //data structure to hold the new image that will be returned
   	imageInput.convertTo(adjustedImage, -1, 1.0 + brightnessFactor, 0); //image gets brightness slider values
    	// Update shared memory with adjusted image
    	memcpy(ptr5, adjustedImage.data, imageSize); //copy the adjusted image to the pointer of the image that will be reflected 
}

void adjustBrightnessPreset(int sliderValue, int previous) {
	size_t imageSize = copyPresetImage.total() * copyPresetImage.elemSize(); ///every element * the size of the individual elements
    	double brightnessFactor = static_cast<double>(sliderValue - previous) / 100.0; //factor to get value of slider

    	cout << "Brightness Factor: " << brightnessFactor << endl; // Debug print
   	copyPresetImage.convertTo(copyPresetImage, -1, 1.0 + brightnessFactor, 0); //image gets brightness preset values
}
