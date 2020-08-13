#include "DebugCode.h"

void AverageFrames::ResetAveFrames(int frames, byte nMaxCount)
{
	if (nCountedFrames < nMaxCount)
	{
		AddedFrames += frames;
		nCountedFrames++;
		Average = AddedFrames / nCountedFrames;
	}

	
}




