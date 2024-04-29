#include <opencv2/opencv.hpp>
#include <iostream>
#include "colorGrading.h"

using namespace cv;
using namespace std;

void adjustColorGrading(Mat& imageInput, int sliderValue) {
    // Calculate image size
    size_t imageSize = imageInput.total() * imageInput.elemSize();

    // Convert the input image to LAB color space
    Mat labImage;
    cvtColor(imageInput, labImage, COLOR_BGR2Lab);

    // Split the LAB image into channels
    vector<Mat> labChannels;
    split(labImage, labChannels);

    // Normalize slider value to range [-50, 50]
    double normalizedSliderValue = (static_cast<double>(sliderValue - 245) / 200.0) * 100.0;

    // Define factors to adjust specific colors
    double yellowFactor = 0.0;  // adjust yellow
    double orangeFactor = 0.0;  // adjust orange
    double redFactor = 0.0;     // adjust red
    double blueFactor = 0.0;    // adjust blue

    // Modify the factors based on the slider value
    if (normalizedSliderValue > 0 && normalizedSliderValue <= 50) {
        yellowFactor = normalizedSliderValue;
        orangeFactor = normalizedSliderValue; // Adding orange to the left
    } else if (normalizedSliderValue > 50 && normalizedSliderValue <= 100) {
        orangeFactor = normalizedSliderValue; // Adding orange to the left
        blueFactor = normalizedSliderValue - 50; // Adding blue to the right
    } else if (normalizedSliderValue < 0 && normalizedSliderValue >= -50) {
        blueFactor = -normalizedSliderValue; // Adding blue to the right
    } else if (normalizedSliderValue < -50 && normalizedSliderValue >= -100) {
        redFactor = -normalizedSliderValue; // Adding red to the right
        blueFactor = -normalizedSliderValue; // Adding blue to the right
    }

    // Adjust the 'a' channel to control yellow-orange color
    labChannels[1] += yellowFactor;
    labChannels[1] += orangeFactor;

    // Adjust the 'b' channel to control blue-yellow color
    labChannels[2] += blueFactor;
    labChannels[2] -= redFactor;

    // Merge the LAB channels back into a single image
    merge(labChannels, labImage);

    // Convert the LAB image back to BGR color space
    Mat adjustedImage;
    cvtColor(labImage, adjustedImage, COLOR_Lab2BGR);

    // Update shared memory with adjusted image
    memcpy(ptr5, adjustedImage.data, imageSize);
}
