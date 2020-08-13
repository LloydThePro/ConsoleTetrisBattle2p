#ifndef FRAME_COUNTER_SYS_H
#define FRAME_COUNTER_SYS_H
#include <chrono>


struct FrameCounter
{
	std::chrono::high_resolution_clock::time_point initTime;
	std::chrono::high_resolution_clock::time_point deltaTime;
	float elapseTime = 0;
	int tickframes = 0;
	int frames = 0;
	FrameCounter();
	void updateD();
	void updateI();

};

#endif // !FRAME_COUNTER_SYS_H

