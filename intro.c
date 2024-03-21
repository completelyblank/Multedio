#include "intro.h"
#include <iostream>

using namespace std;

// Declare GdkCursor variables globally
GdkCursor *handCursor;
GdkCursor *arrowCursor;
GdkCursor *watchCursor;
gint width;
gint height;

void initializeCursors() {
	// Initialize GdkCursor variables
    	handCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "pointer");
    	arrowCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "default");
    	watchCursor = gdk_cursor_new_from_name(gdk_display_get_default(), "watch");
}

void backgroundCode() {
	// Get the default screen
	GdkScreen *screen = gdk_screen_get_default();

	// Get screen width and height
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);
}

void show(Mat background) {
	resize(background, background, Size(width*0.75, height*0.75));
    	Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255));
    	Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));
    	background.copyTo(backgroundROI);
    	imshow("Multedio", mainWindow);
}

char* openFile(GtkWidget *widget, gpointer data) //selects image file and displays in open window
{

	backgroundCode();
	char* filename = nullptr;
	
    	GtkWidget *dialog; //dialog = creates options for opening image and cancelling the process
    	dialog = gtk_file_chooser_dialog_new(
    	"Open Image", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, 
    	"_Cancel", GTK_RESPONSE_CANCEL, 
    	"_Open", GTK_RESPONSE_ACCEPT, NULL);
    	
    	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) //if the open button is clicked
    	{
        	filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)); //file selected and stored in c code
        	gtk_widget_destroy(dialog);
        	return filename;
    	} 
    	else //image not loaded
    	{
        	gtk_widget_destroy(dialog); //file chooser closed (destroyed)
    	}
}

void setCursor(GdkWindow *window, GdkCursor *cursor) //cursor event 
{
	gdk_window_set_cursor(window, cursor);
}

void station(int event, int x, int y, int flags, void* userdata) 
{
	char *filename = (char*)userdata;
	background = imread(filename); // image load
	show(background);
}

void upload(int event, int x, int y, int flags, void* userdata) 
{
	backgroundCode();
	initializeCursors();
	
	if (event == EVENT_LBUTTONDOWN) 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}
    	
    	if (x > 315 && x < 715 && y > 255 && y < 335) 
    	{
    		setCursor(gdk_get_default_root_window(), handCursor);
        	background = imread("src/Upload Hover.png"); //animation effect
        	if (event == EVENT_LBUTTONDOWN) //if you press the button
        	{
            		char* filename = openFile(nullptr, nullptr);
            		setMouseCallback("Multedio", station, filename);
        	} /*else 
        	{
			GdkDragContext* drag_context = (GdkDragContext*)userdata;
            		GtkSelectionData* data = gdk_drag_context_get_selection(drag_context);
            		gchar* uri_list = (gchar*)gtk_selection_data_get_text(data);
            		filename = g_filename_from_uri(uri_list, NULL, NULL);
            		setMouseCallback("Multedio", station, filename);       	
        	}*/
    	} 
    	else //if cursor not on button
    	{
        	setCursor(gdk_get_default_root_window(), arrowCursor);
        	background = imread("src/Upload.png"); 
    	}
	
	show(background);
}

void getStarted(int event, int x, int y, int flags, void* userdata) 
{
	backgroundCode();
	initializeCursors();
	
	if (event == EVENT_LBUTTONDOWN) 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}

    	if (x > 295 && x < 600 && y > 335 && y < 410) //if the x and y coordinates are on the button 
    	{
        	setCursor(gdk_get_default_root_window(), handCursor);
        	background = imread("src/Multedio Hover.png"); //animation effect
        	if (event == EVENT_LBUTTONDOWN) //if you press the button
        	{
            		setCursor(gdk_get_default_root_window(), watchCursor);
            		setMouseCallback("Multedio", upload, nullptr);
        	}
        	
    	} 
    	else
    	{
        	setCursor(gdk_get_default_root_window(), arrowCursor);
        	background = imread("src/Multedio.png"); 
    	}

    	show(background);
}

void mainWindow() {
	gtk_init(NULL, NULL);
	
	backgroundCode();
    	
    	initializeCursors();
    	
    	background = imread("src/Multedio.png");  //reads image called Multedio.png from src directory and saves in variable
    	show(background);
    	setMouseCallback("Multedio", getStarted, nullptr); //uses callback function from intro.h on Multedio

    	waitKey(0); //waits for user interaction
}
