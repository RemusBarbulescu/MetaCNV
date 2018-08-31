#include "../normalize/normalize.h"
#include "../combine/combine.h"

void normalize(std::vector<NewSegmentFrame> &cnv, std::vector <cnvNatorFrame> &cnvNator){
	
	std::map <float, int> freqRD;
	short int ploidity = 2;
	float bias, factor, e_factor;
		
	for (int i = 0; i < cnv.size(); ++i){
		auto searchRD = freqRD.find(cnv[i].rdValue);
		
		// Normalizing SVDetect values
		e_factor = pow((1 + (cnv[i].svValue/100)), 0.75 * cnv[i].svValue);
		cnv[i].svValue = cnv[i].svValue * e_factor;
		
		//Checking whether the value of the cnv was inserted into the vector before
		if (searchRD == freqRD.end()){
			freqRD.insert(std::pair<float, int>(cnv[i].rdValue, 0));
		}
		//If it was inserted before, we increment the number of apparitions by one each time it finds it
		else{
			freqRD[cnv[i].rdValue] = freqRD[cnv[i].rdValue] + 1; 
		}
	}
	
	//Calculate local maximum value;
	int local_maximum = 0;
	float local_maximum_value = 0;
	
	for(const auto& i : freqRD){
		if (i.second > local_maximum){
			local_maximum = i.second;	//Number of apparitions
			local_maximum_value = i.first;	//The value of the most frequent value
		}
	}

	bias = ploidity - local_maximum_value;
    
    if (bias > 0.5) {
        bias =0;
    }

	for (int i = 0; i < cnv.size(); ++i){
		factor = std::min(cnv[i].rdValue/2.0, 1.0);
		cnv[i].rdValue = cnv[i].rdValue + (factor * bias);
	}
	
	std::cout << "Combining ReadDepth and SVDetect ..." << std::endl;
	combine(cnv, cnvNator);
}