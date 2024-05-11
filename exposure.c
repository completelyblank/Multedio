#include <opencv2/opencv.hpp>
#include <iostream>
#include "exposure.h"

using namespace cv;
using namespace std;

void adjustExposure(Mat& imageInput, int sliderValue, int previous) {
	// Calculate image size
	size_t imageSize = imageInput.total() * imageInput.elemSize();
    	double exposureFactor = (sliderValue - previous) / 200.0; // Scale slider value to range -1.0 to 1.0
    	cout << "Exposure Factor: " << exposureFactor << endl; // Debug print
    	Mat adjustedImage;
   	imageInput.convertTo(adjustedImage, -1, 1.0 + exposureFactor, 0);
    	// Update shared memory with adjusted image
    	memcpy(ptr5, adjustedImage.data, imageSize);
}

void adjustExposurePreset(int sliderValue, int previous) {
	// Calculate image size
	size_t imageSize = copyPresetImage.total() * copyPresetImage.elemSize();
    	double exposureFactor = (sliderValue - previous) / 200.0; // Scale slider value to range -1.0 to 1.0
    	cout << "Exposure Factor: " << exposureFactor << endl; // Debug print
   	copyPresetImage.convertTo(copyPresetImage, -1, 1.0 + exposureFactor, 0);
}
