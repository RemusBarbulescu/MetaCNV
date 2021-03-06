#include "../normalize/normalize_XY.h"
#include "../combine/combine_XY.h"

void normalize_XY(std::vector<NewSegmentFrame> &cnv, std::vector <cnvNatorFrame> &cnvNatorXY){

	std::map <float, int> freqRD;
	short int ploidity = 1;
	float bias, factor, e_factor;
		
	for (int i = 0; i < cnv.size(); ++i){
		auto searchRD = freqRD.find(cnv[i].rdValue);
		
		e_factor = pow((1 + (cnv[i].svValue/100)), 0.75 * cnv[i].svValue);
		cnv[i].svValue = cnv[i].svValue ;//* e_factor;
		
		if (searchRD == freqRD.end()){
			freqRD.insert(std::pair<float, int>(cnv[i].rdValue, 0));
		}
		else{
			freqRD[cnv[i].rdValue] = freqRD[cnv[i].rdValue] + 1; 
		}
	}
	
	int local_maximum = 0;
	float local_maximum_value = 0;
	
	for(const auto& i : freqRD){
		if (i.second > local_maximum){
			local_maximum = i.second;
			local_maximum_value = i.first;
		}
	}
	
    bias = ploidity - local_maximum_value;
    
    if (bias > 0.5) {
        bias =0;
    }
    
	for (int i = 0; i < cnv.size(); ++i){
		factor = std::min (cnv[i].rdValue/2.0, 1.0);
		cnv[i].rdValue = cnv[i].rdValue + (factor * bias);
	}
	
	combine_XY(cnv, cnvNatorXY);
}