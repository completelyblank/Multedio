#ifndef CROP_H
#define CROP_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustCrop(Mat& image, int sliderValue, int previous);

#endif
