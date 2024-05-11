#ifndef NOISE_H
#define NOISE_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void adjustNoise(Mat& image, int sliderValue, int previous);
void adjustNoisePreset(int sliderValue, int previous);

#endif
