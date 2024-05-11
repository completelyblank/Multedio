#include <opencv2/opencv.hpp>
#include <iostream>
#include "batch.h"
#include <pthread.h>
#include "preset.h"
#include "continue.h"
#include <queue>
#include <filesystem>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int created = 0;
Mat presetBatchBackgrounds[6];

void storeInQueue(char* directory) {
	fs::path dirPath(directory); // Convert directory path to fs::path object

	// Check if the directory exists
	if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        	cerr << "Error: Directory does not exist or is not a directory." << endl;
        	return;
    	}

    	// Iterate over the files in the directory
    	for (const auto& entry : fs::directory_iterator(dirPath)) {
        	if (entry.is_regular_file()) { // Check if the entry is a regular file
            		std::string filePath = entry.path().string();
            		Mat image = imread(filePath); // Load the image using OpenCV
            		if (!image.empty()) { // Check if the image was loaded successfully
            			images.push(image); // Push the image into the queue
            		    	cout << "Loaded image: " << filePath << endl;
            		} else {
                		cerr << "Failed to load image: " << filePath << endl;
            		}
        	}
    	}
}


void initializeBatchHovering() {
	presetBatchBackgrounds[0] = imread("src/Click_Apply.jpg");
    	presetBatchBackgrounds[1] = imread("src/Ahraz_Apply.jpg");
    	presetBatchBackgrounds[2] = imread("src/Musha_Apply.jpg");
    	presetBatchBackgrounds[3] = imread("src/Zehabia_Apply.jpg");
    	presetBatchBackgrounds[4] = imread("src/Falfizz_Apply.jpg");
    	presetBatchBackgrounds[5] = imread("src/Siamese_Apply.jpg");
}

void batchStation(int event, int x, int y, int flags, void* userdata) {
	if (event == EVENT_MOUSEMOVE) 
    	{	
        	flag = "4";
        	strcpy(ptr1, flag);
    	}
    	if(*ptr7 == 9) {
    		setMouseCallback("Multedio", continueYN, NULL);
    	}
	char *dirname = (char*)userdata;
    	strcpy(ptr6, dirname);
    	if(imageRender == false) {
    		*ptr7 = 0;
    		storeInQueue(dirname);
    		presetImage = images.front();
    		size_t imageSize = presetImage.total() * presetImage.elemSize();
    		memcpy(ptr5, presetImage.data, imageSize);
    		imageRender = true;
    	}
    	Mat image2(presetImage.rows, presetImage.cols, presetImage.type());
	memcpy(image2.data, ptr5, image2.total() * image2.elemSize());
    	if (event == EVENT_LBUTTONDOWN) 
    	{
    		cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}
    	
    	if(x > 85*scaledWidth && x < 133*scaledWidth && y > 219*scaledHeight && y < 262*scaledHeight) { 
    		setCursor(gdk_get_default_root_window(), handCursor);
    		if (event == EVENT_LBUTTONDOWN) {
    			if(pBIndex > 1) {
    				pBIndex--;
    				adjustPreset(presetImage, pBIndex - 1, 0);
    			}
    		}
    	} else if(x > 356*scaledWidth && x < 403*scaledWidth && y > 219*scaledHeight && y < 262*scaledHeight) { 
    		setCursor(gdk_get_default_root_window(), handCursor);
    		if (event == EVENT_LBUTTONDOWN) {
    			if(pBIndex < 5) {
    				pBIndex++;
    				adjustPreset(presetImage, pBIndex - 1, 0);
    			}
    		}
    	} else if(x > 127*scaledWidth && x < 386*scaledWidth && y > 431*scaledHeight && y < 479*scaledHeight) { 
    		setCursor(gdk_get_default_root_window(), handCursor);
    		if (event == EVENT_LBUTTONDOWN && pBIndex > 0) {
    			*ptr7 = pBIndex;
    		}
    	} else {
    		setCursor(gdk_get_default_root_window(), arrowCursor);
    	}
    	
    	background = presetBatchBackgrounds[pBIndex];
    	
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

void batchOther() {
	*ptr7 = 0;
	char *dirname;
	strcpy(dirname, ptr6);
	pthread_mutex_lock(&threadMutex);
	storeInQueue(dirname);
	pthread_mutex_unlock(&threadMutex);
    	image = images.front();
	while (true) {
		if(*ptr7 == 9) {
			break;
		}
        	pthread_mutex_lock(&threadMutex);
        	flag = (char*)(ptr1);
        	pBIndex = *ptr7;
        	pthread_mutex_unlock(&threadMutex);
        	if (pBIndex != 0 && created == 0) {
        		pthread_t bThreads[images.size()];
            		for(int i = 0; i <= images.size(); i++) {
            			int* threadIndex = new int(i);
            			pthread_create(&bThreads[i], NULL, apply, threadIndex);
            		}
            		for(int i = 0; i <= images.size(); i++) {
            			pthread_join(bThreads[i], NULL);
            		}
            		created = 1;
        	}
        	usleep(1000000);
    	}
    	continueFunc();
}
