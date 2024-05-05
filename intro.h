#ifndef INTRO_H
#define INTRO_H

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <map>
#include <functional>

using namespace cv;
using namespace std;

#define READ_END 0
#define WRITE_END 1

extern Mat copyPresetImage;
extern Mat presetImage;
extern int previous[9];
extern char *ptr1, *ptr6;
extern int *ptr2, *ptr3, *ptr4, *ptr7;
extern void *ptr5;
extern Mat background;
extern int draw;
extern GdkCursor *handCursor;
extern GdkCursor *arrowCursor;
extern GdkCursor *watchCursor;
extern gfloat width;
extern gfloat height;
extern gfloat scaledWidth;
extern gfloat scaledHeight;
extern Mat hovering[9];
extern Mat filters[9];
extern int clicked[2];
extern bool slider;
extern int sliderValue[9];
extern bool dragging;
extern int threadCreated;
extern pthread_t threadID;
extern int imageRender, first;
extern pthread_mutex_t threadMutex;
extern int mouseEvent;
extern char* flag;
extern pthread_t threadIDs[9];
extern Mat image;
extern int fd[2];
extern bool written;
extern map<string, function<void(Mat&, int, int)>> functionMap;

char* openFile(GtkWidget *widget, gpointer data);
void setCursor(GdkWindow *window, GdkCursor *cursor);
void callbackFunc(int event, int x, int y, int flags, void* userdata);
void backgroundCode();
void initializeCursors();
void show(Mat background);
void mainWindow();
void mainOther();

#endif 
