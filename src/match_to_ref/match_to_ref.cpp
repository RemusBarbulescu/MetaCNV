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
bool check_and_output(T cnv_chr, U cnv_start, U cnv_end, U cnv_end_next, P cnv_value,
T gene_chr, T gene_id, T biotype, T name, T strand, T exon_id, U exon_start, U exon_end){
	
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
	std::ifstream gene_in("../Input Files/Homo_sapiens.GRCh38.84_onlyExons.gtf");
	std::string match_filepath = "../Output Files/matched_to_refGenome/MetaCNV_mappedtoGRCh38.84_exons_" + ::filename;
	cnv_out.open(match_filepath);
	
	
	// creating gene vectors per chromosome
	std::vector <std::vector<geneFrame>> gene(24);
	
	std::vector <dataFrame> cnv;
	dataFrame Cbuffer; // cnv buffer
	geneFrame Gbuffer; // gene buffer
	std::string line;
	std::vector <std::string> lineSplit;
	
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
	while(std::getline(gene_in, line)) {
		
		boost::split(lineSplit, line, boost::is_any_of("\t"));
		
		if (lineSplit[0] != "chr" && lineSplit[0] != "Chr" && lineSplit[0] != "CHR" 
			&& lineSplit[0] != "chromosome" && lineSplit[0] != "Chromosome"){
			
			Gbuffer.chr = lineSplit[1];
			Gbuffer.gid = lineSplit[2];
			Gbuffer.biotype = lineSplit[3];
			Gbuffer.name = lineSplit[5];
			Gbuffer.strand = lineSplit[7];
			Gbuffer.eid = lineSplit[11];
			Gbuffer._start = boost::lexical_cast<int>(lineSplit[12]);
			Gbuffer._end = boost::lexical_cast<int>(lineSplit[13]);
			
			if (lineSplit[1] == "1"){
				
				gene[0].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "2"){
				
				gene[1].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "3"){
				
				gene[2].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "4"){
				
				gene[3].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "5"){
				
				gene[4].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "6"){
				
				gene[5].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "7"){
				
				gene[6].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "8"){
				
				gene[7].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "9"){
				
				gene[8].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "10"){
				
				gene[9].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "11"){
				
				gene[10].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "12"){
				
				gene[11].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "13"){
				
				gene[12].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "14"){
				
				gene[13].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "15"){
				
				gene[14].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "16"){
				
				gene[15].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "17"){
				
				gene[16].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "18"){
				
				gene[17].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "19"){
				
				gene[18].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "20"){
				
				gene[19].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "21"){
				
				gene[20].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "22"){
				
				gene[21].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "X"){
				
				gene[22].push_back(Gbuffer);
				
			}
			if (lineSplit[1] == "Y"){
				
				gene[23].push_back(Gbuffer);
				
			}
			
			lineSplit.clear();
		}
	}
	
	for (int i = 0; i < cnv.size(); ++i){
		float p = (i / (float) cnv.size()) * 100.0;
		printProgBar(p);
		if (cnv[i].chr == "1"){
			for (int j = 0; j < gene[0].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[0][j].chr, gene[0][j].gid, gene[0][j].biotype, gene[0][j].name, gene[0][j].strand, gene[0][j].eid,
				gene[0][j]._start, gene[0][j]._end);
			}
		}
		if (cnv[i].chr == "2"){
			for (int j = 0; j < gene[1].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[1][j].chr, gene[1][j].gid, gene[1][j].biotype, gene[1][j].name, gene[1][j].strand, gene[1][j].eid,
				gene[1][j]._start, gene[1][j]._end);
			}
		}

		if (cnv[i].chr == "3"){
			for (int j = 0; j < gene[2].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[2][j].chr, gene[2][j].gid, gene[2][j].biotype, gene[2][j].name, gene[2][j].strand, gene[2][j].eid,
				gene[2][j]._start, gene[2][j]._end);
			}
		}
		if (cnv[i].chr == "4"){
			for (int j = 0; j < gene[3].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[3][j].chr, gene[3][j].gid, gene[3][j].biotype, gene[3][j].name, gene[3][j].strand, gene[3][j].eid,
				gene[3][j]._start, gene[3][j]._end);
			}
		}

		if (cnv[i].chr == "5"){
			for (int j = 0; j < gene[4].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[4][j].chr, gene[4][j].gid, gene[4][j].biotype, gene[4][j].name, gene[4][j].strand, gene[4][j].eid,
				gene[4][j]._start, gene[4][j]._end);
			}
		}
		
		if (cnv[i].chr == "6"){
			for (int j = 0; j < gene[5].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[5][j].chr, gene[5][j].gid, gene[5][j].biotype, gene[5][j].name, gene[5][j].strand, gene[5][j].eid,
				gene[5][j]._start, gene[5][j]._end);
			}
		}
		if (cnv[i].chr == "7"){
			for (int j = 0; j < gene[6].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[6][j].chr, gene[6][j].gid, gene[6][j].biotype, gene[6][j].name, gene[6][j].strand, gene[6][j].eid,
				gene[6][j]._start, gene[6][j]._end);
			}
		}
		if (cnv[i].chr == "8"){
			for (int j = 0; j < gene[7].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[7][j].chr, gene[7][j].gid, gene[7][j].biotype, gene[7][j].name, gene[7][j].strand, gene[7][j].eid,
				gene[7][j]._start, gene[7][j]._end);
			}
		}
		if (cnv[i].chr == "9"){
			for (int j = 0; j < gene[8].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[8][j].chr, gene[8][j].gid, gene[8][j].biotype, gene[8][j].name, gene[8][j].strand, gene[8][j].eid,
				gene[8][j]._start, gene[8][j]._end);
			}
		}
		if (cnv[i].chr == "10"){
			for (int j = 0; j < gene[9].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[9][j].chr, gene[9][j].gid, gene[9][j].biotype, gene[9][j].name, gene[9][j].strand, gene[9][j].eid,
				gene[9][j]._start, gene[9][j]._end);
			}
		}
		if (cnv[i].chr == "11"){
			for (int j = 0; j < gene[10].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[10][j].chr, gene[10][j].gid, gene[10][j].biotype, gene[10][j].name, gene[10][j].strand, gene[10][j].eid,
				gene[10][j]._start, gene[10][j]._end);
			}
		}
		if (cnv[i].chr == "12"){
			for (int j = 0; j < gene[11].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[11][j].chr, gene[11][j].gid, gene[11][j].biotype, gene[11][j].name, gene[11][j].strand, gene[11][j].eid,
				gene[11][j]._start, gene[11][j]._end); 
			}
		}
		if (cnv[i].chr == "13"){
			for (int j = 0; j < gene[12].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[12][j].chr, gene[12][j].gid, gene[12][j].biotype, gene[12][j].name, gene[12][j].strand, gene[12][j].eid,
				gene[12][j]._start, gene[12][j]._end);
			}
		}
		if (cnv[i].chr == "14"){
			for (int j = 0; j < gene[13].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[13][j].chr, gene[13][j].gid, gene[13][j].biotype, gene[13][j].name, gene[13][j].strand, gene[13][j].eid,
				gene[13][j]._start, gene[13][j]._end);
			}
		}
		if (cnv[i].chr == "15"){
			for (int j = 0; j < gene[14].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[14][j].chr, gene[14][j].gid, gene[14][j].biotype, gene[14][j].name, gene[14][j].strand, gene[14][j].eid,
				gene[14][j]._start, gene[14][j]._end);
			}
		}
		if (cnv[i].chr == "16"){
			for (int j = 0; j < gene[15].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[15][j].chr, gene[15][j].gid, gene[15][j].biotype, gene[15][j].name, gene[15][j].strand, gene[15][j].eid,
				gene[15][j]._start, gene[15][j]._end);
			}
		}
		if (cnv[i].chr == "17"){
			for (int j = 0; j < gene[16].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[16][j].chr, gene[16][j].gid, gene[16][j].biotype, gene[16][j].name, gene[16][j].strand, gene[16][j].eid,
				gene[16][j]._start, gene[16][j]._end);
			}
		}
		if (cnv[i].chr == "18"){
			for (int j = 0; j < gene[17].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[17][j].chr, gene[17][j].gid, gene[17][j].biotype, gene[17][j].name, gene[17][j].strand, gene[17][j].eid,
				gene[17][j]._start, gene[17][j]._end);
			}
		}
		if (cnv[i].chr == "19"){
			for (int j = 0; j < gene[18].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[18][j].chr, gene[18][j].gid, gene[18][j].biotype, gene[18][j].name, gene[18][j].strand, gene[18][j].eid,
				gene[18][j]._start, gene[18][j]._end);
			}
		}
		if (cnv[i].chr == "20"){
			for (int j = 0; j < gene[19].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[19][j].chr, gene[19][j].gid, gene[19][j].biotype, gene[19][j].name, gene[19][j].strand, gene[19][j].eid,
				gene[19][j]._start, gene[19][j]._end);
			}
		}
		if (cnv[i].chr == "21"){
			for (int j = 0; j < gene[20].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[20][j].chr, gene[20][j].gid, gene[20][j].biotype, gene[20][j].name, gene[20][j].strand, gene[20][j].eid,
				gene[20][j]._start, gene[20][j]._end);
			}
		}
		if (cnv[i].chr == "22"){
			for (int j = 0; j < gene[21].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[21][j].chr, gene[21][j].gid, gene[21][j].biotype, gene[21][j].name, gene[21][j].strand, gene[21][j].eid,
				gene[21][j]._start, gene[21][j]._end);
			}
		}
		if (cnv[i].chr == "X"){
			for (int j = 0; j < gene[22].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[22][j].chr, gene[22][j].gid, gene[22][j].biotype, gene[22][j].name, gene[22][j].strand, gene[22][j].eid,
				gene[22][j]._start, gene[22][j]._end);
			}
		}
		if (cnv[i].chr == "Y"){
			for (int j = 0; j < gene[23].size(); j++){
				check_and_output(cnv[i].chr, cnv[i]._start, cnv[i]._end, cnv[i+1]._end, cnv[i].value,
				gene[23][j].chr, gene[23][j].gid, gene[23][j].biotype, gene[23][j].name, gene[23][j].strand, gene[23][j].eid,
				gene[23][j]._start, gene[23][j]._end);
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