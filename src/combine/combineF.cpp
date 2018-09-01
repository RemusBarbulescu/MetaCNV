#include "../combine/combineF.h"
#include "../compress/compressF.h"
//#include <sstream>

void combineF(std::vector<NewSegmentFrame> const &cnv, std::vector <cnvNatorFrame> &cnvNator){
		
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
		if (i.first >= 2 && i.first <= 2.35){
			if (i.second < local_minimum_freq){
				local_minimum_freq = i.second;
				a_threshold = i.first;
			}
		}
	}
	
	d_threshold = 2 - (a_threshold - 2);
	
	for (int i = 0; i < cnv.size(); ++i){
		if (cnv[i].rdValue == NULL && cnv[i].svValue == NULL){
			cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 0.0, cnv[i].rdValue, cnv[i].svValue, "no data from callers");
		}
		else{
			if (cnv[i].rdValue == NULL && cnv[i].svValue != NULL){
				if (cnv[i].svValue < a_threshold){
					
					cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 0.0, cnv[i].rdValue, cnv[i].svValue, "no data from callers");
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
						if (!cnvNator.empty()){
							for (int k = 0; k < cnvNator.size(); ++k){
								
								found = false;
								if (cnv[i].chr == cnvNator[k].chr && (cnv[i]._start >= cnvNator[k]._start &&
								cnv[i]._start < cnvNator[k]._end)){
								
									if (cnvNator[k].mutation == "deletion"){
										cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::min(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD:AMP, SV:DEL) judge:CNVnator:DEL");
										found = true;
										break;
									}
									else{
										cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::max(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD:AMP, SV:DEL) judge:CNVnator:AMP");
										found = true;
										break;
									}
								}
							}
							if (found == false){
								// not sure if this change (1.0 to cnv.RD) is correct:
								cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i].rdValue, cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD:AMP, SV:DEL)");
                                //cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 2.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD:AMP, SV:DEL)");
							}
						}
						else{
                            // not sure if this change (1.0 to cnv.RD) is correct:
							cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i].rdValue, cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD:AMP, SV:DEL)");
                            //cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 2.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 1 (RD:AMP, SV:DEL)");
						}
					}
					else{
						if (cnv[i].rdValue < a_threshold && cnv[i].svValue >= a_threshold){
							if (!cnvNator.empty()){
								
								for (int k = 0; k < cnvNator.size(); ++k){
								
									found = false;
									if (cnv[i].chr == cnvNator[k].chr && (cnv[i]._start >= cnvNator[k]._start &&
									cnv[i]._start < cnvNator[k]._end)){
								
										if (cnvNator[k].mutation == "deletion"){
											cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::min(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP) judge:CNVnator:DEL");
											found = true;
											break;
										}
										else{
											cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, std::max(cnv[i].rdValue, cnv[i].svValue), cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP) judge:CNVnator:AMP");
											found = true;
											break;
										}
									}
								}
								if (found == false){
                                    // not sure if this change (1.0 to cnv.RD) is correct:
									cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i].rdValue, cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
                                    //cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 2.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
								}
							}
							else{
                            // not sure if this change (1.0 to cnv.RD) is correct:
							cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i].rdValue, cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
                            //cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 2.0, cnv[i].rdValue, cnv[i].svValue, "Conflict 2 (RD:DEL, SV:AMP)");
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
						cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv_value, cnv[i].rdValue, cnv[i].svValue, "RD (SV is Null)");
						nr_decimals.clear();
					}
					else{
						cnv_combined.emplace_back(cnv[i].chr, cnv[i]._start, cnv[i]._end, 2.0, cnv[i].rdValue, cnv[i].svValue, "unknown Error");
					}
				}
			}
		}
	}
	for (int i = 0; i < cnv_combined.size(); ++i){
        /* // I think we should skip this since there is no cn=ploidy anymore
		if  ( (cnv_combined[i].comment == "Conflict 1 (RD:AMP, SV:DEL)" || cnv_combined[i].comment == "Conflict 2 (RD:DEL, SV:AMP)" )  && 
            ( (cnv_combined[i-1].comment == "RD" && cnv_combined[i+1].comment == "RD") || (cnv_combined[i-1].comment == "SV" && cnv_combined[i+1].comment == "SV") ) ) {
			cnv_combined[i].value = cnv_combined[i-1].value;
			cnv_combined[i].comment = "Removed(Conflict 1) - " + cnv_combined[i-1].comment;
        }
         * */
	}
	std::cout << "Compressing ..." << std::endl;
	compressF(cnv_combined);
}