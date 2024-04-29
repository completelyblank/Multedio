#include "intro.h"
#include "station.h"
#include "upload.h"
#include "getStarted.h"
#include <fcntl.h>
#include <iostream>
#include "brightness.h"
#include "exposure.h"
#include "tint.h"
#include "noiseReduction.h"
#include "colorGrading.h"
#include "vignette.h"

using namespace std;

void initializeCursors() {
	// Initialize GdkCursor variables
    	handCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "pointer"); //for clicking on icons
    	arrowCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "default"); //for normal 
    	watchCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "watch"); 
}

void backgroundCode() {
	// Get the default screen
	GdkScreen *screen = gdk_screen_get_default();

	// Get screen width and height
	width = gdk_screen_get_width(screen); //gets the screens ki width
	height = gdk_screen_get_height(screen); //gets screen ki height
	scaledWidth = width / 1366; //laptop adjustment
	scaledHeight = height / 675; //laptop adjustment
}

void show(Mat background) //takes background image (what we input) 
{
	if(!background.empty()) //if background is not empty 
	{
		resize(background, background, Size(width*0.75, height*0.75)); //show in accordance to scale
    		Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255)); //make window in accordance to scale and hues (not zaruri as they wont be seen0
    		Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows)); //Interaction Space made 
    		background.copyTo(backgroundROI); //Interactive Space has background we take as input 
    		imshow("Multedio", mainWindow); //show the image in the window with Multedio as the title
	} 
	else 
	{
		cout << "Failed to load\n";
	}
}



void setCursor(GdkWindow *window, GdkCursor *cursor) //cursor event 
{
	gdk_window_set_cursor(window, cursor); //whatever cursor we want at the time (hand for clicking, arrow for normal)
}



void mainWindow() 
{
    	backgroundCode(); //function called for setting the background as the window
	clicked[0] = 0; //hasnt been clicked
    	clicked[1] = 0; //hasnt been clicked
    	slider = false; //no sliders to be shown
    	dragging = false; //no dragging to be done
   	
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
    
    
    	initializeCursors(); //Cursors made
    	initializeHoveringPNGs(); //Icons will glow when cursor hovers upon them

    	background = imread("src/Multedio.png"); //Read the image on this Directory
    	show(background); //Show that image
    	setMouseCallback("Multedio", getStarted, NULL); //Mouse now starts from here

    	// Keep the main loop running
    	gtk_main();

}


void mainOther() {
	functionMap = //Function Map which saves Functions and their labels as Key and Values
	{
	        {"Brightness", adjustBrightness},
	        {"Exposure", adjustExposure},
	        {"Tint", adjustTint},
	        {"Noise", adjustNoise},
	        {"Color", adjustColorGrading},
		{"Vignette", adjustVignette}/*,
	        {"Temperature", adjustTemperature},
	        {"Crop", adjustCrop},
	        {"Preset", adjustPreset}*/
	};
	
	clicked[0] = 0;
    	clicked[1] = 0;
    while (true) 
    {
        pthread_mutex_lock(&threadMutex); //Only one Feature Thread accesses at the time //Brightness Thread runs and accesses the Values of the image
        flag = (char*)(ptr1); //TypeCasting so we can use further on
        printf("%s\n", flag); 
        if (strcmp(flag, "1") == 0) //if the flag is 1
        {
            pthread_mutex_unlock(&threadMutex); //CS Section can now be used by the other threads
            break;
        }
        pthread_mutex_unlock(&threadMutex); //else it will be unlocked as time will have passed and we dont want Threads to starve
        cout << "Other" << endl;
        usleep(1000000); //Sleeps 1 second to let Thread change
    }
    getOther();
 
}
