#include "intro.h"
#include <iostream>

using namespace std;

// Declare GdkCursor variables globally
GdkCursor *handCursor;
GdkCursor *arrowCursor;
GdkCursor *watchCursor;
gfloat width;
gfloat height;
gfloat scaledWidth;
gfloat scaledHeight;
Mat hovering[9];

void initializeHoveringPNGs() {
	// load assets
    	hovering[0] = imread("src/Temperature_Hover.png");
    	hovering[1] = imread("src/Tint_Hover.png");
    	hovering[2] = imread("src/Exposure_Hover.png");
    	hovering[3] = imread("src/Crop_Hover.png");
    	hovering[4] = imread("src/Preset_Hover.png");
    	hovering[5] = imread("src/Noise_R_Hover.png");
    	hovering[6] = imread("src/Vignette_Hover.png");
    	hovering[7] = imread("src/Brightness_Hover.png");
    	hovering[8] = imread("src/Color_Manipulation_Hover.png");
}

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
	scaledWidth = width / 1366;
	scaledHeight = height / 675;
}

void show(Mat background) {
	if(!background.empty()) {
		resize(background, background, Size(width*0.75, height*0.75));
    		Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255));
    		Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));
    		background.copyTo(backgroundROI);
    		imshow("Multedio", mainWindow);
	} else {
		cout << "Failed to load\n";
	}
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

void station(int event, int x, int y, int flags, void* userdata) {
	// Load the background image
    	Mat background = imread("src/Station.png");
    	char *filename = (char*)userdata;
    	Mat image = imread(filename);
    	if (event == EVENT_LBUTTONDOWN) 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}
    	
    	if (y > 148*scaledHeight && y < 220*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) {
			background = hovering[0];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) {
			background = hovering[1];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) {
			background = hovering[2];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else if (y > 264*scaledHeight && y < 334*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) {
			background = hovering[3];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) {
			background = hovering[4];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) {
			background = hovering[5];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else if (y > 384*scaledHeight && y < 450*scaledHeight) {
		if (x > 63*scaledWidth && x < 147*scaledHeight) {
			background = hovering[6];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else if (x > 208*scaledWidth && x < 289*scaledHeight) {
			background = hovering[7];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else if (x > 349*scaledWidth && x < 434*scaledHeight) {
			background = hovering[8];
			setCursor(gdk_get_default_root_window(), handCursor);
		} else {
			setCursor(gdk_get_default_root_window(), arrowCursor);
		}
	} else {
		setCursor(gdk_get_default_root_window(), arrowCursor);
	}
	 resize(background, background, Size(width*0.75, height*0.75));
	 resize(image, image, Size(470*scaledWidth, 472*scaledHeight));

	// Create a main window for displaying the result
    	Mat mainWindow(height*0.75, width*0.75, CV_8UC3, Scalar(51, 138, 255));

    	// Define the position to place the image on top of the background
    	int imageX = 520 * scaledWidth; // Adjust these values as needed
    	int imageY = 16 * scaledHeight;// Adjust these values as needed
    
        Rect imageROI(imageX, imageY, image.cols, image.rows);
        
        // Extract the region of interest from the background image
        Mat backgroundROI = mainWindow(Rect(0, 0, background.cols, background.rows));

        // Copy the background image to the main window
        background.copyTo(backgroundROI);

        // Place the image on top of the background
        Mat imageRegion = mainWindow(imageROI);
        image.copyTo(imageRegion);

	// Show the result
    	imshow("Multedio", mainWindow);
}


void upload(int event, int x, int y, int flags, void* userdata) 
{
	backgroundCode();
	initializeCursors();
	
	if (event == EVENT_LBUTTONDOWN) 
    	{
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
    	}
    	
    	if (x > 315*scaledWidth && x < 715*scaledWidth && y > 255*scaledHeight && y < 335*scaledHeight) 
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

    	if (x > 295*scaledWidth && x < 600*scaledWidth && y > 335*scaledHeight && y < 410*scaledHeight) //if the x and y coordinates are on the button 
    	{
        	setCursor(gdk_get_default_root_window(), handCursor);
        	background = imread("src/Multedio_Hover.png"); //animation effect
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
    	initializeHoveringPNGs();
    	
    	background = imread("src/Multedio.png");  //reads image called Multedio.png from src directory and saves in variable
    	show(background);
    	setMouseCallback("Multedio", getStarted, nullptr); //uses callback function from intro.h on Multedio

    	waitKey(0); //waits for user interaction
}
