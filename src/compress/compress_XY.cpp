#include "../compress/compress_XY.h"
#include "../match_to_ref/match_to_ref.h"
//#include "../match_to_ref/match_to_ref_genes.h"

void compress_XY(std::vector<cnvFrame> const &cnvXY){
	
	std::string filepath = "../Output Files/" + ::filenameXY;
	
	std::ofstream fout_XY(boost::lexical_cast<std::string>(filepath));
	cnvFrame buffer("", 0, 0, 0, 0, 0, ""); // making all the members NULL
	fout_XY << std::fixed << std::setprecision(1);
	fout_XY << "chr\t" << "segment.start\t" << "segment.end\t" << "segment.length\t" << "MetaCNV:cn\t" << "RD.cn\t" << "SV.cn\t" << "MetaCNV.comments\t" << std::endl;
	

	for(int i = 0; i < cnvXY.size(); ++i){
		
		if (buffer.chr.empty()){
			buffer.chr = cnvXY[i].chr;
			buffer._start = cnvXY[i]._start;
			buffer._end = cnvXY[i]._end;
			buffer.value = cnvXY[i].value;
			buffer.rdValue = cnvXY[i].rdValue;
			buffer.svValue = cnvXY[i].svValue;
			buffer.comment = cnvXY[i].comment;
		}
		else{
			if (buffer.chr == cnvXY[i].chr && buffer.value == cnvXY[i].value){
				buffer._end = cnvXY[i]._end;
				if (buffer.comment.find(cnvXY[i].comment) == std::string::npos){
					buffer.comment.append(", ");
					buffer.comment.append(cnvXY[i].comment);
				}
			}
			else{
				fout_XY << buffer.chr << "\t" << buffer._start << "\t" << buffer._end << "\t" << buffer._end - buffer._start 
                << buffer.value << "\t" << buffer.rdValue << "\t" << buffer.svValue << "\t" << buffer.comment << std::endl;
				buffer.chr = cnvXY[i].chr;
				buffer._start = cnvXY[i]._start;
				buffer._end = cnvXY[i]._end;
				buffer.value = cnvXY[i].value;
				buffer.rdValue = cnvXY[i].rdValue;
				buffer.svValue = cnvXY[i].svValue;
				buffer.comment = cnvXY[i].comment;
			}
		}
	}
    if (::matchGenes == "Yes"){
		std::cout << "Mapping MetaCNV output (for autosomes) to the reference genome GRCh38.84 on gene level ..." << std::endl;
		//match_to_ref_genes(filepath);
	}
	if (::matchExons == "Yes"){
		std::cout << "Mapping MetaCNV output (for autosomes) to the reference genome GRCh38.84 on exon level ..." << std::endl;
		match_to_ref(filepath);
	}
}
