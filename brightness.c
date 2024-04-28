#include <opencv2/opencv.hpp>
#include <iostream>
#include "brightness.h"

using namespace cv;
using namespace std;

void adjustBrightness(Mat& imageInput, int sliderValue) {
	// Calculate image size
	size_t imageSize = imageInput.total() * imageInput.elemSize();
    	double brightnessFactor = (sliderValue - 245) / 100.0; // Scale slider value to range -1.0 to 1.0
    	cout << "Brightness Factor: " << brightnessFactor << endl; // Debug print
    	Mat adjustedImage;
   	imageInput.convertTo(adjustedImage, -1, 1.0 + brightnessFactor, 0);
    	// Update shared memory with adjusted image
    	memcpy(ptr5, adjustedImage.data, imageSize);
}

