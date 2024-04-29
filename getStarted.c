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

    	if (x > 295*scaledWidth && x < 600*scaledWidth && y > 335*scaledHeight && y < 410*scaledHeight) //if the x and y coordinates are on the button 
    	{
        	setCursor(gdk_get_default_root_window(), handCursor);
        	background = imread("src/Multedio_Hover.png"); //animation effect (glow)
        	if (event == EVENT_LBUTTONDOWN) //if you press the button
        	{	
        		flag = "1";
            		setCursor(gdk_get_default_root_window(), watchCursor); //cursor made
    			strcpy(ptr1, flag); //ptr1 gets flag ki val (1)
            		setMouseCallback("Multedio", upload, nullptr); 
        	}
        	
    	} 
    	else
    	{
        	setCursor(gdk_get_default_root_window(), arrowCursor);
        	background = imread("src/Multedio.png"); 
    	}

    	show(background);
}

void getOther() 
{
	while (true) {
        	pthread_mutex_lock(&threadMutex); //Locks for only 1 thread to access the resources
        	flag = (char*)(ptr1); //TypeCasting
       		cout << flag << endl;
        	if (strcmp(flag, "2") == 0) //if the flag is 2
        	{
            		pthread_mutex_unlock(&threadMutex); //the threads can now access the 
            		break;
        	}
        pthread_mutex_unlock(&threadMutex); //Hasnt come to the Flag=2 part so we unlock the section so Threads are not starved
        	cout << "Next Other" << endl;
        	usleep(1000000); //Sleeps so other Threads can have their chance
    	}
    	uploadOther();
}
