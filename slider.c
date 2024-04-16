#include <iostream>
#include "slider.h"
#include "station.h"
using namespace std;

void drawSlider(Mat &image, int value) {
    	resize(image, image, Size(width*0.75, height*0.75));
        rectangle(image, Point(140, 310), Point(350, 330), Scalar(255, 255, 255), -1);
   	
    	// Draw the trackbar slider
    	line(image, Point(value, 290), Point(value, 330), Scalar(0, 0, 255), 2);
}

void onMouse(int event, int x, int y, int flags, void* userdata) {
	
}

void mouseCallBack() {
		drawSlider(background, sliderValue);
    		if(!clicked) {
    			return;
    		}
}
