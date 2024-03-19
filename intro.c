#include "intro.h"
#include <iostream>

using namespace std;

void openFile(GtkWidget *widget, gpointer data) //selects image file and displays in open window
{
    GtkWidget *dialog;
    //dialog = creates options for opening image and cancelling the process
    dialog = gtk_file_chooser_dialog_new("Open Image", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) //if the open button is clicked
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)); //file selected and stored in c code
        Mat image = imread(filename); //reads chosen image and stores in image variable
        if (!image.empty()) //if image loaded sucessfully
        {
            namedWindow("Image", WINDOW_NORMAL); //image opened in window
            gtk_widget_destroy(dialog); //file chooser window destroyed
            resize(image, image, Size(900, 500)); //image resized
            imshow("Image", image); //image shown after resizing
            waitKey(0); //waits for user to interact
            destroyAllWindows(); //windows closed
        }
        g_free(filename); //memory freed
    } 
    else //image not loaded
    {
        gtk_widget_destroy(dialog); //file chooser closed (destroyed)
    }
}

void setCursor(GdkWindow *window, GdkCursor *cursor) {
    gdk_window_set_cursor(window, cursor);
}

void callbackFunc(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    }
    GdkCursor *handCursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_HAND2);
    GdkCursor *arrowCursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_ARROW);
    GdkCursor *watchCursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_WATCH);

    if (x > 295 && x < 600 && y > 335 && y < 410) {
        setCursor(gdk_get_default_root_window(), handCursor);
        background = imread("Multedio Hover.png");
        if (event == EVENT_LBUTTONDOWN) {
            setCursor(gdk_get_default_root_window(), watchCursor);
            openFile(nullptr, nullptr);
        }
    } else {
        setCursor(gdk_get_default_root_window(), arrowCursor);
        background = imread("Multedio.png"); 
    }

    resize(background, background, Size(900, 500));
    Mat mainWindow(500, 900, CV_8UC3, Scalar(51, 138, 255));
    Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));
    background.copyTo(backgroundROI);
    imshow("Main Window", mainWindow);
}

