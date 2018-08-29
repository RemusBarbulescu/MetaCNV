#include "mcnvgui.h"


GtkWidget *window, *box, *hline1, *hline2, *hline3, *hline4, *hline5,
	*genderBox, *genderLabel,*genderRadioMale, *genderRadioFemale,
	*matchRadioBox, *matchLabel1, *matchRadioYes, *matchRadioNo,
	*rdFilepathBox, *rdChooseBox, *rdLabel1, *rdLabel2, *rdButton,
	*svFilepathBox, *svChooseBox, *svLabel1, *svLabel2, *svButton,
	*cnFilepathBox, *cnChooseBox, *cnRadioBox, *cnRadioYes, *cnRadioNo, *cnLabel1, *cnLabel2, *cnLabel3, *cnButton,
	*outputBoxFilepath, *outputLabel1, *outputLabel2, *outputEntry,
	*runBox, *runButton, *FileNotSelectedLabel;

static void rdOpen_dialog (GtkWidget *widget, gpointer window){
	
	GtkWidget *dialog;
	
	dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW ( window ), 
	GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	
	gtk_widget_show_all ( dialog );
	
	gint resp = gtk_dialog_run (GTK_DIALOG ( dialog ));
	
	if (resp == GTK_RESPONSE_OK){
		gtk_label_set_text (GTK_LABEL ( rdLabel2 ), gtk_file_chooser_get_filename(GTK_FILE_CHOOSER ( dialog )));
	}
		
	gtk_widget_destroy ( dialog );
	
}


static void svOpen_dialog (GtkWidget *widget, gpointer window){
	
	GtkWidget *dialog;
	
	dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW ( window ), 
	GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	
	gtk_widget_show_all ( dialog );
	
	gint resp = gtk_dialog_run (GTK_DIALOG ( dialog ));
	
	if (resp == GTK_RESPONSE_OK){
		gtk_label_set_text (GTK_LABEL ( svLabel2 ), gtk_file_chooser_get_filename(GTK_FILE_CHOOSER ( dialog )));
	}

	gtk_widget_destroy ( dialog );
	
}

static void cnvNatorOpen_dialog (GtkWidget *widget, gpointer window){
	
	GtkWidget *dialog;
	
	dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW ( window ), 
	GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	
	gtk_widget_show_all ( dialog );
	
	gint resp = gtk_dialog_run (GTK_DIALOG ( dialog ));
	
	if (resp == GTK_RESPONSE_OK){
		gtk_label_set_text (GTK_LABEL ( cnLabel3 ), gtk_file_chooser_get_filename(GTK_FILE_CHOOSER ( dialog )));
	}
		
	gtk_widget_destroy ( dialog );
	
}

static void cnFile_activate (GtkWidget *widget, gpointer window){
	
	gtk_widget_set_sensitive (cnLabel2, TRUE);
	gtk_widget_set_sensitive (cnLabel3, TRUE);
	gtk_widget_set_sensitive (cnButton, TRUE);
	
}

static void cnFile_deactivate (GtkWidget *widget, gpointer window){
	
	gtk_widget_set_sensitive (cnLabel2, FALSE);
	gtk_widget_set_sensitive (cnLabel3, FALSE);
	gtk_widget_set_sensitive (cnButton, FALSE);
	
}

static void run_app (GtkWidget *widget, gpointer window){
	
	::readDepth_filepath = gtk_label_get_text (GTK_LABEL ( rdLabel2 ));
	::svdetect_filepath = gtk_label_get_text (GTK_LABEL ( svLabel2 ));
	::cnvNator_filepath = gtk_label_get_text (GTK_LABEL ( cnLabel3 ));
	::filename = gtk_entry_get_text (GTK_ENTRY ( outputEntry ));
	::filenameXY = ::filename + "_XY.dat";
	::filename = ::filename + ".dat";
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( cnRadioYes )) == TRUE)
	{
		if (::readDepth_filepath == "") {

			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "ReadDepth file not set!");
		}
		
		if (::svdetect_filepath == "") {

			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "SVDetect file not set!");
		}
		
		if (::cnvNator_filepath == "") {

			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "CNVnator file not set!");
		}
		
		if (::filename == ".dat"){
			
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "Output file not set!");
		}
		
		if (::readDepth_filepath != "" && ::svdetect_filepath != "" && ::cnvNator_filepath != "" 
		&& ::filename != ".dat"){
			
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( genderRadioMale )) == TRUE){
				
				::gender = "Male";
				
			}
			else{
				::gender = "Female";
			}
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( matchRadioYes )) == TRUE){
				
				::match = "Yes";
				
			}
			
			else{
				::match = "No";
			}
			
			::readDepth_filepath = gtk_label_get_text (GTK_LABEL ( rdLabel2 ));
			::svdetect_filepath = gtk_label_get_text (GTK_LABEL ( svLabel2 ));
			::cnvNator_option = "Yes";
			::cnvNator_filepath = gtk_label_get_text (GTK_LABEL ( cnLabel3 ));
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel), "");
			
			gtk_main_quit();
			
		}
	}
	else {
		if (::readDepth_filepath == ""){
			std::cout << "RD" << std::endl;
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "readDepth file not set!");
		}
		
		if (::svdetect_filepath == ""){
			std::cout << "SV" << std::endl;
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "SVdetect file not set!");
		}
		
		if (::filename == ".dat"){
			std::cout << "asd" << std::endl;
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "Output file not set!");
		}
		
		if (::readDepth_filepath != "" && ::svdetect_filepath != "" && ::filename != ".dat"){
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( genderRadioMale )) == TRUE){
				
				::gender = "Male";
				
			}
			else{
				::gender = "Female";
			}
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( matchRadioYes )) == TRUE){
				
				::match = "Yes";
				
			}
			
			else{
				::match = "No";
			}
			
			::readDepth_filepath = gtk_label_get_text (GTK_LABEL ( rdLabel2 ));
			::svdetect_filepath = gtk_label_get_text (GTK_LABEL ( svLabel2 ));
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel), "");
			
			/*if (::gender == "Male"){
			
				if (::cnvNator_option == "Yes"){
					cnv_nator(cnvNator, cnvNatorXY);
				}

			}
			else{
				if (::cnvNator_option == "Yes") {
					cnv_nator_female(cnvNator);
				}
			
			}*/
			
			gtk_main_quit();
		}
	}
	
}


void mcnvGUI (){
	
	window = gtk_window_new ( GTK_WINDOW_TOPLEVEL );
	gtk_widget_set_size_request (window, 600, 400);
	gtk_window_set_title(GTK_WINDOW ( window ), "MetaCNV");
	g_signal_connect (window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	
	
	
	/*********************** BUTTONS ***********************/
	
	
	rdButton = gtk_button_new_with_label ("Choose filepath");
	g_signal_connect (rdButton, "clicked", G_CALLBACK (rdOpen_dialog), window);
	
	svButton = gtk_button_new_with_label ("Choose filepath");
	g_signal_connect (svButton, "clicked", G_CALLBACK (svOpen_dialog), window);
	
	cnButton = gtk_button_new_with_label ("Choose filepath");
	g_signal_connect (cnButton, "clicked", G_CALLBACK (cnvNatorOpen_dialog), window);
	
	runButton = gtk_button_new_with_label ("   Run   ");
	g_signal_connect (runButton, "clicked", G_CALLBACK (run_app), window);
	
	
	
	////////////////////////////////////////////////////////
	
	
	/*********************** LABELS ***********************/
	
	genderLabel = gtk_label_new ("Gender: ");
	
	matchLabel1 = gtk_label_new ("Do you wish to match it to the reference genome? ");
		
	rdLabel1 = gtk_label_new ("ReadDepth filepath: ");
	rdLabel2 = gtk_label_new ("");
	
	svLabel1 = gtk_label_new ("SVDetect filepath: ");
	svLabel2 = gtk_label_new ("");
	
	cnLabel1 = gtk_label_new ("Do you wish to include cnvNator? ");
	cnLabel2 = gtk_label_new ("CNVnator filepath: ");
	cnLabel3 = gtk_label_new ("");
	
	
	outputLabel1 = gtk_label_new ("Output filename:  MetaCNV/Output_files/");
	outputLabel2 = gtk_label_new (".dat");
	
	//::runLabel = gtk_label_new ("");
	FileNotSelectedLabel = gtk_label_new ("");
	
	///////////////////////////////////////////////////////
	
	
	/*********************** SEPARATOR *********************/
	
	hline1 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline2 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline3 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline4 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline5 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	
	////////////////////////////////////////////////////////
	
	
	
	
	/********************** ENTRIES ***********************/
	
	outputEntry = gtk_entry_new ();
	
	//////////////////////////////////////////////////////
	
	
	/*********************** RADIO ***********************/
	
	genderRadioMale = gtk_radio_button_new_with_label (NULL, "Male");
	genderRadioFemale = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON (genderRadioMale )), "Female");
	
	matchRadioNo = gtk_radio_button_new_with_label (NULL, "No");
	matchRadioYes = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON ( matchRadioNo )), "Yes");
	
	cnRadioNo = gtk_radio_button_new_with_label (NULL, "No");
	g_signal_connect (cnRadioNo, "clicked", G_CALLBACK (cnFile_deactivate), window);
	cnRadioYes = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON ( cnRadioNo )), "Yes");
	g_signal_connect (cnRadioYes, "clicked", G_CALLBACK (cnFile_activate), window);
	
	//////////////////////////////////////////////////////
	
	
	/*********************** BOXES ***********************/
	
	genderBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( genderBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( genderBox ), genderLabel, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( genderBox ), genderRadioMale, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( genderBox ), genderRadioFemale, 0, 0, 2);

	
	matchRadioBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( matchRadioBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( matchRadioBox ), matchLabel1, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioBox ), matchRadioNo, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioBox ), matchRadioYes, 0, 0, 2);
	
	rdChooseBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( rdChooseBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( rdChooseBox ), rdLabel1, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( rdChooseBox ), rdButton, 0, 0, 2);
	
	rdFilepathBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_start (GTK_BOX ( rdFilepathBox ), rdLabel2, 0, 0, 5);
	
	
	
	svChooseBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( svChooseBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( svChooseBox), svLabel1, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( svChooseBox ), svButton, 0, 0, 2);
	
	svFilepathBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start (GTK_BOX ( svFilepathBox ), svLabel2, 0, 0, 5);
	
	
	cnRadioBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( cnRadioBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( cnRadioBox ), cnLabel1, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX (cnRadioBox ), cnRadioNo, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX (cnRadioBox ), cnRadioYes, 0, 0, 2);
	
	cnChooseBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( cnChooseBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( cnChooseBox), cnLabel2, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( cnChooseBox ), cnButton, 0, 0, 2);
	
	cnFilepathBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start (GTK_BOX ( cnFilepathBox ), cnLabel3, 0, 0, 5);
	
	
	outputBoxFilepath = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( outputBoxFilepath ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( outputBoxFilepath ), outputLabel1, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( outputBoxFilepath ), outputEntry, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( outputBoxFilepath ), outputLabel2, 0, 0, 2);
	
	
	runBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_end (GTK_BOX ( runBox ), runButton, 0, 0, 15);
	gtk_box_pack_end (GTK_BOX ( runBox ), FileNotSelectedLabel, 0, 0, 15);
	
	
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	gtk_box_pack_start (GTK_BOX ( box ), genderBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline1, 0, 0, 0);
	
	
	gtk_box_pack_start (GTK_BOX ( box ), matchRadioBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline2, 0, 0, 0);
	
	gtk_box_pack_start (GTK_BOX ( box ), rdChooseBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), rdFilepathBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline3, 0, 0, 0);
	
	
	gtk_box_pack_start (GTK_BOX ( box ), svChooseBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), svFilepathBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline4, 0, 0, 0);

	gtk_box_pack_start (GTK_BOX ( box ), cnRadioBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), cnChooseBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), cnFilepathBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline5, 0, 0, 0);

	
	gtk_box_pack_start ( GTK_BOX ( box ), outputBoxFilepath, 0, 0, 0);
	gtk_box_pack_start ( GTK_BOX ( box ), runBox, 0, 0, 0);
	
	///////////////////////////////////////////////////////
	
	
	/*********************** CHECK **************************/
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( cnRadioNo )) == TRUE) {
		
		gtk_widget_set_sensitive (cnLabel2, FALSE);
		gtk_widget_set_sensitive (cnLabel3, FALSE);
		gtk_widget_set_sensitive (cnButton, FALSE);
		
	}
	
	////////////////////////////////////////////////////
	
	gtk_container_add (GTK_CONTAINER ( window ), box);
	
	
	gtk_widget_show_all ( window );
	
}