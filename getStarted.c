#include "getStarted.h"
#include "upload.h"

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
        	background = imread("src/Multedio_Hover.png"); //animation effect
        	if (event == EVENT_LBUTTONDOWN) //if you press the button
        	{
            		setCursor(gdk_get_default_root_window(), watchCursor);
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
