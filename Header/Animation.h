#ifndef ANIM_SYS_H
#define ANIM_SYS_H
#include "UtilStructs.h"
#include <iostream>
#include <string>

typedef struct _Animframes
{
	byte nFrames = 0;
	vec2by FrameSz = { 0,0 };
	char** frames = nullptr;
}AnimFrames;


class AnimSys
{
private:
	
public:
	AnimFrames frames;
	vec2s Pos = { 0,0 };
	AnimSys(byte, vec2by, vec2s);
	void FreeMem();
	void LoadAnimFromFile(const char *);
};

#endif // !ANIM_SYS_H

