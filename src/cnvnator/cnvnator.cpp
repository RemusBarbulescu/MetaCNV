#include "../cnvnator/cnvnator.h"
#include "../cnvnator/cnvnatorsplit.h"


void cnv_nator(std::vector <cnvNatorFrame> &cnvNator, std::vector <cnvNatorFrame> &cnvNatorXY ){
					
	std::cout << "Extracting cnvNator data..." << std::endl;
	
	std::ifstream cnv_in (::cnvNator_filepath.c_str());
	
	std::string line;
	std::vector <std::string> chr = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11",
					"12", "13", "14", "15", "16", "17", "18", "19", "20", "21",
					"22", "X", "Y"};
					
	std::vector <std::string> lineSplit;
	std::vector <std::string> cellSplit;
	std::vector <cnvNatorFrame> cnv;
	cnvNatorFrame buffer;
	
	while (std::getline(cnv_in, line)){
		
		boost::split (lineSplit, line, boost::is_any_of("\t"));
		boost::split (cellSplit, lineSplit[1], boost::is_any_of(":-"));
		
		if (std::find(chr.begin(), chr.end(), cellSplit[0]) != chr.end()){
			
			buffer.mutation = lineSplit[0];
			buffer.chr = cellSplit[0];
			buffer._start = boost::lexical_cast<int>(cellSplit[1]);
			buffer._end = boost::lexical_cast<int>(cellSplit[2]);
			cnv.push_back(buffer);
	
		}
		
	}
	
	cnv_nator_split(cnv, cnvNator, cnvNatorXY);
}