#include "../compress/compress.h"
#include "../match_to_ref/match_to_ref.h"

void compress(std::vector<cnvFrame> const &cnv){
		
	std::string filepath = "../Output Files/" + ::filename;
	
	std::ofstream fout(boost::lexical_cast<std::string>(filepath));
	cnvFrame buffer("", 0, 0, 0, 0, 0, ""); // making all the members NULL
	fout << "chr\t" << "segment.start\t" << "segment.end\t" << "segment.length(kb)\t" << "MetaCNV.CN\t" << "RD.CN\t" << "SV.CN\t" << "MetaCNV.comments\t" << std::endl;
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
				fout << buffer.chr << "\t" << buffer._start << "\t" << buffer._end << "\t" << buffer._end - buffer._start + 1 
				<< "\t" << (buffer._end - buffer._start)/1000.0 << "\t" << buffer.value << "\t" << buffer.rdValue 
				<< "\t" << buffer.svValue << "\t" << buffer.comment << std::endl;
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
	if (::match == "Yes"){
		std::cout << "Mapping MetaCNV (for chr1-chr22) to reference genome GRCh38 ..." << std::endl;
		match_to_ref(filepath);
	}
}
