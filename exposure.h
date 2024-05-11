#ifndef EXP_H
#define EXP_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustExposure(Mat& image, int sliderValue, int previous);
void adjustExposurePreset(int sliderValue, int previous);

#endif
