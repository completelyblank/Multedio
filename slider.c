#include <iostream>
#include "slider.h"
#include "station.h"
using namespace std;

void drawSlider(Mat &image, int value) {
    	resize(image, image, Size(width*0.75, height*0.75));
        rectangle(image, Point(110, 300), Point(380, 320), Scalar(255, 255, 255), -1);
   	
    	// Draw the trackbar slider
    	line(image, Point(value, 290), Point(value, 330), Scalar(0, 0, 255), 2);
}

void onMouse(int event, int x, int y, int flags, void* userdata) {
	
}

void mouseCallBack() {
		drawSlider(background, sliderValue);
		if (mouseEvent == EVENT_LBUTTONDOWN) {
        		sliderValue += 5;
    		}
    		if(!clicked) {
    			return;
    		}
}
