#include <iostream>
#include "slider.h"
#include "station.h"
#include "brightness.h"
using namespace std;

void drawSlider(Mat &image, int value) {
    	resize(image, image, Size(width*0.75, height*0.75));
        // Draw the rectangle with black border
        rectangle(image, Point(143, 310), Point(348, 330), Scalar(0, 0, 0), 2); 
        // Draw the rectangle with white interior
        rectangle(image, Point(145, 312), Point(345, 328), Scalar(255, 255, 255), -1); 
   	
    	// Draw the trackbar slider
    	rectangle(image, Point(145, 312), Point(value, 328), Scalar(128, 0, 128), -1);
}

void onMouse(int event, int x, int y, int flags, void* userdata) {
	
}

void *mouseCallBack(void *arg) {
    char *extracting = (char*)arg;

    // function name is separated by space from the index
    char name[15] = {'\0'};
    int i = 0;
    while (extracting[i] != ' ' && extracting[i] != '\0') {
        name[i] = extracting[i];
        i++;
    }

    //cout << "Extracted Name: " << name << endl;
    i++;
    int index = extracting[i] - '0';
    // Find the function in the map
    auto it = functionMap.find(name);
    if (it != functionMap.end()) {
        //pthread_mutex_lock(&threadMutex);
        while (true) {
        	cout << index << endl;
            if (clicked[0] == (index + 1)) {
                if (clicked[1]) {
                	clicked[1] = 0;
                    	*ptr3 = clicked[1];
                    	sliderValue[index] = ptr4[index];
                    	cout << sliderValue[index] << endl;
			image = imread(ptr6);
			//Mat image2(image.rows, image.cols, image.type(), ptr5); 
                    	it->second(image, sliderValue[index]);
                }
            } 
            usleep(1000);
        }
        //pthread_mutex_unlock(&threadMutex);
    } else {
        cout << "Function not found: " << name << endl;
    }

    return NULL;
}


void* testing(void *arg) {
	cout << "testing" << endl;
	
	return NULL;
}
