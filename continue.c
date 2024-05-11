#include <opencv2/opencv.hpp>
#include <iostream>
#include "continue.h"
#include "preset.h"
#include "upload.h"

using namespace cv;
using namespace std;

void continueYN(int event, int x, int y, int flags, void* userdata) {
	backgroundCode();
	initializeCursors();
	background = imread("src/Preset_Applied.jpg");
	if (event == EVENT_LBUTTONDOWN) 
    	{
    		cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}
    	if (x > 271*scaledWidth && x < 610*scaledWidth && y > 36*scaledHeight && y < 158*scaledHeight) 
    	{	
    		setCursor(gdk_get_default_root_window(), handCursor);
    		if (event == EVENT_LBUTTONDOWN) {
    			*ptr7 = 11;
    			imageRender = false;
    			setMouseCallback("Multedio", upload, NULL);
    		}
    	} 
    	else if (x > 627*scaledWidth && x < 845*scaledWidth && y > 267*scaledHeight && y < 384*scaledHeight)
    	{
    		setCursor(gdk_get_default_root_window(), handCursor);
    		if (event == EVENT_LBUTTONDOWN) {
    			*ptr7 = 10;
    			destroyWindow("Multedio");
    		}
    	}
    	else //if cursor not on button
    	{
        	setCursor(gdk_get_default_root_window(), arrowCursor);
    	}
	
	show(background);
}

void continueFunc() {
	while (true) {
        	pthread_mutex_lock(&threadMutex);
        	int ending = *ptr7;
        	if(ending == 10) {
        		exit(1);
        	} else if(ending == 11) {
        		pthread_mutex_unlock(&threadMutex);
        		break;
        	}
        	pthread_mutex_unlock(&threadMutex);
        	usleep(1000000);
    	}
    	strcpy(ptr1, "2");
    	uploadOther();
}
