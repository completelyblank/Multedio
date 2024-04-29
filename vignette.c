#include <opencv2/opencv.hpp>
#include <iostream>
#include "vignette.h"

using namespace cv;
using namespace std;

void adjustVignette(Mat& imageInput, int sliderValue) {
    double strength = static_cast<double>(sliderValue - 145) / 200;
    size_t imageSize = imageInput.total() * imageInput.elemSize();

    // Calculate the center of the image
    Point center = Point(imageInput.cols / 2, imageInput.rows / 2);

    // Calculate the maximum distance from the center to the corners of the image
    double maxDistance = sqrt(pow(center.x, 2) + pow(center.y, 2));

    // Create a mask with the same size as the input image
    Mat mask = Mat::zeros(imageInput.size(), CV_8U);

    // Create a white circle (vignette mask) with a gradually decreasing intensity towards the edges
    for (int y = 0; y < imageInput.rows; ++y) {
        for (int x = 0; x < imageInput.cols; ++x) {
            // Calculate distance from the center
            double distance = sqrt(pow(x - center.x, 2) + pow(y - center.y, 2));

            // Calculate intensity based on distance (linear interpolation)
            double intensity = 255 - (255 * distance / maxDistance * strength);

            // Ensure intensity is in the range [0, 255]
            intensity = max(0.0, min(255.0, intensity));

            // Ensure intensity remains in the range [0, 255] after lightening
            intensity = min(255.0, intensity);

            // Set pixel intensity in the mask
            mask.at<uchar>(y, x) = static_cast<uchar>(intensity);
        }
    }

    // Convert mask to match the number of channels of the image
    Mat convertedMask;
    cvtColor(mask, convertedMask, COLOR_GRAY2BGR);

    // Apply the vignette effect by blending the image with the mask
    Mat result;
    multiply(imageInput, convertedMask, result, 1.0 / 255); // Divide by 255 to normalize mask values

    // Update the shared memory with the adjusted image
    memcpy(ptr5, result.data, imageSize);
}

