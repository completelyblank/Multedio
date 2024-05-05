#include "getStarted.h"
#include "upload.h"
#include <unistd.h>

void getStarted(int event, int x, int y, int flags, void* userdata) 
{
	backgroundCode();
	initializeCursors();
	
	if (event == EVENT_LBUTTONDOWN) 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}

    	if (x > 401*scaledWidth && x < 600*scaledWidth && y > 358*scaledHeight && y < 410*scaledHeight) //if the x and y coordinates are on the button 
    	{
        	setCursor(gdk_get_default_root_window(), handCursor);
        	background = imread("src/Intro_Hover.jpg"); //animation effect
        	if (event == EVENT_LBUTTONDOWN) //if you press the button
        	{	
        		flag = "1";
            		setCursor(gdk_get_default_root_window(), watchCursor); //cursor changed
    			strcpy(ptr1, flag);
            		setMouseCallback("Multedio", upload, nullptr);
        	}
        	
    	} 
    	else //if not on button
    	{
        	setCursor(gdk_get_default_root_window(), arrowCursor);
        	background = imread("src/Intro.jpg"); 
    	}

    	show(background);
}

void getOther() { //for knowing that next function works
	while (true) {
        	pthread_mutex_lock(&threadMutex);
        	flag = (char*)(ptr1);
       		cout << flag << endl; //debug and know
        	if (strcmp(flag, "2") == 0) {
            		pthread_mutex_unlock(&threadMutex); //threads can access
            		break;
        	}
        pthread_mutex_unlock(&threadMutex); //condition has passed, unlock the thread
        	cout << "Next Other" << endl;
        	usleep(1000000);
    	}
    	uploadOther();
}
