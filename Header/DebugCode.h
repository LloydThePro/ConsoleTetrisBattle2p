#ifndef DEBUG_CODE_H
#define DEBUG_CODE_H
#include "UtilStructs.h"

struct AverageFrames
{
	long int AddedFrames = 0;
	int nCountedFrames = 0;
	int Average = 0;
	void ResetAveFrames(int frames, byte nMaxCount);
	
};

#endif // !DEBUG_CODE_H

