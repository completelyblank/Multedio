#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include "intro.h"
#include "station.h"
#include "upload.h"
#include "brightness.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <map>
#include <functional>

using namespace cv;
using namespace std;

int pBIndex;
queue<Mat> images;
Mat copyPresetImage;
Mat background; //image variable for background (Multedio's background that we show on opening)
Mat presetImage;
GdkCursor *handCursor;
GdkCursor *arrowCursor;
GdkCursor *watchCursor;
gfloat width;
gfloat height;
gfloat scaledWidth;
gfloat scaledHeight;
Mat hovering[9];
Mat filters[9];
int clicked[2];
bool slider;
int sliderValue[9];
bool dragging;
int threadCreated;
pthread_t threadID;
int imageRender, first;
int mouseEvent;
pthread_mutex_t threadMutex;
char *flag;
pthread_t threadIDs[9];
int draw;
Mat image;
int fd[2];
bool written;
char *ptr1, *ptr6; 
int *ptr2, *ptr3, *ptr4, *ptr7;
void *ptr5;
map<string, function<void(Mat&, int, int)>> functionMap;
int previous[9];

int main() 
{  
	const int SIZE = (20)*sizeof(int);
	gtk_init(NULL, NULL);
	int fd, fd2, fd3;
	char *name = "SHM_OBJECT";
	char *name2 = "image";
	char *name3 = "filename";
	fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	fd3 = shm_open(name3, O_CREAT | O_RDWR, 0666);
 	ftruncate(fd, SIZE);
 	ftruncate(fd3, SIZE);
 	ptr1 = (char*) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	ptr2 = (int*)ptr1;
	ptr2 = ptr2 + 1;
	ptr3 = ptr2 + 1;
	ptr4 = ptr3 + 1;
	ptr7 = ptr4 + 1;
	ptr6 = (char*) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd3, 0);
	size_t imageSize = 70000000;
    	fd2 = shm_open(name2, O_CREAT | O_RDWR, 0666);
    	ftruncate(fd2, imageSize);
    	ptr5 = mmap(NULL, imageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
	pthread_t ui, other;
	pid_t pid = fork();
	if(pid == 0) {
		mainOther();
	} else {
		flag = "0";
		strcpy(ptr1, flag);
		clicked[0] = 0;
		*ptr2 = clicked[0];
                clicked[1] = 0;
		*ptr3 = clicked[1];
		mainWindow();
		usleep(100000);
	}
	shm_unlink(name);
	shm_unlink(name2);
	shm_unlink(name3);
}




