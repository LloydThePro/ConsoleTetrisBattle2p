#include "Animation.h"



void AnimSys::LoadAnimFromFile(const char * file)
{
	std::ifstream data(file);
	if (!data.is_open())return;

	if (AnimSys::frames.frames == nullptr)
	{
		AnimSys::frames.frames = new char*[AnimSys::frames.nFrames];
	}
	else
		FreeMem();
	
	
	std::string copy;
	
	for (byte i = 0; i < AnimSys::frames.nFrames; i++)
	{
		std::string copy2;
		for (byte j = 0; j < AnimSys::frames.FrameSz.Y; j++)
		{
			std::getline(data, copy);
			copy2 += copy;
		}
		AnimSys::frames.frames[i] = new char[AnimSys::frames.FrameSz.X * AnimSys::frames.FrameSz.Y];
		memcpy(AnimSys::frames.frames[i], &copy2[0], AnimSys::frames.FrameSz.X * AnimSys::frames.FrameSz.Y);
		
	}
	

}

AnimSys::AnimSys(byte nFrames, vec2by FramesSz, vec2s APos)
{
	AnimSys::frames.FrameSz = FramesSz;
	AnimSys::frames.nFrames = nFrames;
	AnimSys::Pos = APos;
}


void AnimSys::FreeMem()
{
	if (AnimSys::frames.frames != nullptr)
	{
		for (byte i = 0; i < AnimSys::frames.nFrames; i++)
		{
			delete[] AnimSys::frames.frames[i];
		}
		delete[] AnimSys::frames.frames;
	}
}
