#ifndef STATION_H
#define STATION_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

using namespace cv;

void initializeHoveringPNGs();
void station(int event, int x, int y, int flags, void* userdata);

#endif
