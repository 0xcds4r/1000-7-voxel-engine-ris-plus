#include "TimeCycle.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// float fTemp = bDayStatus ? 1.770f : 0.410f;

float fSLC_R = 0.0f;
float fSLC_G = 0.0f;
float fSLC_B = 0.0f;

float fSLC_ADD_R = 0.0f;
float fSLC_ADD_G = 0.0f;
float fSLC_ADD_B = 0.0f;

float fBrightness = 0.0f;
float fGamma = 0.0f;

uint32_t GetTickCount();
uint32_t m_dwDayLightTick = 0;
uint32_t iWorldTickOver = 0;
uint32_t iWorldTickGlobal = 0;

#define WORLD_MAX_TICKS 24000

float fScrapCycle[WORLD_MAX_TICKS+1] = { 0.0f };

void TimeCycle::setup()
{
	fSLC_R = (0.1*2);
	fSLC_G = (0.15*2);
	fSLC_B = (0.2*2);
	fSLC_ADD_R = 0.0f;
	fSLC_ADD_G = 0.0f;
	fSLC_ADD_B = 0.0f;
	fBrightness = 1.770f;
	fGamma = 1.6f;

	iWorldTickOver = WORLD_MAX_TICKS;

	float fMeltion = 0.25f;

	for(int i = WORLD_MAX_TICKS; i > 0; i--)
	{	
		if(i > (WORLD_MAX_TICKS / 4 ))
		{
			if(fMeltion < 2.75f) {
				fMeltion += 0.0004166666f; 
			}
		}
		else 
		{
			if(fMeltion > 0.15f) {
				fMeltion -= 0.0004166666f; 
			}
		}

		fScrapCycle[i] = fMeltion;
	}

	m_dwDayLightTick = GetTickCount();
}

int iGlobalStepCycleInstant = -1;

void TimeCycle::update(Shader* shader)
{
	shader->uniform1f("u_gamma", fGamma);	
	shader->uniform3f("u_skyLightColor", (fSLC_R) + fBrightness + fSLC_ADD_R, (fSLC_G) + fBrightness + fSLC_ADD_G, (fSLC_B) + fBrightness + fSLC_ADD_B);
	TimeCycle::process();

	if(iWorldTickGlobal < 19000)
		glClearColor(0.5f,0.8f,0.9f,1.0f);
	else
		glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void TimeCycle::setTickStep(int iStep)
{
	iGlobalStepCycleInstant = iStep; 
}

void TimeCycle::setGlobalTick(int iTick)
{
	iWorldTickGlobal = iTick;
}

uint32_t TimeCycle::getGlobalTick()
{
	return iWorldTickGlobal;
}

bool bAlwaysSkipFrame = false;
void TimeCycle::process()
{
	int iTimeGrant = 50; // 1 tact
	bool bTime = GetTickCount() - m_dwDayLightTick >= (iTimeGrant);
	bool bSkipFrame = iGlobalStepCycleInstant != -1 ? true : bTime;

	if(bSkipFrame || bAlwaysSkipFrame) 
	{
		static bool bStage = false;

		if(!bStage)
		{
			if(iWorldTickGlobal != WORLD_MAX_TICKS) 
			{
				iWorldTickGlobal += bAlwaysSkipFrame ? 5 : 1;

				if(fScrapCycle[iWorldTickGlobal] != 0.0f)
					fBrightness = fScrapCycle[iWorldTickGlobal];
			}
			else
			{
				iWorldTickGlobal = 0;
				bStage = true;
			}
		}
		else
		{
			if(iWorldTickGlobal != WORLD_MAX_TICKS) 
			{
				iWorldTickGlobal += bAlwaysSkipFrame ? 5 : 1;

				if(fScrapCycle[iWorldTickGlobal] != 0.0f)
					fBrightness = fScrapCycle[iWorldTickGlobal];
			}
			else
			{
				iWorldTickGlobal = 0;
				bStage = false;
			}
		}

		m_dwDayLightTick = GetTickCount();
	}
}