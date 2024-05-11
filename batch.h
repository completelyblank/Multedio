#ifndef BATCH_H
#define BATCH_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

void initializeBatchHovering();
void batchStation(int event, int x, int y, int flags, void* userdata);
void batchOther();

#endif
