#ifndef TINT_H
#define TINT_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustTint(Mat& image, int sliderValue, int previous);
void adjustTintPreset(int sliderValue, int previous);

#endif
