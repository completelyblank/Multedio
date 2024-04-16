#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"
#include "station.h"
#include "upload.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

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
bool slider;
int sliderValue;
bool dragging;
int threadCreated;
pthread_t threadID;
int mouseCordx;
int mouseEvent;
pthread_mutex_t threadMutex;
int flag1, flag2, flag3, flag4;

int main() 
{  
	flag1 = false;
	flag2 = false;
	flag3 = false;
	flag4 = false;
	pthread_t ui, other;
	pthread_create(&ui, NULL, mainWindow, NULL);
	pthread_create(&other, NULL, mainOther, NULL);
	pthread_join(ui, NULL);
	pthread_join(other, NULL);
}



