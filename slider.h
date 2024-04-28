#ifndef SLIDER_H
#define SLIDER_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

using namespace cv;

void drawSlider(Mat &image, int value);
void onMouse(int event, int x, int y, int flags, void* userdata);
void *mouseCallBack(void *arg);
void *testing(void *arg);

#endif
