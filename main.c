#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

using namespace cv;

Mat background;

int main(int argc, char *argv[]) {
    background = imread("Multedio.png");
    resize(background, background, Size(900, 500));

    Mat mainWindow(500, 900, CV_8UC3, Scalar(51, 138, 255));
    Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));
    background.copyTo(backgroundROI);

    imshow("Main Window", mainWindow);
    setMouseCallback("Main Window", callbackFunc, nullptr);

    waitKey(0);
}

