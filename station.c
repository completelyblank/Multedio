#include "station.h"
#include "slider.h"
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <filesystem>
#include "preset.h"
#include <stack>

namespace fs = std::filesystem;
using namespace std;

bool filterFlags[9];
Mat presetBackgrounds[6];
int pIndex = 0;
stack<Mat> undo;
stack<Mat> redo;
bool toUndo = false;
int undoCount = 0;
stack<int> sliderUndo;
stack<int> indexUndo;
bool once = false;
bool toRedo;
int redoCount = 0;
stack<int> sliderRedo;
stack<int> indexRedo;

void initializeHoveringPNGs() {
	// load assets
    	hovering[0] = imread("src/Temperature_Hover.jpg");
    	hovering[1] = imread("src/Tint_Hover.jpg");
    	hovering[2] = imread("src/Exposure_Hover.jpg");
    	hovering[3] = imread("src/Crop_Hover.jpg");
    	hovering[4] = imread("src/Preset_Hover.jpg");
    	hovering[5] = imread("src/Noise_R_Hover.jpg");
    	hovering[6] = imread("src/Vignette_Hover.jpg");
    	hovering[7] = imread("src/Brightness_Hover.jpg");
    	hovering[8] = imread("src/Color_Manipulation_Hover.jpg");
    	
    	filters[0] = imread("src/Temperature.jpg");
    	filters[1] = imread("src/Tint.jpg");
    	filters[2] = imread("src/Exposure.jpg");
    	filters[3] = imread("src/Crop.jpg");
    	filters[4] = imread("src/Preset.jpg");
    	filters[5] = imread("src/Noise Reduction.jpg");
    	filters[6] = imread("src/Vignette.jpg");
    	filters[7] = imread("src/Brightness.jpg");
    	filters[8] = imread("src/Color Grading.jpg");
    	
    	for(int i = 0; i < 9; i++) {
    		filterFlags[i] = false;
    	}
    	
    	imageRender = false;
    	
    	presetBackgrounds[0] = imread("src/click.jpg");
    	presetBackgrounds[1] = imread("src/Ahraz.jpg");
    	presetBackgrounds[2] = imread("src/Musha.jpg");
    	presetBackgrounds[3] = imread("src/Zehabia.jpg");
    	presetBackgrounds[4] = imread("src/Falfizz.jpg");
    	presetBackgrounds[5] = imread("src/Siamese.jpg");
}

void station(int event, int x, int y, int flags, void* userdata) {
    	char *filename = (char*)userdata;
    	strcpy(ptr6, filename);
    	if(imageRender == false) {
    		image = imread(filename);
    		presetImage = imread(ptr6);
    		size_t imageSize = image.total() * image.elemSize();
    		memcpy(ptr5, image.data, imageSize);
    		imageRender = true;
    		undo.push(image);
    		
    	}
    	Mat image2(image.rows, image.cols, image.type());
	memcpy(image2.data, ptr5, image2.total() * image2.elemSize());	
    	if (event == EVENT_MOUSEMOVE) 
    	{
    		flag = "3";
        	strcpy(ptr1, flag);
    	}
    	if (event == EVENT_LBUTTONDOWN) 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}
    	
    	if(x > 235*scaledWidth && x < 262*scaledWidth && y > 32*scaledHeight && y < 57*scaledHeight) { // save
    		setCursor(gdk_get_default_root_window(), handCursor);
    		if (event == EVENT_LBUTTONDOWN) {
    			mkdir("My Edits", 0777);
    			string filenameStr(filename); 
    			filenameStr = fs::path(filenameStr).filename();
    			string newFilename = "My Edits/" + filenameStr + "_edit.png"; // Concatenate strings
    			cout << newFilename << endl;
            		imwrite(newFilename, image2);
            	}
        } else if (x > 125*scaledWidth && x < 160*scaledWidth && y > 34*scaledHeight && y < 58*scaledHeight) { // undo
        	setCursor(gdk_get_default_root_window(), handCursor);
        	if (event == EVENT_LBUTTONDOWN) {
			if(undoCount > 0) {
				redo.push(undo.top());
				redoCount++;
				undo.pop();
				Mat topImage = undo.top();
				memcpy(ptr5, topImage.data, topImage.total() * topImage.elemSize());	
				undoCount--;
				cout << "popped undo" << endl;
				cout << "Index: " << indexUndo.top() << " Slider: " << sliderUndo.top() << endl;
				if(indexUndo.top() == 5) {
					pIndex = sliderUndo.top();
				} else {
					sliderValue[indexUndo.top() - 1] = sliderUndo.top();
				}
				ptr4[indexUndo.top() - 1] = sliderValue[indexUndo.top() - 1];
				sliderUndo.pop();
				indexUndo.pop();
				*ptr7 = 1;
			}
		}
       
        } else if (x > 330*scaledWidth && x < 372*scaledWidth && y > 34*scaledHeight && y < 58*scaledHeight) { // redo
        	setCursor(gdk_get_default_root_window(), handCursor);
        	if (event == EVENT_LBUTTONDOWN) {
        		if(redoCount > 0) {
        			undoCount++;
        			cout << "stack size: " << redo.size() << endl;
				Mat topImage = redo.top();
				undo.push(topImage);
				redo.pop();
				memcpy(ptr5, topImage.data, topImage.total() * topImage.elemSize());	
				redoCount--;
				cout << "popped redo" << endl;
				cout << "slider stack size: " << sliderRedo.size() << " index stack size: " << indexRedo.size() << endl;
				cout << "Index: " << indexRedo.top() << " Slider: " << sliderRedo.top() << endl;
				sliderUndo.push(sliderValue[indexRedo.top() - 1]);
				indexUndo.push(indexRedo.top());
				ptr4[indexRedo.top() - 1] = sliderRedo.top();
				cout << sliderRedo.top() << endl;
				sliderRedo.pop();
				indexRedo.pop();
				*ptr7 = 1;
        		}
        	}
	} else if (y > 148*scaledHeight && y < 220*scaledHeight) {
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
					background = presetBackgrounds[pIndex];
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
				background = imread("src/Station.jpg");
			}
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else {
		if (!clicked[0]) {
			background = imread("src/Station.jpg");
		}
		setCursor(gdk_get_default_root_window(), arrowCursor);
	}
	
	if(clicked[0] && clicked[0] != 5) {
		if(!once) {
			sliderUndo.push(sliderValue[clicked[0] - 1]);
			indexUndo.push(clicked[0]);
			once = true;
		}
		if(ptr4[3] == 145) {
			sliderValue[3] = 145;
		}
		drawSlider(background, sliderValue[clicked[0] - 1]);
		if(x > 88*scaledWidth && x < 133*scaledWidth && y > 301*scaledHeight && y < 340*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				clicked[1] = 1;
				*ptr3 = clicked[1];
				if(sliderValue[clicked[0] - 1] > 145) {
					sliderValue[clicked[0] - 1] -= 5;
					ptr4[clicked[0] - 1] = sliderValue[clicked[0] - 1];
					toUndo = true;
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
					toUndo = true;
				}
			}
		}
		else if (x > 52*scaledWidth && x < 92*scaledWidth && y > 143*scaledHeight && y < 182*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				setCursor(gdk_get_default_root_window(), arrowCursor);
				indexRedo.push(clicked[0]);
				sliderRedo.push(ptr4[clicked[0] - 1]);
				clicked[0] = 0;
				*ptr2 = clicked[0];
				slider = false;
				if(toUndo) {
					undo.push(image2);
					undoCount++;
					cout << "pushed undo" << endl;
					cout << "Values saved:\nIndex: " << indexUndo.top() << endl << "Slider Value: " << sliderUndo.top() << endl;
				} else {
					sliderUndo.pop();
					indexUndo.pop();
					indexRedo.pop();
					sliderRedo.pop();
				}
				toUndo = false;
				once = false;
			}
		}
		else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else if (clicked[0] && clicked[0] == 5) {
		if(!once) {
			sliderUndo.push(pIndex);
			indexUndo.push(clicked[0]);
			once = true;
		}
		if(x > 88*scaledWidth && x < 133*scaledWidth && y > 301*scaledHeight && y < 340*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				clicked[1] = 1;
				*ptr3 = clicked[1];
				if(pIndex > 1) {
					pIndex--;
					background = presetBackgrounds[pIndex];
					adjustPreset(image2, pIndex - 1, 0);
					toUndo = true;
				}
			}
		}
		else if(x > 356*scaledWidth && x < 405*scaledWidth && y > 299*scaledHeight && y < 341*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				clicked[1] = 1;
				*ptr3 = clicked[1];
				if(pIndex < 5) {
					pIndex++;
					background = presetBackgrounds[pIndex];
					adjustPreset(image2, pIndex - 1, 0);
					toUndo = true;
				}
			}
		}
		else if (x > 52*scaledWidth && x < 92*scaledWidth && y > 143*scaledHeight && y < 182*scaledHeight){
			setCursor(gdk_get_default_root_window(), handCursor);
			if (event == EVENT_LBUTTONDOWN) {
				setCursor(gdk_get_default_root_window(), arrowCursor);
				indexRedo.push(clicked[0]);
				clicked[0] = 0;
				*ptr2 = clicked[0];
				slider = false;
				if(toUndo) {
					undo.push(image2);
					cout << "pushed undo" << endl;
					undoCount++;
					cout << "Values saved:\nIndex: " << indexUndo.top() << endl << "Slider Value: " << sliderUndo.top() << endl;
					sliderRedo.push(pIndex);
				} else {
					sliderUndo.pop();
					indexUndo.pop();
					indexRedo.pop();
				}
				toUndo = false;
				once = false;
			}
		}
		else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	}
	
	resize(background, background, Size(width*0.75, height*0.75));
	resize(image2, image2, Size(470*scaledWidth, 472*scaledHeight));

	// Create a main window for displaying the result
    	Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255));

    	// Define the position to place the image on top of the background
    	int imageX = scaledWidth*520; // Adjust these values as needed
    	int imageY = scaledHeight*16; // Adjust these values as needed
    
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
	*ptr7 = 0;
	for(int i = 0; i < 9; i++) 
   	{
    		previous[i] = ptr4[i];
    	}
	first = -1;
	image = imread(ptr6);
	memcpy(ptr5, image.data, image.total() * image.elemSize());
	presetImage = imread(ptr6);
	char *names[8] = {"Temperature 0", "Tint 1", "Exposure 2", "Crop 3", "Noise 5", "Vignette 6", "Brightness 7", "Color 8"};
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
        	for(int i = 0; i < 8; i++) {
            		if(filterFlags[i] == false) {
                		pthread_create(&threadIDs[i], NULL, mouseCallBack, (void*)names[i]);
                		filterFlags[i] = true;
            		}
        	}
        	usleep(100000);
    	}
	for(int i = 0; i < 8; i++) {
        	if(filterFlags[i] == true) {
        		pthread_join(threadIDs[i], NULL);
        		filterFlags[i] = false;
        	}
        }
}
