#include <opencv2/opencv.hpp>
#include <iostream>
#include "crop.h"

using namespace cv;
using namespace std;

void adjustCrop(Mat& imageInput, int sliderValue, int previous) {
	// Store the original size
    	Size originalSize = imageInput.size();

    	// Perform cropping
    	Mat croppedImage = imageInput(Range(0 + (sliderValue - previous), imageInput.rows - (sliderValue - previous)), Range(0 + (sliderValue - previous), imageInput.cols- (sliderValue - previous)));

    	// Resize cropped image back to original size
    	resize(croppedImage, croppedImage, originalSize);

    	// Update shared memory with adjusted image
    	size_t imageSize = croppedImage.total() * croppedImage.elemSize();
    	memcpy(ptr5, croppedImage.data, imageSize);
}

