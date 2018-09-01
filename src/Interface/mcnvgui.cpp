#include "mcnvgui.h"

GtkWidget *window, *box, *hline1, *hline2, *hline3, *hline4, *hline5, *hline6, *hline7, *hline8,
    *descriptionBox, *descriptionLabel1,
    *parametertitleBox, *parametertitleLabel,
	*genderBox, *genderLabel1, *genderLabel2, *genderRadioMale, *genderRadioFemale,
	*inputtitleBox, *inputtitleLabel,
    *rdFilepathBox, *rdChooseBox, *rdLabel0, *rdLabel1, *rdLabel2, *rdButton,
	*svFilepathBox, *svChooseBox, *svLabel1, *svLabel2, *svButton,
	*cnFilepathBox, *cnChooseBox, *cnRadioBox, *cnRadioYes, *cnRadioNo, *cnLabel1, *cnLabel2, *cnLabel3, *cnButton,
    *outputtitleBox, *outputtitleLabel,
	*outputBoxFilepath, *outputLabel0, *outputLabel1, *outputLabel2, *outputEntry,
    *mappingtitleBox, *mappingtitleLabel,
    *matchRadioBox, *matchLabel0, *matchLabel1, *matchRadioYes, *matchRadioNo, 
    *matchRadioGenesBox, *matchLabel2, *matchLabel3, *matchRadioGenesYes, *matchRadioGenesNo, 
    *matchRadioExonsBox, *matchRadioExonsYes, *matchRadioExonsNo, 	
    *runBox, *runButton, *closeButton, *FileNotSelectedLabel;

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

static void map_activate (GtkWidget *widget, gpointer window){
	gtk_widget_set_sensitive (matchLabel2, TRUE);
	gtk_widget_set_sensitive (matchLabel3, TRUE);
	gtk_widget_set_sensitive ( matchRadioGenesNo, TRUE);
    gtk_widget_set_sensitive ( matchRadioGenesYes, TRUE);
    gtk_widget_set_sensitive ( matchRadioExonsNo, TRUE);
    gtk_widget_set_sensitive ( matchRadioExonsYes, TRUE);
}

static void map_deactivate (GtkWidget *widget, gpointer window){
    gtk_widget_set_sensitive (matchLabel2, FALSE);
	gtk_widget_set_sensitive (matchLabel3, FALSE);
    gtk_widget_set_sensitive ( matchRadioGenesNo, FALSE);
    gtk_widget_set_sensitive ( matchRadioGenesYes, FALSE);
    gtk_widget_set_sensitive ( matchRadioExonsNo, FALSE);
    gtk_widget_set_sensitive ( matchRadioExonsYes, FALSE);
}
static void run_app (GtkWidget *widget, gpointer window){
	
	::readDepth_filepath = gtk_label_get_text (GTK_LABEL ( rdLabel2 ));
	::svdetect_filepath = gtk_label_get_text (GTK_LABEL ( svLabel2 ));
	::cnvNator_filepath = gtk_label_get_text (GTK_LABEL ( cnLabel3 ));
	::filename = gtk_entry_get_text (GTK_ENTRY ( outputEntry ));
	::filenameXY = ::filename + "_XY.dat";
	::filename = ::filename + ".dat";
    gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "MetaCNV is running .... " );
	
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
			
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "MetaCNV output file not set!");
		}
		
		if (::readDepth_filepath != "" && ::svdetect_filepath != "" && ::cnvNator_filepath != "" 
		&& ::filename != ".dat"){
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( genderRadioMale )) == TRUE){
				
				::gender = "Male";
				
			}
			else{
				::gender = "Female";
			}
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( matchRadioExonsYes )) == TRUE){
				
				::match = "Yes";
				
			}
			
			else{
				::match = "No";
			}
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( matchRadioGenesYes )) == TRUE){
				
				::matchGenes = "Yes";
				
			}
			
			else{
				::matchGenes = "No";
			}
			::readDepth_filepath = gtk_label_get_text (GTK_LABEL ( rdLabel2 ));
			::svdetect_filepath = gtk_label_get_text (GTK_LABEL ( svLabel2 ));
			::cnvNator_option = "Yes";
			::cnvNator_filepath = gtk_label_get_text (GTK_LABEL ( cnLabel3 ));
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "MetaCNV is running .... " ); //this is not working 
			
			gtk_main_quit();
		}
	}
	else {
		if (::readDepth_filepath == ""){
			std::cout << "RD" << std::endl;
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "ReadDepth file not set!");
		}
		
		if (::svdetect_filepath == ""){
			std::cout << "SV" << std::endl;
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "SVDetect file not set!");
		}
		
		if (::filename == ".dat"){
			std::cout << "asd" << std::endl;
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "MetaCNV output file not set!");
		}
		
		if (::readDepth_filepath != "" && ::svdetect_filepath != "" && ::filename != ".dat"){
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( genderRadioMale )) == TRUE){
				
				::gender = "Male";
				
			}
			else{
				::gender = "Female";
			}
			
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( matchRadioExonsYes )) == TRUE){
				
				::match = "Yes";
				
			}
			
			else{
				::match = "No";
			}

			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( matchRadioGenesYes )) == TRUE){
				
				::matchGenes = "Yes";
				
			}
			
			else{
				::matchGenes = "No";
			}
			
			::readDepth_filepath = gtk_label_get_text (GTK_LABEL ( rdLabel2 ));
			::svdetect_filepath = gtk_label_get_text (GTK_LABEL ( svLabel2 ));
			gtk_label_set_text (GTK_LABEL ( FileNotSelectedLabel ), "MetaCNV is running .... " ); //this is not working 
			
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
	gtk_window_set_title(GTK_WINDOW ( window ), "MetaCNV ");
	g_signal_connect (window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	
	/*********************** BUTTONS ***********************/
	
	rdButton = gtk_button_new_with_label ("Choose filepath");
	g_signal_connect (rdButton, "clicked", G_CALLBACK (rdOpen_dialog), window);
	
	svButton = gtk_button_new_with_label ("Choose filepath");
	g_signal_connect (svButton, "clicked", G_CALLBACK (svOpen_dialog), window);
	
	cnButton = gtk_button_new_with_label ("Choose filepath");
	g_signal_connect (cnButton, "clicked", G_CALLBACK (cnvNatorOpen_dialog), window);
	
	runButton = gtk_button_new_with_label ("  Run MetaCNV  ");
    gtk_widget_set_size_request(runButton, 90, 50);
    GdkRGBA bg_run = { 0.75, 0, 1, 0.5 };
	gtk_widget_override_background_color(runButton, GTK_STATE_FLAG_NORMAL, &bg_run);
	g_signal_connect (runButton, "clicked", G_CALLBACK (run_app), window);
    
	closeButton = gtk_button_new_with_label (" Close MetaCNV ");
	gtk_widget_set_size_request(closeButton, 90, 50);
    GdkRGBA bg_close = { 0.6, 0.6, 0.6, 0.5 };
	gtk_widget_override_background_color(closeButton, GTK_STATE_FLAG_NORMAL, &bg_close);
    g_signal_connect (closeButton, "clicked", G_CALLBACK (gtk_main_quit), window);
	
	////////////////////////////////////////////////////////
	
	/*********************** LABELS ***********************/
    descriptionLabel1 = gtk_label_new ("  MetaCNV is a copy number caller that infers reliably copy numbers for human genomes with a consensus approach; \n  MetaCNV accepts the results of up to three copy number callers and infers absolute and non-biased copy numbers \n  gap-less for a genome. MetaCNV is based on a meta-model that bypasses weaknesses of current calling models \n  and combines the strength of existing approaches.");
        
    parametertitleLabel = gtk_label_new ("\tParameters");
    genderLabel2 = gtk_label_new ("\t\tGender: ");
	
    inputtitleLabel = gtk_label_new ("\tInput files");
	rdLabel1 = gtk_label_new ("\t\tReadDepth filepath\t");
	rdLabel2 = gtk_label_new ("");
	
	svLabel1 = gtk_label_new ("\t\tSVDetect filepath\t");
	svLabel2 = gtk_label_new ("");
	
	cnLabel1 = gtk_label_new ("\t\tDo you wish to include CNVnator? ");
	cnLabel2 = gtk_label_new ("\t\tCNVnator filepath:\t");
	cnLabel3 = gtk_label_new ("");
		
    outputtitleLabel = gtk_label_new ("\tOutput file " );
	outputLabel1 = gtk_label_new ("\t\tMetaCNV file in path MetaCNV/Output_files/");
	outputLabel2 = gtk_label_new (".dat");
    
    mappingtitleLabel = gtk_label_new ("\tMapping to a reference genome");
	matchLabel1 = gtk_label_new ("\t\tDo you wish to match MetaCNV's output to the GRCh38 reference genome? ");
    matchLabel2 = gtk_label_new ("\t\t\t\t\t\t\t\t\tto GRCh38 on gene level ");
    matchLabel3 = gtk_label_new ("\t\t\t\t\t\t\t\t\tto GRCh38 on exon level ");
	
	//::runLabel = gtk_label_new ("");
	FileNotSelectedLabel = gtk_label_new ("");
	
	///////////////////////////////////////////////////////
	
	
	/*********************** SEPARATOR *********************/
	
	hline1 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline2 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline3 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline4 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	hline5 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    hline6 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    hline7 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    hline8 = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	
	////////////////////////////////////////////////////////
	
	/********************** ENTRIES ***********************/
	
	outputEntry = gtk_entry_new ();
	
	//////////////////////////////////////////////////////
	
	/*********************** RADIO ***********************/
	
	genderRadioMale = gtk_radio_button_new_with_label (NULL, "Male");
	genderRadioFemale = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON (genderRadioMale )), "Female");
	
	matchRadioNo = gtk_radio_button_new_with_label (NULL, "No");
	matchRadioYes = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON ( matchRadioNo )), "Yes");
	
    matchRadioGenesNo = gtk_radio_button_new_with_label (NULL, "No");
	matchRadioGenesYes = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON ( matchRadioGenesNo )), "Yes");
    matchRadioExonsNo = gtk_radio_button_new_with_label (NULL, "No");
    matchRadioExonsYes = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON ( matchRadioExonsNo )), "Yes");
    g_signal_connect (matchRadioNo, "clicked", G_CALLBACK (map_deactivate), window);
    g_signal_connect (matchRadioYes, "clicked", G_CALLBACK (map_activate), window);
    
	cnRadioNo = gtk_radio_button_new_with_label (NULL, "No");
	g_signal_connect (cnRadioNo, "clicked", G_CALLBACK (cnFile_deactivate), window);
	cnRadioYes = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON ( cnRadioNo )), "Yes");
	g_signal_connect (cnRadioYes, "clicked", G_CALLBACK (cnFile_activate), window);
	
	//////////////////////////////////////////////////////
		
	/*********************** BOXES ***********************/
	descriptionBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( descriptionBox ), "margin-top", 15, NULL);
	gtk_box_pack_start (GTK_BOX ( descriptionBox ), descriptionLabel1, 0, 0, 2);
    
    parametertitleBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( descriptionBox ), "margin-top", 15, NULL);
    gtk_box_pack_start (GTK_BOX ( parametertitleBox ), parametertitleLabel, 0, 0, 2);
    
	genderBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( genderBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( genderBox ), genderLabel1, 0, 0, 2);
    gtk_box_pack_start (GTK_BOX ( genderBox ), genderLabel2, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( genderBox ), genderRadioMale, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( genderBox ), genderRadioFemale, 0, 0, 2);

    inputtitleBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( inputtitleBox ), "margin-top", 15, NULL);
    gtk_box_pack_start (GTK_BOX ( inputtitleBox ), inputtitleLabel, 0, 0, 2);
	
    rdChooseBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( rdChooseBox ), "margin-top", 15, NULL);
	gtk_box_pack_start (GTK_BOX ( rdChooseBox ), rdLabel0, 0, 0, 2);
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
	
	outputtitleBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( outputtitleBox ), "margin-top", 15, NULL);
    gtk_box_pack_start (GTK_BOX ( outputtitleBox ), outputtitleLabel, 0, 0, 2);
    
	outputBoxFilepath = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( outputBoxFilepath ), "margin-top", 15, NULL);
    gtk_box_pack_start (GTK_BOX ( outputBoxFilepath ), outputLabel0, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( outputBoxFilepath ), outputLabel1, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( outputBoxFilepath ), outputEntry, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( outputBoxFilepath ), outputLabel2, 0, 0, 2);
	
    mappingtitleBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( mappingtitleBox ), "margin-top", 15, NULL);
    gtk_box_pack_start (GTK_BOX ( mappingtitleBox ), mappingtitleLabel, 0, 0, 2);
    
 	matchRadioBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_set (GTK_BOX ( matchRadioBox ), "margin-top", 5, NULL);
	gtk_box_pack_start (GTK_BOX ( matchRadioBox ), matchLabel1, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioBox ), matchRadioNo, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioBox ), matchRadioYes, 0, 0, 2);
	
	matchRadioGenesBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start (GTK_BOX ( matchRadioGenesBox ), matchLabel2, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioGenesBox ), matchRadioGenesNo, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioGenesBox ), matchRadioGenesYes, 0, 0, 2);
    
    matchRadioExonsBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start (GTK_BOX ( matchRadioExonsBox ), matchLabel3, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioExonsBox ), matchRadioExonsNo, 0, 0, 2);
	gtk_box_pack_start (GTK_BOX ( matchRadioExonsBox ), matchRadioExonsYes, 0, 0, 2);
	
	runBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_end (GTK_BOX ( runBox ), runButton, 0, 0, 15);
    gtk_box_pack_end (GTK_BOX ( runBox ), closeButton, 0, 0, 15);
	gtk_box_pack_end (GTK_BOX ( runBox ), FileNotSelectedLabel, 0, 0, 15);
	
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
    gtk_box_pack_start (GTK_BOX ( box ), descriptionBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline1, 0, 0, 0);
    
    gtk_box_pack_start (GTK_BOX ( box ), parametertitleBox, 0, 0, 0);
		
	gtk_box_pack_start (GTK_BOX ( box ), genderBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline2, 0, 0, 0);
	
    gtk_box_pack_start (GTK_BOX ( box ), inputtitleBox, 0, 0, 0);
		    
	gtk_box_pack_start (GTK_BOX ( box ), rdChooseBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), rdFilepathBox, 0, 0, 0);
	//gtk_box_pack_start (GTK_BOX ( box ), hline3, 0, 0, 0);
	
	gtk_box_pack_start (GTK_BOX ( box ), svChooseBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), svFilepathBox, 0, 0, 0);
	//gtk_box_pack_start (GTK_BOX ( box ), hline4, 0, 0, 0);

	gtk_box_pack_start (GTK_BOX ( box ), cnRadioBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), cnChooseBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), cnFilepathBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline5, 0, 0, 0);
    
    gtk_box_pack_start (GTK_BOX ( box ), outputtitleBox, 0, 0, 0);
		
    gtk_box_pack_start (GTK_BOX ( box ), outputBoxFilepath, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline6, 0, 0, 0);
    
    gtk_box_pack_start (GTK_BOX ( box ), mappingtitleBox, 0, 0, 0);
    
    gtk_box_pack_start (GTK_BOX ( box ), matchRadioBox, 0, 0, 0);
    gtk_box_pack_start (GTK_BOX ( box ), matchRadioGenesBox, 0, 0, 0);
    gtk_box_pack_start (GTK_BOX ( box ), matchRadioExonsBox, 0, 0, 0);
	gtk_box_pack_start (GTK_BOX ( box ), hline7, 0, 0, 0);
    	
    gtk_box_pack_start (GTK_BOX ( box ), runBox, 0, 0, 0);
    gtk_box_pack_start (GTK_BOX ( box ), hline8, 0, 0, 0);
    
    ///////////////////////////////////////////////////////
	
	/*********************** CHECK **************************/
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( cnRadioNo )) == TRUE) {
		
		gtk_widget_set_sensitive (cnLabel2, FALSE);
		gtk_widget_set_sensitive (cnLabel3, FALSE);
		gtk_widget_set_sensitive (cnButton, FALSE);
	}
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON ( matchRadioNo )) == TRUE) {
		gtk_widget_set_sensitive (matchLabel2, FALSE);
		gtk_widget_set_sensitive (matchLabel3, FALSE);
		gtk_widget_set_sensitive (matchRadioGenesYes, FALSE);
        gtk_widget_set_sensitive (matchRadioGenesNo, FALSE);
        gtk_widget_set_sensitive (matchRadioExonsYes, FALSE);
        gtk_widget_set_sensitive (matchRadioExonsNo, FALSE);
	}
	
	////////////////////////////////////////////////////
	
	gtk_container_add (GTK_CONTAINER ( window ), box);
	
	gtk_widget_show_all ( window );

}