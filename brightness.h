#ifndef BRIGHT_H
#define BRIGHT_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustBrightness(Mat& image, int sliderValue, int previous);
void adjustBrightnessPreset(int sliderValue, int previous);

#endif
