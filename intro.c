#include "intro.h"
#include "station.h"
#include "upload.h"
#include "getStarted.h"
#include <fcntl.h>
#include <iostream>
#include "preset.h"
#include "crop.h"
#include "batch.h"

using namespace std;

void initializeCursors() {
	// Initialize GdkCursor variables
    	handCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "pointer");
    	arrowCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "default");
    	watchCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "watch");
}

void backgroundCode() {
	// Get the default screen
	GdkScreen *screen = gdk_screen_get_default();

	// Get screen width and height
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);
	scaledWidth = width / 1366;
	scaledHeight = height / 675;
}

void show(Mat background) {
	if(!background.empty()) {
		resize(background, background, Size(width*0.75, height*0.75));
    		Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255));
    		Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));
    		background.copyTo(backgroundROI);
    		imshow("Multedio", mainWindow);
	} else {
		cout << "Failed to load\n";
	}
}



void setCursor(GdkWindow *window, GdkCursor *cursor) //cursor event 
{
	gdk_window_set_cursor(window, cursor);
}



void mainWindow() {
    	backgroundCode();
	clicked[0] = 0;
    	clicked[1] = 0;
    	slider = false;
    	dragging = false;
   	for(int i = 0; i < 9; i++) //9 Feautures 9 Sliders
   	{
    		sliderValue[i] = 145;
    		ptr4[i] = sliderValue[i];
    	}
    	
    	for(int i = 0; i < 3; i++) 
    	{
    		sliderValue[i] = 245;
    		ptr4[i] = sliderValue[i];
    	}
    	
    	sliderValue[7] = 245;
    	ptr4[7] = sliderValue[7];
    
    	sliderValue[8] = 245;
    	ptr4[8] = sliderValue[8];
    
    	initializeCursors();
    	initializeHoveringPNGs();
    	initializeBatchHovering();

    	background = imread("src/Intro.jpg");
    	show(background);
    	setMouseCallback("Multedio", getStarted, NULL);

    	// Keep the main loop running
    	gtk_main();

}


void mainOther() {
	functionMap = {
	        {"Brightness", adjustBrightness},
	        {"Exposure", adjustExposure},
	        {"Tint", adjustTint},
	        {"Vignette", adjustVignette},
	        {"Noise", adjustNoise},
	        {"Color", adjustColorGrading},
	        {"Crop", adjustCrop},
	        {"Temperature", adjustTemperature},
	        {"Preset", adjustPreset}
	};
	clicked[0] = 0;
    	clicked[1] = 0;
    while (true) {
        pthread_mutex_lock(&threadMutex);
        flag = (char*)(ptr1);
        printf("%s\n", flag); 
        if (strcmp(flag, "1") == 0) {
            pthread_mutex_unlock(&threadMutex);
            break;
        }
        pthread_mutex_unlock(&threadMutex);
        cout << "Other" << endl;
        usleep(1000000);
    }
    getOther();
 
}
