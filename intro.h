#ifndef INTRO_H
#define INTRO_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>

using namespace cv;

extern Mat background;

char* openFile(GtkWidget *widget, gpointer data);
void setCursor(GdkWindow *window, GdkCursor *cursor);
void callbackFunc(int event, int x, int y, int flags, void* userdata);
void mainWindow();

#endif 
