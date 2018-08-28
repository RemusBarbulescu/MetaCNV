#include "../cnvnator/cnvnatorsplit.h"


void cnv_nator_split ( std::vector <cnvNatorFrame> cnvNator_full, std::vector <cnvNatorFrame> &cnvNator, 
			std::vector <cnvNatorFrame> &cnvNatorXY ){
	
	for (int i = 0; i < cnvNator_full.size(); ++i){
		if (cnvNator_full[i].chr != "X" && cnvNator_full[i].chr != "Y"){
			cnvNator.push_back(cnvNator_full[i]);
		}
		else {
			cnvNatorXY.push_back(cnvNator_full[i]);
		}
	}
}