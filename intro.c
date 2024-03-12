#include "intro.h"
#include <iostream>

using namespace std;

void openFile(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Open Image", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        Mat image = imread(filename);
        if (!image.empty()) {
            namedWindow("Image", WINDOW_NORMAL);
            gtk_widget_destroy(dialog);
            resize(image, image, Size(900, 500));
            imshow("Image", image);
            waitKey(0);
            destroyAllWindows();
        }
        g_free(filename);
    } else {
        gtk_widget_destroy(dialog);
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

