/*
 * 
 * MetaCNV_v1.2
 * 
 */


#include "../src/new_segments/new_segments.h"
#include "../src/new_segments/new_segmentsF.h"
#include "../src/cnvnator/cnvnator.h"
#include "../src/cnvnator/cnvnator_female.h"
#include "../src/Interface/mcnvgui.h"


std::string gender = "";
std::string match = "";
std::string matchGenes = "";
std::string matchExons = "";
std::string filename = "";
std::string filenameXY = "";
std::string readDepth_filepath = "";
std::string svdetect_filepath = "";
std::string cnvNator_option = "";
std::string cnvNator_filepath = "";


int main(int argc, char *argv[]){
	
	//system("echo -e 159585 | sudo -S service apache2 stop >>/dev/null 2>>/dev/null") ;
	
	std::vector <cnvNatorFrame> cnvNator;
	std::vector <cnvNatorFrame> cnvNatorXY;
	gtk_init (&argc, &argv);
	
		
	mcnvGUI();
	
	gtk_main();
		
	clock_t start_t = clock();

	
	
	/* Checking the gender and also if 
	 * cnvNator is included in the input files
	 */
	if (::gender == "Male"){	// ::variable_name refers to a global variable
			
		if (::cnvNator_option == "Yes"){
			cnv_nator(cnvNator, cnvNatorXY);
		}
			
		if (newSegments(cnvNator, cnvNatorXY) == EXIT_FAILURE){

			return EXIT_FAILURE;
		}
	}
	else{
		if (::cnvNator_option == "Yes") {
			cnv_nator_female(cnvNator);
		}
			
		if (newSegmentsF(cnvNator) == EXIT_FAILURE){
	
				return EXIT_FAILURE;
		}
	}
	
	
	clock_t stop_t = clock();
	std::cout << "Execution time: " << (stop_t - start_t)/double(CLOCKS_PER_SEC) << " seconds" << std::endl;

	
	return 0;
}
