#include "upload.h"

void upload(int event, int x, int y, int flags, void* userdata);

char* openDirectory(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    char *dirname = nullptr;

    dialog = gtk_file_chooser_dialog_new(
        "Open Directory", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        dirname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_widget_destroy(dialog);
        return dirname;
    } else {
        gtk_widget_destroy(dialog);
        return nullptr;
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
        	return nullptr;
    	}
}

void upload(int event, int x, int y, int flags, void* userdata) 
{
	backgroundCode();
	initializeCursors();
	
	if (event == EVENT_LBUTTONDOWN) 
    	{	
        	cout << "Mouse clicked at: (" << x << ", " << y << ")" << endl;
        	flag = "2";
        	strcpy(ptr1, flag);
    	}
    	
    	if (x > 153*scaledWidth && x < 341*scaledWidth && y > 133*scaledHeight && y < 251*scaledHeight) 
    	{	
    		setCursor(gdk_get_default_root_window(), handCursor);
        	background = imread("src/Upload_Single.jpg"); //animation effect
        	if (event == EVENT_LBUTTONDOWN) //if you press the button
        	{
            		char* filename = openFile(nullptr, nullptr);
            		if (filename != nullptr) {
            			setMouseCallback("Multedio", station, filename);
            		} 
        	}
    	} 
    	else if (x > 576*scaledWidth && x < 776*scaledWidth && y > 149*scaledHeight && y < 345*scaledHeight)
    	{
    		setCursor(gdk_get_default_root_window(), handCursor);
        	background = imread("src/Upload_Batch.jpg"); //animation effect
        	if (event == EVENT_LBUTTONDOWN) //if you press the button
        	{
        		char* dirname = openDirectory(nullptr, nullptr);
            		if (dirname != nullptr) {
            			setMouseCallback("Multedio", batchStation, dirname);
            		}
        	}
    	}
    	else //if cursor not on button
    	{
        	setCursor(gdk_get_default_root_window(), arrowCursor);
        	background = imread("src/Upload.jpg"); 
    	}
	
	show(background);
}

void uploadOther() {
	while (true) {
        	pthread_mutex_lock(&threadMutex);
        	flag = (char*)(ptr1);
        	cout<<flag<<endl;
        	if (strcmp(flag, "3") == 0 || strcmp(flag, "4") == 0) {
            		pthread_mutex_unlock(&threadMutex);
            		break;
        	}
        pthread_mutex_unlock(&threadMutex);
        	usleep(1000000);
    	}
    	if(strcmp(flag, "3") == 0) {
    		rendering();
    	} else if(strcmp(flag, "4") == 0) {
    		batchOther();
    	}
}
