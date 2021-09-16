#ifndef VOXELS_TIMECYCLE_H_
#define VOXELS_TIMECYCLE_H_

#include "../graphics/Shader.h"

class TimeCycle
{
public:
	static void setup();
	static void update(Shader*);
	static void process();
	static void setTickStep(int);
	static void setGlobalTick(int);
	static uint32_t getGlobalTick();
	
};

#endif