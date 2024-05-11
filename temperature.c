#include <opencv2/opencv.hpp>
#include <iostream>
#include "temperature.h"

using namespace cv;
using namespace std;

void adjustTemperature(Mat& imageInput, int sliderValue, int previous) {
    // Calculate image size
    size_t imageSize = imageInput.total() * imageInput.elemSize();
    
    // Calculate temperature factor
    double temperatureFactor = (sliderValue - previous) / 200.0; // Scale slider value to range -1.0 to 1.0
    cout << "Temperature Factor: " << temperatureFactor << endl; // Debug print
    
    // Adjust temperature
    Mat adjustedImage = imageInput.clone(); // Create a copy to store the adjusted image
    if (temperatureFactor > 0.0) {
        // Increase the red and green channels for warmer temperature
        adjustedImage += Scalar(0, 255 * temperatureFactor, 255 * temperatureFactor);
    } else if (temperatureFactor < 0.0) {
        // Increase the blue channel for cooler temperature
        adjustedImage += Scalar(-255 * temperatureFactor, -255 * temperatureFactor, 0);
    }
    
    // Update shared memory with adjusted image
    memcpy(ptr5, adjustedImage.data, imageSize);
}

void adjustTemperaturePreset(int sliderValue, int previous) {
    // Calculate image size
    size_t imageSize = copyPresetImage.total() * copyPresetImage.elemSize();
    
    // Calculate temperature factor
    double temperatureFactor = (sliderValue - previous) / 200.0; // Scale slider value to range -1.0 to 1.0
    cout << "Temperature Factor: " << temperatureFactor << endl; // Debug print
    
    // Adjust temperature
    if (temperatureFactor > 0.0) {
        // Increase the red and green channels for warmer temperature
        copyPresetImage += Scalar(0, 255 * temperatureFactor, 255 * temperatureFactor);
    } else if (temperatureFactor < 0.0) {
        // Increase the blue channel for cooler temperature
        copyPresetImage += Scalar(-255 * temperatureFactor, -255 * temperatureFactor, 0);
    }
}

