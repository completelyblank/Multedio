#include "station.h"
#include <iostream>
using namespace std;

void initializeHoveringPNGs() {
	// load assets
    	hovering[0] = imread("src/Temperature_Hover.png");
    	hovering[1] = imread("src/Tint_Hover.png");
    	hovering[2] = imread("src/Exposure_Hover.png");
    	hovering[3] = imread("src/Crop_Hover.png");
    	hovering[4] = imread("src/Preset_Hover.png");
    	hovering[5] = imread("src/Noise_R_Hover.png");
    	hovering[6] = imread("src/Vignette_Hover.png");
    	hovering[7] = imread("src/Brightness_Hover.png");
    	hovering[8] = imread("src/Color_Manipulation_Hover.png");
    	
    	filters[0] = imread("src/Temperature.png");
    	filters[1] = imread("src/Tint.png");
    	filters[2] = imread("src/Exposure.png");
    	filters[3] = imread("src/Crop.png");
    	filters[4] = imread("src/Preset.png");
    	filters[5] = imread("src/Noise Reduction.png");
    	filters[6] = imread("src/Vignette.png");
    	filters[7] = imread("src/Brightness.png");
    	filters[8] = imread("src/Color Grading.png");
}

void station(int event, int x, int y, int flags, void* userdata) {
	// Load the background image
	static Mat background = imread("src/Station.png");
    	char *filename = (char*)userdata;
    	Mat image = imread(filename);
    	if (event == EVENT_LBUTTONDOWN) 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}
    	
    	if (y > 148*scaledHeight && y < 220*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) {
			if (!clicked) {
				background = hovering[0];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[0];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) {
			if (!clicked) {
				background = hovering[1];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[1];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) {
			if (!clicked) {
				background = hovering[2];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[2];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else if (y > 264*scaledHeight && y < 334*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) {
			if (!clicked) {
				background = hovering[3];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[3];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) {
			if (!clicked) {
				background = hovering[4];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[4];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) {
			if (!clicked) {
				background = hovering[5];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[5];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else if (y > 384*scaledHeight && y < 450*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) {
			if (!clicked) {
				background = hovering[6];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[6];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) {
			if (!clicked) {
				background = hovering[7];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[7];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) {
			if (!clicked) {
				background = hovering[8];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[8];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked = true;
				}
			}
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else {
		setCursor(gdk_get_default_root_window(), arrowCursor);
	}
	
	if (x > 52*scaledWidth && x < 92*scaledWidth && y > 143*scaledHeight && y < 182*scaledHeight && clicked == true) {
		setCursor(gdk_get_default_root_window(), handCursor);
		if (event == EVENT_LBUTTONDOWN) {
			setCursor(gdk_get_default_root_window(), arrowCursor);
			clicked = false;
		}
	}
	
	resize(background, background, Size(width*0.75, height*0.75));
	resize(image, image, Size(470*scaledWidth, 472*scaledHeight));

	// Create a main window for displaying the result
    	Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255));

    	// Define the position to place the image on top of the background
    	float imageX = 520*scaledWidth; // Adjust these values as needed
    	float imageY = 16*scaledHeight; // Adjust these values as needed
    
        Rect imageROI(imageX, imageY, image.cols, image.rows);
        
        // Extract the region of interest from the background image
        Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));

        // Copy the background image to the main window
        background.copyTo(backgroundROI);

        // Place the image on top of the background
        Mat imageRegion = mainWindow(imageROI);
        image.copyTo(imageRegion);

	// Show the result
    	imshow("Multedio", mainWindow);
}
