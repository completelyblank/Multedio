#ifndef TEMP_H
#define TEMP_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustTemperature(Mat& image, int sliderValue, int previous);
void adjustTemperaturePreset(int sliderValue, int previous);

#endif
