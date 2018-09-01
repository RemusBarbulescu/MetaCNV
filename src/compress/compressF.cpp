#include "../compress/compressF.h"
#include "../match_to_ref/match_to_ref.h"
//#include "../match_to_ref/match_to_ref_genes.h"

void compressF(std::vector<cnvFrame> const &cnv){
			
	std::string filepath = "../Output Files/" + ::filename;
	std::ofstream fout(boost::lexical_cast<std::string>(filepath));
	cnvFrame buffer("", 0, 0, 0, 0, 0, ""); // making all the members NULL
	fout << "chr\t" << "segment.start\t" << "segment.end\t" << "segment.length\t" << "MetaCNV.cn\t" << "RD.cn\t" << "SV.cn\t" << "MetaCNV.comments\t" << std::endl;
	fout << std::fixed << std::setprecision(1);
	
	for(int i = 0; i < cnv.size(); ++i){
		
		if (buffer.chr.empty()){
			buffer.chr = cnv[i].chr;
			buffer._start = cnv[i]._start;
			buffer._end = cnv[i]._end;
			buffer.value = cnv[i].value;
			buffer.rdValue = cnv[i].rdValue;
			buffer.svValue = cnv[i].svValue;
			buffer.comment = cnv[i].comment;
		}
		else{
			if (buffer.chr == cnv[i].chr && buffer.value == cnv[i].value){
				buffer._end = cnv[i]._end;
				if (buffer.comment.find(cnv[i].comment) == std::string::npos){
					buffer.comment.append(", ");
					buffer.comment.append(cnv[i].comment);
				}
			}
			else{
				fout << buffer.chr << "\t" << buffer._start << "\t" << buffer._end << "\t" << buffer._end - buffer._start 
                << buffer.value << "\t" << buffer.rdValue << "\t" << buffer.svValue << "\t" << buffer.comment << std::endl;
				buffer.chr = cnv[i].chr;
				buffer._start = cnv[i]._start;
				buffer._end = cnv[i]._end;
				buffer.value = cnv[i].value;
				buffer.rdValue = cnv[i].rdValue;
				buffer.svValue = cnv[i].svValue;
				buffer.comment = cnv[i].comment;
			}
		}
	}
    if (::matchGenes == "Yes"){
		std::cout << "Mapping MetaCNV output to the reference genome GRCh38.84 on genes level ..." << std::endl;
		//match_to_ref_genes(filepath);
	}
	if (::matchExons == "Yes"){
		std::cout << "Mapping MetaCNV output to the reference genome GRCh38.84 on exon level ..." << std::endl;
		match_to_ref(filepath);
	}
}
