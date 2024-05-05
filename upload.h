#ifndef UPLOAD_H
#define UPLOAD_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"
#include "station.h"
#include "batch.h"

using namespace cv;
using namespace std;

char* openDirectory(GtkWidget *widget, gpointer data);
char* openFile(GtkWidget *widget, gpointer data);
void upload(int event, int x, int y, int flags, void* userdata);
void uploadOther();

#endif
