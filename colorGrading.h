#ifndef COLORG_H
#define COLORG_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustColorGrading(Mat& image, int sliderVal, int previous);
void adjustColorGradingPreset(int sliderVal, int previous);

#endif
