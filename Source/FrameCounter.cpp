#include "FrameCounter.h"
FrameCounter::FrameCounter()
{
	initTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> tempPoint = deltaTime - initTime;
	elapseTime = tempPoint.count();
}


void FrameCounter::updateD()
{
	std::chrono::duration<float> timePoint;
	deltaTime = std::chrono::high_resolution_clock::now();
	timePoint = deltaTime - initTime;
	elapseTime = timePoint.count();
	tickframes++;
}

void FrameCounter::updateI()
{
	if (elapseTime >= 1)
	{
		frames = tickframes;
		tickframes = 0;
		initTime = std::chrono::high_resolution_clock::now();
	}
}