#include "../new_segments/new_segments.h"
#include "../combine/crunch.h"
#include "../normalize/normalize.h"
#include "../normalize/normalize_XY.h"

//sorting data from files by chromosome and by start position
bool compareData(const cnvSegs& i, const cnvSegs& j){
    if (i.chr < j.chr)
        return true;
    else if (i.chr > j.chr)
        return false;

    if (i._start < j._start)
        return true;
    else if (i._start > j._start)
        return false;

    return false;
}


bool newSegments(std::vector <cnvNatorFrame> &cnvNator, std::vector <cnvNatorFrame> &cnvNatorXY){
	
	std::ifstream readDepth;
	std::ifstream svdetect;
	
	
	readDepth.open(::readDepth_filepath.c_str());
	if (readDepth.fail()) {
		std::cout << "Error opening readDepth file (file does not exist) ..." << std::endl;
		return EXIT_FAILURE;
	}
	
	
	svdetect.open(::svdetect_filepath.c_str());
	if (svdetect.fail()) {
		std::cout << "Error opening SVdetect file (file does not exist) ..." << std::endl;
		return EXIT_FAILURE;
	}
	
	std::cout << "Creating the new segment file..." << std::endl;
	
	std::vector <cnvSegs> rd; // readDepth vector
	std::vector <cnvSegs> sv; // SVdetect vector
	
	cnvSegs buffer;
	
	std::vector <NewSegmentFrame> segment; // vector that will contain the new segments
	std::vector <NewSegmentFrame> segmentXY;
	
	NewSegmentFrame segBuffer;
	
	std::vector <std::string> lineSplit;
	std::string line;
	std::stringstream nr_decimals;
	
	nr_decimals.precision(4);
	
	
	/* Reading input files from readDepth and SVdetect */
	
	while(std::getline(readDepth, line)){
		boost::split(lineSplit, line, boost::is_any_of("\t"));
		
		if (lineSplit[0] != "chr" && lineSplit[0] != "Chr" && lineSplit[0] != "CHR" 
			&& lineSplit[0] != "chromosome" && lineSplit[0] != "Chromosome"){
				
			if (lineSplit[0].size() > 2){
				
				lineSplit[0].erase(lineSplit[0].begin(),lineSplit[0].begin()+3); // if a "chr" is present before the 
			}									// value, it will erase it(e.g.: chr12)
			buffer.chr = lineSplit[0];
			buffer._start = boost::lexical_cast<int>(lineSplit[1]);
			buffer._end = boost::lexical_cast<int>(lineSplit[2]);
			nr_decimals << std::fixed << boost::lexical_cast<float>(lineSplit[4]);
			nr_decimals >> buffer.value;
			nr_decimals.clear();
			rd.push_back(buffer);
		}
		lineSplit.clear();
	}
	
	while(std::getline(svdetect, line)){
		boost::split(lineSplit, line, boost::is_any_of("\t"));
		
		if (lineSplit[0] != "chr" && lineSplit[0] != "Chr" && lineSplit[0] != "CHR" 
			&& lineSplit[0] != "chromosome" && lineSplit[0] != "Chromosome"){
				
			if (lineSplit[0].size() > 2){
				
				lineSplit[0].erase(lineSplit[0].begin(),lineSplit[0].begin()+3);
			}
			buffer.chr = lineSplit[0];
			buffer._start = boost::lexical_cast<int>(lineSplit[1]);
			buffer._end = boost::lexical_cast<int>(lineSplit[2]);
			nr_decimals << std::fixed << boost::lexical_cast<float>(lineSplit[5]);
			nr_decimals >> buffer.value;
			nr_decimals.clear();
			sv.push_back(buffer);
		}
		lineSplit.clear();
	}
	
	// sorting vectors
	std::sort(rd.begin(),rd.end(), compareData); 
	std::sort(sv.begin(),sv.end(), compareData); 
	
	crunch(rd, sv, segment, segmentXY, segBuffer);
	rd.empty();
	sv.empty();
	
	
	std::cout << "Normalizing readDepth and SVdetect values..." << std::endl;
	normalize(segment, cnvNator);
	normalize_XY(segmentXY, cnvNatorXY);
	
	return EXIT_SUCCESS;
}
