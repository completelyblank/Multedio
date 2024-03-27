#ifndef INTRO_H
#define INTRO_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>

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

char* openFile(GtkWidget *widget, gpointer data);
void setCursor(GdkWindow *window, GdkCursor *cursor);
void callbackFunc(int event, int x, int y, int flags, void* userdata);
void backgroundCode();
void initializeCursors();
void show(Mat background);
void mainWindow();

#endif 
