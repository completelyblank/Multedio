#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"

using namespace cv;

Mat background; //image variable for background (Multedio's background that we show on opening)

int main() 
{
    background = imread("src/Multedio.png");  //reads image called Multedio.png from src directory and saves in variable
    resize(background, background, Size(900, 500)); //background resized 

    Mat mainWindow(500, 900, CV_8UC3, Scalar(51, 138, 255)); //main window created with colors and size 
    Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows)); //region of interest created in main window
    background.copyTo(backgroundROI); //background image is now the region of interest

    imshow("Main Window", mainWindow); //the main window is opened and has Main Window as the name
    setMouseCallback("Main Window", callbackFunc, nullptr); //uses callback function from intro.h on Main Window

    waitKey(0); //waits for user interaction
}

