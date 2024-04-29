#include "station.h"
#include "slider.h"
#include <pthread.h>
#include <iostream>
using namespace std;

bool filterFlags[9];

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
    	threadCreated = 0;
    	
    	for(int i = 0; i < 9; i++) {
    		filterFlags[i] = false;
    	}
    	
    	imageRender = false;
}

void station(int event, int x, int y, int flags, void* userdata) 
{
    	char *filename = (char*)userdata; //TypeCasting 
    	strcpy(ptr6, filename); //Ptr6 has filename ki value 
    	if(imageRender == false) //If Image has not been rendered 
    	{
    		image = imread(filename); //read the image 
    		size_t imageSize = image.total() * image.elemSize(); //allocate size to the image
    		memcpy(ptr5, image.data, imageSize); //copy into the memory 
    		imageRender = true; //now image shall be rendered
    	}
    	Mat image2(image.rows, image.cols, image.type(), ptr5); //image created which has allocation of number of rows, cols, type, and ptr5 ka object 
    	if (event == EVENT_MOUSEMOVE) //if the mouse moves
    	{
    		flag = "3"; //flag shall be 3
        	strcpy(ptr1, flag); //now ptr1 shall have flag ki val which is 3
    	}
    	if (event == EVENT_LBUTTONDOWN) //if the left mouse button is clicked 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl; //we write down coordinates for troubleshooting
    	}
    	
    	if (y > 148*scaledHeight && y < 220*scaledHeight) 
    	{
		if (x > 63*scaledWidth && x < 147*scaledHeight) { // temperature
			if (!clicked[0]) {
				background = hovering[0];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[0];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 1;
					*ptr2 = clicked[0];
				}
			}
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) { // tint
			if (!clicked[0]) {
				background = hovering[1];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[1];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 2;
					*ptr2 = clicked[0];
				}
			}
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) { // exposure
			if (!clicked[0]) {
				background = hovering[2];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[2];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 3;
					*ptr2 = clicked[0];
				}
			}
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else if (y > 264*scaledHeight && y < 334*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) { // crop
			if (!clicked[0]) {
				background = hovering[3];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[3];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 4;
					*ptr2 = clicked[0];
				}
			}
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) { // preset
			if (!clicked[0]) {
				background = hovering[4];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[4];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 5;
					*ptr2 = clicked[0];
				}
			}
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) { // noise reduction
			if (!clicked[0]) {
				background = hovering[5];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[5];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 6;
					*ptr2 = clicked[0];
				}
			}
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else if (y > 384*scaledHeight && y < 450*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) { // vignette
			if (!clicked[0]) {
				background = hovering[6];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[6];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 7;
					*ptr2 = clicked[0];
				}
			}
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) { // brightness
			if (!clicked[0]) {
				background = hovering[7];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[7];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 8;
					*ptr2 = clicked[0];
				}
			}
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) { // color grading
			if (!clicked[0]) {
				background = hovering[8];
				setCursor(gdk_get_default_root_window(), handCursor);
				if (event == EVENT_LBUTTONDOWN) {
					background = filters[8];
					setCursor(gdk_get_default_root_window(), arrowCursor);
					clicked[0] = 9;
					*ptr2 = clicked[0];
				}
			}
		} else {
			if (!clicked[0]) {
				background = imread("src/Station.png");
			}
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else {
		if (!clicked[0]) {
			background = imread("src/Station.png");
		}
		setCursor(gdk_get_default_root_window(), arrowCursor);
	}
	
	if(clicked[0]) {
		drawSlider(background, sliderValue[clicked[0] - 1]);
		if(x > 88*scaledWidth && x < 133*scaledWidth && y > 301*scaledHeight && y < 340*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				clicked[1] = 1;
				*ptr3 = clicked[1];
				if(sliderValue[clicked[0] - 1] > 145) {
					sliderValue[clicked[0] - 1] -= 5;
					ptr4[clicked[0] - 1] = sliderValue[clicked[0] - 1];
				}
			}
		}
		else if(x > 356*scaledWidth && x < 405*scaledWidth && y > 299*scaledHeight && y < 341*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				clicked[1] = 1;
				*ptr3 = clicked[1];
				if(sliderValue[clicked[0] - 1] < 345) {
					sliderValue[clicked[0] - 1] += 5;
					ptr4[clicked[0] - 1] = sliderValue[clicked[0] - 1];
				}
			}
		}
		else if (x > 52*scaledWidth && x < 92*scaledWidth && y > 143*scaledHeight && y < 182*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				setCursor(gdk_get_default_root_window(), arrowCursor);
				clicked[0] = 0;
				*ptr2 = clicked[0];
				slider = false;
			}
		}
		else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	}
	
	resize(background, background, Size(width*0.75, height*0.75));
	resize(image2, image2, Size(scaledWidth*470, scaledHeight*472));
	

	// Create a main window for displaying the result
    	Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255));

    	// Define the position to place the image on top of the background
    	int imageX = 520 * scaledWidth; // Adjust these values as needed
    	int imageY = 16 * scaledHeight; // Adjust these values as needed
    
        Rect imageROI(imageX, imageY, image2.cols, image2.rows);
        
        // Extract the region of interest from the background image
        Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));

        // Copy the background image to the main window
        background.copyTo(backgroundROI);

        // Place the image on top of the background
        Mat imageRegion = mainWindow(imageROI);
        image2.copyTo(imageRegion);

	// Show the result
    	imshow("Multedio", mainWindow);
}

void rendering() {
	char *names[9] = {"Temperature 0", "Tint 1", "Exposure 2", "Crop 3", "Preset 4", "Noise 5", "Vignette 6", "Brightness 7", "Color 8"};
	while (true) {
        	flag = (char*)(ptr1);
        	clicked[0] = *ptr2;
        	clicked[1] = *ptr3;
        	for(int i = 0; i < 9; i++) {
        		sliderValue[i] = ptr4[i];
        	}
        	if (strcmp(flag, "4") == 0) {
        		break;
        	}
        	//for(int i = 0; i < 9; i++) {
            		if(filterFlags[7] == false) {
                		pthread_create(&threadIDs[7], NULL, mouseCallBack, (void*)names[7]);
                		filterFlags[7] = true;
            		}
            		if(filterFlags[2] == false) {
                		pthread_create(&threadIDs[2], NULL, mouseCallBack, (void*)names[2]);
                		filterFlags[2] = true;
            		}
            		if(filterFlags[1] == false) {
                		pthread_create(&threadIDs[1], NULL, mouseCallBack, (void*)names[1]);
                		filterFlags[1] = true;
            		}
            		if(filterFlags[5] == false) {
                		pthread_create(&threadIDs[5], NULL, mouseCallBack, (void*)names[5]);
                		filterFlags[5] = true;
            		}
            		if(filterFlags[8] == false) {
                		pthread_create(&threadIDs[8], NULL, mouseCallBack, (void*)names[8]);
                		filterFlags[8] = true;
            		}
			if(filterFlags[6] == false) {
                		pthread_create(&threadIDs[6], NULL, mouseCallBack, (void*)names[6]);
                		filterFlags[6] = true;
            		}
        	//}
        	usleep(10000);
    	}
	//for(int i = 0; i < 9; i++) {
        	//if(filterFlags[i] == true) {
        		pthread_join(threadIDs[7], NULL);
        		pthread_join(threadIDs[2], NULL);
        		pthread_join(threadIDs[1], NULL);
        		pthread_join(threadIDs[5], NULL);
        		pthread_join(threadIDs[8], NULL);
			pthread_join(threadIDs[6], NULL);
        		//filterFlags[i] = false;
        	//}
        //}
}
