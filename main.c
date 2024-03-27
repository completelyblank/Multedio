#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"
#include "station.h"
#include "upload.h"

using namespace cv;

Mat background; //image variable for background (Multedio's background that we show on opening)
GdkCursor *handCursor;
GdkCursor *arrowCursor;
GdkCursor *watchCursor;
gfloat width;
gfloat height;
gfloat scaledWidth;
gfloat scaledHeight;
Mat hovering[9];
Mat filters[9];
bool clicked;

int main() 
{  
	mainWindow();
}
