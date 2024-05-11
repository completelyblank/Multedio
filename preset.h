#ifndef PRESET_H
#define PRESET_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"
#include "brightness.h"
#include "exposure.h"
#include "tint.h"
#include "vignette.h"
#include "colorGrading.h"
#include "noiseReduction.h"
#include "temperature.h"

void adjustPreset(Mat& image, int sliderVal, int previous);
void* apply(void *arg);
void adjustPresetBatch(Mat& imageInput, int sliderVal, int previous);

#endif
