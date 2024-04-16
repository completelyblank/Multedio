#ifndef INTRO_H
#define INTRO_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace cv;

extern Mat background;
extern GdkCursor *handCursor;
extern GdkCursor *arrowCursor;
extern GdkCursor *watchCursor;
extern gfloat width;
extern gfloat height;
extern gfloat scaledWidth;
extern gfloat scaledHeight;
extern Mat hovering[9];
extern Mat filters[9];
extern bool clicked;
extern bool slider;
extern int sliderValue;
extern bool dragging;
extern int threadCreated;
extern pthread_t threadID;
extern int mouseCordx;
extern pthread_mutex_t threadMutex;
extern int mouseEvent;
extern int flag1, flag2, flag3, flag4;

char* openFile(GtkWidget *widget, gpointer data);
void setCursor(GdkWindow *window, GdkCursor *cursor);
void callbackFunc(int event, int x, int y, int flags, void* userdata);
void backgroundCode();
void initializeCursors();
void show(Mat background);
void *mainWindow(void *arg);
void *mainOther(void *arg);

#endif 
