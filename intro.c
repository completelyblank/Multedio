#include "intro.h"
#include "station.h"
#include "upload.h"
#include "getStarted.h"
#include <iostream>

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
	gtk_init(NULL, NULL);

	backgroundCode();
    	
    	initializeCursors();
    	initializeHoveringPNGs();
    	
    	background = imread("src/Multedio.png");  //reads image called Multedio.png from src directory and saves in variable
    	show(background);
    	setMouseCallback("Multedio", getStarted, nullptr); //uses callback function from intro.h on Multedio

    	waitKey(0); //waits for user interaction
}
