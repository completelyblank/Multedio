#include <opencv2/opencv.hpp>
#include <iostream>
#include "tint.h"

using namespace cv;
using namespace std;

void adjustTint(Mat& imageInput, int sliderValue, int previous) {
    size_t imageSize = imageInput.total() * imageInput.elemSize();

    // Scale slider value to range -1.0 to 1.0 for green and purple factors
    double greenFactor = (previous - sliderValue) / 400.0;
    double purpleFactor = (previous - sliderValue) / 400.0;

    // Debug print
    cout << "Green Factor: " << greenFactor << endl;
    cout << "Purple Factor: " << purpleFactor << endl;

    // Apply tint to the image
    Mat adjustedImage = imageInput.clone(); // Make a copy of the original image
    adjustedImage.forEach<Vec3b>([&](Vec3b& pixel, const int* position) {
        pixel[1] = saturate_cast<uchar>(pixel[1] * (1.0 - greenFactor)); // Adjust green channel //RIGHT PEI GREEN KAREGA
        pixel[0] = saturate_cast<uchar>(pixel[0] * (1.0 + purpleFactor)); // Adjust blue (assuming purple) channel //LEFT PEI PURPLE
    });
    

    // Update shared memory with adjusted image
    memcpy(ptr5, adjustedImage.data, imageSize);
}

void adjustTintPreset(int sliderValue, int previous) {
    size_t imageSize = copyPresetImage.total() * copyPresetImage.elemSize();

    // Scale slider value to range -1.0 to 1.0 for green and purple factors
    double greenFactor = (previous - sliderValue) / 400.0;
    double purpleFactor = (previous - sliderValue) / 400.0;

    // Debug print
    cout << "Green Factor: " << greenFactor << endl;
    cout << "Purple Factor: " << purpleFactor << endl;

    copyPresetImage.forEach<Vec3b>([&](Vec3b& pixel, const int* position) {
        pixel[1] = saturate_cast<uchar>(pixel[1] * (1.0 - greenFactor)); // Adjust green channel //RIGHT PEI GREEN KAREGA
        pixel[0] = saturate_cast<uchar>(pixel[0] * (1.0 + purpleFactor)); // Adjust blue (assuming purple) channel //LEFT PEI PURPLE
    });
}
