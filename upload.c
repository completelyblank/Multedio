#include "upload.h"

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
