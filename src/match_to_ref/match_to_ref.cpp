/* 
 * This script matches copy numver values to the reference genome
 * 
 * 
 */

#include "../match_to_ref/match_to_ref.h"
#include <thread>
#include <cstdlib>

std::ofstream cnv_out;

template <typename T, typename U, typename P>
bool check_and_output(T cnv_chr, U cnv_start, U cnv_end, U cnv_end_next, P cnv_value, T gene_chr, T gene_id, T biotype, T name, T strand, T exon_id, U exon_start, U exon_end){
	
	//cnv starts before and ends after the exon

	if (gene_chr == cnv_chr && exon_start >= cnv_start && exon_end <= cnv_end){
		
		cnv_out << gene_chr << "\t" << gene_id << "\t" << biotype << "\t" << name
		<< "\t" << strand << "\t" << exon_id << "\t" << exon_start << "\t" << exon_end 
		<< "\t" << cnv_chr<< "\t" << cnv_start << "\t" << cnv_end << "\t" << cnv_value 
		<< "\t" << 1.00 << std::endl;
	}

	// cnv region ends within exon

	if (gene_chr == cnv_chr && exon_start >= cnv_start && exon_end > cnv_end && exon_start < cnv_end &&
		exon_end < cnv_end_next){
		
		cnv_out << gene_chr << "\t" << gene_id << "\t" << biotype << "\t" << name
		<< "\t" << strand << "\t" << exon_id << "\t" << exon_start << "\t" << exon_end 
		<< "\t" << cnv_chr<< "\t" << cnv_start << "\t" << cnv_end << "\t" << cnv_value << "\t"
		<< (static_cast<float>(cnv_end - exon_start) / static_cast<float>(exon_end -  exon_start))
		<< std::endl;
	}

	// cnv region starts and ends within the exon

	if (gene_chr == cnv_chr && exon_start < cnv_start && exon_end > cnv_end){
		
		cnv_out << gene_chr << "\t" << gene_id << "\t" << biotype << "\t" << name
		<< "\t" << strand << "\t" << exon_id << "\t" << exon_start << "\t" << exon_end 
		<< "\t" << cnv_chr<< "\t" << cnv_start << "\t" << cnv_end << "\t" << cnv_value << "\t"           
		<< (static_cast<float>(cnv_end - cnv_start) / static_cast<float>(exon_end -  exon_start))
		<< std::endl;
	}

	// cnv region starts within exon

	if (gene_chr == cnv_chr && exon_start < cnv_start && exon_end < cnv_end && exon_end > cnv_start){
		
		cnv_out << gene_chr << "\t" << gene_id << "\t" << biotype << "\t" << name
		<< "\t" << strand << "\t" << exon_id << "\t" << exon_start << "\t" << exon_end 
		<< "\t" << cnv_chr<< "\t" << cnv_start << "\t" << cnv_end << "\t" << cnv_value << "\t"
		<< (static_cast<float>(exon_end - cnv_start) / static_cast<float>(exon_end -  exon_start))
		<< std::endl;
	}
}

struct dataFrame{
	std::string chr;
	int _start;
	int _end;
	float value;
};

void printProgBar( float percent );

void match_to_ref(std::string filepath)
{
	std::ifstream cnv_in(filepath);
	std::ifstream exon_in("../Input Files/Homo_sapiens.GRCh38.84_onlyExons.gtf");
	std::string match_filepath = "../Output Files/matched_to_refGenome/MetaCNVoutput_mappedtoGRCh38.84_exons_" + ::filename;
	cnv_out.open(match_filepath);
	
	// creating exon vectors per chromosome
	std::vector <std::vector<exonFrame>> exon(24);
	
	std::vector <dataFrame> cnv;
	dataFrame Cbuffer; // cnv buffer
	exonFrame Gbuffer; // exon buffer
	std::string line;
	std::vector <std::string> lineSplit;
    
    //skipping the first header line in ref file 
	
	
    cnv_out << "chr\t" << "metaCNV.start\t" << "metaCNV.end\t" << "metaCNV.cn" << std::endl; 
	while (std::getline(cnv_in, line)) {
		boost::split(lineSplit, line, boost::is_any_of("\t"));
			if (lineSplit[0] != "chr" && lineSplit[0] != "Chr" && lineSplit[0] != "CHR" 
			&& lineSplit[0] != "chromosome" && lineSplit[0] != "Chromosome"){
				Cbuffer.chr = lineSplit[0];
				Cbuffer._start = boost::lexical_cast<int>(lineSplit[1]);
				Cbuffer._end = boost::lexical_cast<int>(lineSplit[2]);
				Cbuffer.value = boost::lexical_cast<float>(lineSplit[4]);
				cnv.push_back(Cbuffer);
				lineSplit.clear();
			}
	}
	while(std::getline(exon_in, line)) {
		
		boost::split(lineSplit, line, boost::is_any_of("\t"));
		
		if (lineSplit[0] != "chr" && lineSplit[0] != "Chr" && lineSplit[0] != "CHR" && lineSplit[0] != "chromosome" && lineSplit[0] != "Chromosome"){
			
			Gbuffer.chr = lineSplit[1];
			Gbuffer.gid = lineSplit[2];
			Gbuffer.biotype = lineSplit[3];
			Gbuffer.name = lineSplit[5];
			Gbuffer.strand = lineSplit[7];
			Gbuffer.eid = lineSplit[11];
			Gbuffer._start = boost::lexical_cast<int>(lineSplit[12]);
			Gbuffer._end = boost::lexical_cast<int>(lineSplit[13]);
			
			if (lineSplit[1] == "1"){
				
				exon[0].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "2"){
				
				exon[1].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "3"){
				
				exon[2].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "4"){
				
				exon[3].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "5"){
				
				exon[4].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "6"){
				
				exon[5].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "7"){
				
				exon[6].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "8"){
				
				exon[7].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "9"){
				
				exon[8].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "10"){
				
				exon[9].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "11"){
				
				exon[10].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "12"){
				
				exon[11].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "13"){
				
				exon[12].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "14"){
				
				exon[13].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "15"){
				
				exon[14].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "16"){
				
				exon[15].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "17"){
				
				exon[16].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "18"){
				
				exon[17].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "19"){
				
				exon[18].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "20"){
				
				exon[19].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "21"){
				
				exon[20].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "22"){
				
				exon[21].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "X"){
				
				exon[22].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "Y"){
				
				exon[23].push_back(Gbuffer);
				
			}
			
			lineSplit.clear();
		}
	}
	
	for (int i = 0; i < cnv.size(); ++i){
		float p = (i / (float) cnv.size()) * 100.0;
		//printProgBar(p);
		if (cnv[i].chr == "1"){
			for (int j = 0; j < exon[0].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[0][j].chr, exon[0][j].gid, exon[0][j].biotype, exon[0][j].name, exon[0][j].strand, exon[0][j].eid,
				exon[0][j]._start, exon[0][j]._end);
			}
		}
		if (cnv[i].chr == "2"){
			for (int j = 0; j < exon[1].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[1][j].chr, exon[1][j].gid, exon[1][j].biotype, exon[1][j].name, exon[1][j].strand, exon[1][j].eid,
				exon[1][j]._start, exon[1][j]._end);
			}
		}

		if (cnv[i].chr == "3"){
			for (int j = 0; j < exon[2].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[2][j].chr, exon[2][j].gid, exon[2][j].biotype, exon[2][j].name, exon[2][j].strand, exon[2][j].eid,
				exon[2][j]._start, exon[2][j]._end);
			}
		}
		if (cnv[i].chr == "4"){
			for (int j = 0; j < exon[3].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[3][j].chr, exon[3][j].gid, exon[3][j].biotype, exon[3][j].name, exon[3][j].strand, exon[3][j].eid,
				exon[3][j]._start, exon[3][j]._end);
			}
		}

		if (cnv[i].chr == "5"){
			for (int j = 0; j < exon[4].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[4][j].chr, exon[4][j].gid, exon[4][j].biotype, exon[4][j].name, exon[4][j].strand, exon[4][j].eid,
				exon[4][j]._start, exon[4][j]._end);
			}
		}
		
		if (cnv[i].chr == "6"){
			for (int j = 0; j < exon[5].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[5][j].chr, exon[5][j].gid, exon[5][j].biotype, exon[5][j].name, exon[5][j].strand, exon[5][j].eid,
				exon[5][j]._start, exon[5][j]._end);
			}
		}
		if (cnv[i].chr == "7"){
			for (int j = 0; j < exon[6].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[6][j].chr, exon[6][j].gid, exon[6][j].biotype, exon[6][j].name, exon[6][j].strand, exon[6][j].eid,
				exon[6][j]._start, exon[6][j]._end);
			}
		}
		if (cnv[i].chr == "8"){
			for (int j = 0; j < exon[7].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[7][j].chr, exon[7][j].gid, exon[7][j].biotype, exon[7][j].name, exon[7][j].strand, exon[7][j].eid,
				exon[7][j]._start, exon[7][j]._end);
			}
		}
		if (cnv[i].chr == "9"){
			for (int j = 0; j < exon[8].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[8][j].chr, exon[8][j].gid, exon[8][j].biotype, exon[8][j].name, exon[8][j].strand, exon[8][j].eid,
				exon[8][j]._start, exon[8][j]._end);
			}
		}
		if (cnv[i].chr == "10"){
			for (int j = 0; j < exon[9].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[9][j].chr, exon[9][j].gid, exon[9][j].biotype, exon[9][j].name, exon[9][j].strand, exon[9][j].eid,
				exon[9][j]._start, exon[9][j]._end);
			}
		}
		if (cnv[i].chr == "11"){
			for (int j = 0; j < exon[10].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[10][j].chr, exon[10][j].gid, exon[10][j].biotype, exon[10][j].name, exon[10][j].strand, exon[10][j].eid,
				exon[10][j]._start, exon[10][j]._end);
			}
		}
		if (cnv[i].chr == "12"){
			for (int j = 0; j < exon[11].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[11][j].chr, exon[11][j].gid, exon[11][j].biotype, exon[11][j].name, exon[11][j].strand, exon[11][j].eid,
				exon[11][j]._start, exon[11][j]._end); 
			}
		}
		if (cnv[i].chr == "13"){
			for (int j = 0; j < exon[12].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[12][j].chr, exon[12][j].gid, exon[12][j].biotype, exon[12][j].name, exon[12][j].strand, exon[12][j].eid,
				exon[12][j]._start, exon[12][j]._end);
			}
		}
		if (cnv[i].chr == "14"){
			for (int j = 0; j < exon[13].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[13][j].chr, exon[13][j].gid, exon[13][j].biotype, exon[13][j].name, exon[13][j].strand, exon[13][j].eid,
				exon[13][j]._start, exon[13][j]._end);
			}
		}
		if (cnv[i].chr == "15"){
			for (int j = 0; j < exon[14].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[14][j].chr, exon[14][j].gid, exon[14][j].biotype, exon[14][j].name, exon[14][j].strand, exon[14][j].eid,
				exon[14][j]._start, exon[14][j]._end);
			}
		}
		if (cnv[i].chr == "16"){
			for (int j = 0; j < exon[15].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[15][j].chr, exon[15][j].gid, exon[15][j].biotype, exon[15][j].name, exon[15][j].strand, exon[15][j].eid,
				exon[15][j]._start, exon[15][j]._end);
			}
		}
		if (cnv[i].chr == "17"){
			for (int j = 0; j < exon[16].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[16][j].chr, exon[16][j].gid, exon[16][j].biotype, exon[16][j].name, exon[16][j].strand, exon[16][j].eid,
				exon[16][j]._start, exon[16][j]._end);
			}
		}
		if (cnv[i].chr == "18"){
			for (int j = 0; j < exon[17].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[17][j].chr, exon[17][j].gid, exon[17][j].biotype, exon[17][j].name, exon[17][j].strand, exon[17][j].eid,
				exon[17][j]._start, exon[17][j]._end);
			}
		}
		if (cnv[i].chr == "19"){
			for (int j = 0; j < exon[18].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[18][j].chr, exon[18][j].gid, exon[18][j].biotype, exon[18][j].name, exon[18][j].strand, exon[18][j].eid,
				exon[18][j]._start, exon[18][j]._end);
			}
		}
		if (cnv[i].chr == "20"){
			for (int j = 0; j < exon[19].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[19][j].chr, exon[19][j].gid, exon[19][j].biotype, exon[19][j].name, exon[19][j].strand, exon[19][j].eid,
				exon[19][j]._start, exon[19][j]._end);
			}
		}
		if (cnv[i].chr == "21"){
			for (int j = 0; j < exon[20].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[20][j].chr, exon[20][j].gid, exon[20][j].biotype, exon[20][j].name, exon[20][j].strand, exon[20][j].eid,
				exon[20][j]._start, exon[20][j]._end);
			}
		}
		if (cnv[i].chr == "22"){
			for (int j = 0; j < exon[21].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[21][j].chr, exon[21][j].gid, exon[21][j].biotype, exon[21][j].name, exon[21][j].strand, exon[21][j].eid,
				exon[21][j]._start, exon[21][j]._end);
			}
		}
		if (cnv[i].chr == "X"){
			for (int j = 0; j < exon[22].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[22][j].chr, exon[22][j].gid, exon[22][j].biotype, exon[22][j].name, exon[22][j].strand, exon[22][j].eid,
				exon[22][j]._start, exon[22][j]._end);
			}
		}
		if (cnv[i].chr == "Y"){
			for (int j = 0; j < exon[23].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				exon[23][j].chr, exon[23][j].gid, exon[23][j].biotype, exon[23][j].name, exon[23][j].strand, exon[23][j].eid,
				exon[23][j]._start, exon[23][j]._end);
			}
		}
	}
	printProgBar(100);
	
	cnv_out.close();
}

void printProgBar( float percent ) {
	std::string bar;

	for(int i = 0; i < 50; i ++){
		if( i < (int)(floor(percent)/2)){
		  bar.replace(i,1,"#");
		}else if( i == (int)(floor(percent)/2)){
		  bar.replace(i,1,"#");
		}else{
		  bar.replace(i,1," ");
		}
	}

	std::cout << std::fixed << std::setprecision(5);
	std::cout<< "\r" "[" << bar << "] ";
	std::cout.width( 3 );
	std::cout<< percent << "%     " << std::flush;
	if (percent == 100){
		std::cout << std::endl;
	}
}