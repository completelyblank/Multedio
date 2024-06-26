#ifndef STATION_H
#define STATION_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"
#include <pthread.h>

using namespace cv;

void initializeHoveringPNGs();
void station(int event, int x, int y, int flags, void* userdata);
void rendering();

#endif
