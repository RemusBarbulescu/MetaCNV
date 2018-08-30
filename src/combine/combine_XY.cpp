#include "../combine/combine_XY.h"
#include "../compress/compress_XY.h"
//#include <sstream>

void combine_XY(std::vector<NewSegmentFrame> const &cnv, std::vector <cnvNatorFrame> &cnvNatorXY){
			
	std::map <float, int> freq;
	std::vector <cnvFrame> cnv_combined;
	bool found = false;
	std::stringstream nr_decimals; // used to modify the number of decimals, 
	float cnv_value; // from 4 decimals to 1 decimal
	nr_decimals.precision(1);
	
	for(int i = 0; i < cnv.size(); ++i){
		auto search = freq.find(cnv[i].rdValue);
		if (search == freq.end()){
			freq.insert(std::pair<float, int>(cnv[i].rdValue, 0));
		}
		else{
			freq[cnv[i].rdValue] = freq[cnv[i].rdValue] + 1; 
		}
	}
	
	int local_minimum_freq = std::numeric_limits<int>::max();
	float a_threshold = 0; // amplifications threshold
	float d_threshold = 0; // deletions threshold
	
	for(const auto& i : freq){
		if (i.first >= 1.1 && i.first <= 1.3){
			if (i.second < local_minimum_freq){
				local_minimum_freq = i.second;
				a_threshold = i.first;
			}
		}
	}
	
	d_threshold = 1 - (a_threshold - 1);
	
	for (int i = 0; i < cnv.size(); ++i){
		if (cnv[i].rdValue == NULL && cnv[i].svValue == NULL){
			cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 0.0, cnv[i].rdValue, cnv[i].svValue, "no data from callers");
		}
		else{
			if (cnv[i].rdValue == NULL && cnv[i].svValue != NULL){
				if (cnv[i].svValue < a_threshold){
					
					cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 0.0, cnv[i].rdValue, cnv[i].svValue, "RD is null( SV<threshold)");
				}
				else{
					if (cnv[i].svValue >= a_threshold){
						nr_decimals << std::fixed << cnv[i].svValue;
						nr_decimals >> cnv_value;
						cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv_value, cnv[i].rdValue, cnv[i].svValue, "SV (RD is Null)");
						nr_decimals.clear();
					}
				}
			}
			else{
				if (cnv[i].rdValue != NULL && cnv[i].svValue != NULL){
					if (cnv[i].rdValue >= a_threshold && cnv[i].svValue <= a_threshold){
						if (!cnvNatorXY.empty()){
							for (int k = 0; k < cnvNatorXY.size(); ++k){
								
								found = false;
								if (cnv[i].chr == cnvNatorXY[k].chr && (cnv[i]._start >= cnvNatorXY[k]._start &&
								cnv[i]._start < cnvNatorXY[k]._end)){
								
									if (cnvNatorXY[k].mutation == "deletion"){
										cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::min(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD: AMP, SV:DEL)"); 
										found = true;
										break;
									}
									else{
										cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::max(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD: AMP, SV:DEL)");
										found = true;
										break;
									}
								}
							}
							if (found == false){
								
								cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 1.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD: AMP, SV:DEL)");
								
							}
						}
						else{
							cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 1.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD: AMP, SV:DE )");
						}
					}
					else{
						if (cnv[i].rdValue < a_threshold && cnv[i].svValue >= a_threshold){
							if (!cnvNatorXY.empty()){
								for (int k = 0; k < cnvNatorXY.size(); ++k){
									
									found = false;
									if (cnv[i].chr == cnvNatorXY[k].chr && (cnv[i]._start >= cnvNatorXY[k]._start &&
									cnv[i]._start < cnvNatorXY[k]._end)){
								
										if (cnvNatorXY[k].mutation == "deletion"){
											cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::min(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
											found = true;
											break;
										}
										else{
											cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::max(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
											found = true;
											break;
										}
									}
								}
								if (found == false){
									
									cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 1.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
									
								}
							}
							else{
								cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 1.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
							}
						}
						else{
							if (cnv[i].rdValue < a_threshold && cnv[i].svValue < a_threshold){
								nr_decimals << std::fixed << cnv[i].rdValue;
								nr_decimals >> cnv_value;
								cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv_value, cnv[i].rdValue, cnv[i].svValue, "RD");
								nr_decimals.clear();
							}
							else{
								if (cnv[i].rdValue >= d_threshold && cnv[i].svValue >= a_threshold){
									nr_decimals << std::fixed << cnv[i].svValue;
									nr_decimals >> cnv_value;
									cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv_value, cnv[i].rdValue, cnv[i].svValue, "SV");
									nr_decimals.clear();
								}
							}
						}
					}
				}
				else{
					if (cnv[i].rdValue != NULL && cnv[i].svValue == NULL){
						nr_decimals << std::fixed << cnv[i].rdValue;
						nr_decimals >> cnv_value;
						cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv_value, cnv[i].rdValue, cnv[i].svValue, "RD (SV is null)");
						nr_decimals.clear();
					}
					else{
						cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 1.0, cnv[i].rdValue, cnv[i].svValue, "unknown Error");
					}
				}
			}
		}
	}
	for (int i = 0; i < cnv_combined.size(); ++i){
		
		if (cnv_combined[i].comment == "Conflict 1 (RD:AMP, SV:DEL)" && ((cnv_combined[i-1].comment == "RD" && cnv_combined[i+1].comment == "RD") ||
		(cnv_combined[i-1].comment == "SV" && cnv_combined[i+1].comment == "SV"))){
			cnv_combined[i].value = cnv_combined[i-1].value;
			cnv_combined[i].comment = "Removed(Conflict 1) - " + cnv_combined[i-1].comment;
		}
	}
	compress_XY(cnv_combined);
}