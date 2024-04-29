#ifndef VIG_H
#define VIG_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustVignette(Mat& image, int sliderValue);

#endif
