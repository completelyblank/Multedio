#ifndef VIG_H
#define VIG_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustVignette(Mat& imageInput, int sliderValue, int previous);
void adjustVignettePreset(int sliderValue, int previous);

#endif
