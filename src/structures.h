#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include "libraries.h"

struct cnvSegs{
	std::string chr;
	int _start;
	int _end;
	float value;
};

struct NewSegmentFrame{
	std::string chr;
	int _start;
	int _end;
	float rdValue;
	float svValue;
};

struct cnvFrame{
	std::string chr;
	int _start;
	int _end;
	float value;
	float rdValue;
	float svValue;
	std::string comment;
	
	cnvFrame(std::string chr, int _start, int _end, float value, float rdValue, float svValue, std::string comment) : 
	chr(chr), _start(_start), _end(_end), value(value), rdValue(rdValue), svValue(svValue), comment(comment) {}
};

struct geneFrame{
	std::string chr;
	std::string gid; //Gene ID
	std::string biotype;
	std::string name;
	std::string strand;
	std::string eid; //Exon ID
	int _start; // Exon start
	int _end; // Exon end
};

struct cnvNatorFrame{
	std::string mutation;
	std::string chr;
	int _start;
	int _end;
};

/*extern std::vector <cnvNatorFrame> cnvNator;
extern std::vector <cnvNatorFrame> cnvNatorXY;*/
//extern GtkWidget *runLabel;
extern std::string gender;
extern std::string match;
extern std::string filename;
extern std::string filenameXY;
extern std::string readDepth_filepath;
extern std::string svdetect_filepath;
extern std::string cnvNator_option;
extern std::string cnvNator_filepath;

#endif