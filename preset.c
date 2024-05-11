#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <sstream>
#include <string>
#include "preset.h"

using namespace cv;
using namespace std;

string outputDirectory = "My Edits";
const int NUM_ROWS = 5;
const int NUM_COLS = 7;
int x = 1;
pthread_mutex_t imagesMutex = PTHREAD_MUTEX_INITIALIZER;

void adjustPreset(Mat& imageInput, int sliderVal, int previous) {
	cout << sliderVal << endl;
	size_t imageSize = imageInput.total() * imageInput.elemSize();
	int i = sliderVal;
	// Open the CSV file
    	ifstream file("presets.csv");
    
    	int columns[NUM_COLS][NUM_ROWS];
    	
    	string line;
   	int rowIndex = 0;
    	while (getline(file, line)) {
        	// Create a string stream from the line
        	stringstream ss(line);
        	int value;
        	int columnIndex = 0;

        	// Read each value from the line and store in corresponding column array
        	while (ss >> value) {
            		columns[columnIndex++][rowIndex] = value;
            		// Skip whitespace and commas
            		ss.ignore();
        	}
        	++rowIndex;
    	}
    	
    	file.close();
    	
    	copyPresetImage = presetImage.clone();
    		
    	adjustBrightnessPreset(columns[0][i], 245);	
    	adjustExposurePreset(columns[1][i], 245);
    	adjustTintPreset(columns[2][i], 245);
    	adjustTemperaturePreset(columns[3][i], 245);
    	adjustColorGradingPreset(columns[4][i], 245);
    	adjustNoisePreset(columns[5][i], 145);
    	adjustVignette(copyPresetImage, columns[6][i], 145);
}

void adjustPresetBatch(Mat& imageInput, int sliderVal, int previous) {
	size_t imageSize = imageInput.total() * imageInput.elemSize();
	int i = sliderVal;
	// Open the CSV file
    	ifstream file("presets.csv");
    
    	int columns[NUM_COLS][NUM_ROWS];
    	
    	string line;
   	int rowIndex = 0;
    	while (getline(file, line)) {
        	// Create a string stream from the line
        	stringstream ss(line);
        	int value;
        	int columnIndex = 0;

        	// Read each value from the line and store in corresponding column array
        	while (ss >> value) {
            		columns[columnIndex++][rowIndex] = value;
            		// Skip whitespace and commas
            		ss.ignore();
        	}
        	++rowIndex;
    	}
    	
    	file.close();
    	
    	copyPresetImage = imageInput.clone();
    		
    	adjustBrightnessPreset(columns[0][i], 245);	
    	adjustExposurePreset(columns[1][i], 245);
    	adjustTintPreset(columns[2][i], 245);
    	adjustTemperaturePreset(columns[3][i], 245);
    	adjustColorGradingPreset(columns[4][i], 245);
    	adjustNoisePreset(columns[5][i], 145);
    	adjustVignettePreset(columns[6][i], 145);
}

void* apply(void *arg) {
    int value = *(int*)arg;
    while (true) {
        if (!images.empty()) {
            // Adjust the preset image
            if (value == x - 1) {
            	Mat imageToEdit = images.front();
            	images.pop();
                adjustPresetBatch(imageToEdit, pBIndex - 1, 0);
                imageToEdit = copyPresetImage;
                // Construct the file path for saving the image
                string filename = outputDirectory + "/image_" + to_string(x) + ".jpg";
                // Save the image to the file
                imwrite(filename, imageToEdit);
                cout << "Image saved: " << filename << endl;
                x++;
                cout << x << endl;
            }
        } else {
           break;
        }
        usleep(1000000);
    }
    *ptr7 = 9;
    return NULL;
}

