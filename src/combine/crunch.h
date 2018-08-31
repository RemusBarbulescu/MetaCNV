#ifndef _CRUNCH_H_
#define _CRUNCH_H_

#include "../libraries.h"
#include "../structures.h"

bool sortData(const NewSegmentFrame& i, const NewSegmentFrame& j){
    if (i.chr < j.chr)
        return true;
    else if (i.chr > j.chr)
        return false;

    if (i._start < j._start)
        return true;
    else if (i._start > j._start)
        return false;

    return false;
}

extern bool crunch (std::vector <cnvSegs> &rd, std::vector <cnvSegs> &sv,
std::vector <NewSegmentFrame> &segment,std::vector <NewSegmentFrame> &segmentXY){
	

	std::vector <NewSegmentFrame> buffer;
	std::vector <NewSegmentFrame> bufferXY;
	
	NewSegmentFrame segBuffer;
	
	// Inserting on one column start/end values
	for ( int i = 0; i < rd.size(); ++i ){
		segBuffer.chr = rd[i].chr; 
		segBuffer._start = rd[i]._start; // inserting start value
        //segBuffer._end = 0;
		segBuffer._end = rd[i]._end; 
		segBuffer.rdValue = rd[i].value;
		segBuffer.svValue = 0.0;
		
		if ( segBuffer.chr != "Y" && segBuffer.chr != "X" )
			buffer.push_back ( segBuffer );
		else
			bufferXY.push_back ( segBuffer );
		

		segBuffer._start = rd[i]._end; // inserting end value
		if ( segBuffer.chr != "Y" && segBuffer.chr != "X" )
			buffer.push_back ( segBuffer );
		else
			bufferXY.push_back ( segBuffer );
	}
	
	// same as above but for SVdetect values
	for ( int i = 0; i < sv.size(); ++i ){
		segBuffer.chr = sv[i].chr; 
		segBuffer._start = sv[i]._start; 
        //segBuffer._end = 0;
		segBuffer._end = sv[i]._end; 
		segBuffer.rdValue = 0.0;
		segBuffer.svValue = sv[i].value;
		if (segBuffer.chr != "Y" && segBuffer.chr != "X")
			buffer.push_back ( segBuffer );
		else
			bufferXY.push_back ( segBuffer );
			
		segBuffer._start = sv[i]._end; 
		if (segBuffer.chr != "Y" && segBuffer.chr != "X")
			buffer.push_back ( segBuffer );
		else
			bufferXY.push_back ( segBuffer );
	}
	
	std::sort (buffer.begin(), buffer.end(), sortData);
	std::sort (bufferXY.begin(), bufferXY.end(), sortData);
	
	int j = 0, k = 0, counter = 0;
	
	for ( int i = 0; i < buffer.size() - 1; ++i){
		
		if (buffer[i].chr == buffer[i+1].chr){
			
			if (i + 1 < buffer.size() - 1){
				
				if ((buffer[i+1]._start - buffer[i]._start) > 1){
					
					segBuffer.chr = buffer[i].chr;
					segBuffer._start = buffer[i]._start;
					segBuffer._end = buffer[i+1]._start;
					
					for (j; j < rd.size(); ++j){
						
						if (rd[j].chr == segBuffer.chr){
							
							if (segBuffer._start >= rd[j]._start && segBuffer._start <= rd[j]._end){
							
								segBuffer.rdValue = rd[j].value;
								break;
							}
							else{
								if (rd[j+1]._start >= segBuffer._start && rd[j+1]._start <= segBuffer._end){
								
									segBuffer.rdValue = rd[j+1].value;
									++j;
									break;
								}
								else{
									segBuffer.rdValue = 0;
									break;
								}
							}
						}
					}
					
					for (k; k < sv.size(); ++k){
						
						if (sv[k].chr == segBuffer.chr){
							
							if (segBuffer._start >= sv[k]._start && segBuffer._start <= sv[k]._end){
								
								segBuffer.svValue = sv[k].value;
								break;
							}
							else{
								if (sv[k+1]._start >= segBuffer._start && sv[k+1]._start <= segBuffer._end){
									
									segBuffer.svValue = sv[k+1].value;
									++k;
									break;
								}
								else{
									
									segBuffer.svValue = 0;
									break;
								}
							}
						}
					}

					segment.push_back(segBuffer);
					
				}
				else{ continue; }
			}
			else{ break; }
		}
		else{ continue; }
		
	}
	
	j = 0;
	k = 0;
	for ( int i = 0; i < bufferXY.size() - 1; ++i){
		
		
		if (bufferXY[i].chr == bufferXY[i+1].chr){
			
			if (i + 1 < bufferXY.size() - 1){
				
				if ((bufferXY[i+1]._start - bufferXY[i]._start) > 1){
					
					segBuffer.chr = bufferXY[i].chr;
					segBuffer._start = bufferXY[i]._start;
					segBuffer._end = bufferXY[i+1]._start;
					
					for (j; j < rd.size(); ++j){
						
						if (rd[j].chr == segBuffer.chr){
							
							if (segBuffer._start >= rd[j]._start && segBuffer._start <= rd[j]._end){
								
								segBuffer.rdValue = rd[j].value;
								break;
							}
							else{
								if (rd[j+1]._start >= segBuffer._start && rd[j+1]._start <= segBuffer._end){
									
									segBuffer.rdValue = rd[j+1].value;
									++j;
									break;
								}
								else{
									segBuffer.rdValue = 0;
									break;
								}
							}
						}
					}
					
					for (k; k < sv.size(); ++k){
						
						if (sv[k].chr == segBuffer.chr){
							
							if (segBuffer._start >= sv[k]._start && segBuffer._start <= sv[k]._end){
								
								segBuffer.svValue = sv[k].value;
								break;
							}
							else{
								if (sv[k+1]._start >= segBuffer._start && sv[k+1]._start <= segBuffer._end){
									
									segBuffer.svValue = sv[k+1].value;
									++k;
									break;
								}
								else{
									
									segBuffer.svValue = 0;
									break;
								}
							}
						}
					}

					segmentXY.push_back(segBuffer);
					
				}
				else{ continue; }
			}
			else{ break; }
		}
		else{ continue; }
		
	}
	std::cout << counter << std::endl;
}

#endif