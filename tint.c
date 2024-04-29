#include <opencv2/opencv.hpp>
#include <iostream>
#include "tint.h"

using namespace cv;
using namespace std;

void adjustTint(Mat& imageInput, int sliderValue) {
    // Calculate image size
    size_t imageSize = imageInput.total() * imageInput.elemSize();

    // Scale slider value to range -1.0 to 1.0 for green and purple factors
    double greenFactor = (245 - sliderValue) / 200.0;
    double purpleFactor = (sliderValue - 245) / 200.0;

    // Debug print
    cout << "Green Factor: " << greenFactor << endl;
    cout << "Purple Factor: " << purpleFactor << endl;

    // Apply tint to the image
    Mat adjustedImage = imageInput.clone(); // Make a copy of the original image
    adjustedImage.forEach<Vec3b>([&](Vec3b& pixel, const int* position) {
        pixel[1] *= 1.0 + greenFactor; // Adjust green channel
        pixel[0] *= 1.0 + purpleFactor; // Adjust blue (assuming purple) channel
    });

    // Update shared memory with adjusted image
    memcpy(ptr5, adjustedImage.data, imageSize);
}


