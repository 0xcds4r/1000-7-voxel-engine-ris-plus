#include "gui.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../window/Events.h"
#include "../window/Camera.h"
#include "../voxels/Level.h"

#include <algorithm>
#include <string>
#include <chrono>

extern Camera* camera;

bool chat::m_bIsChatActive;
uint32_t GetTickCount();

void chat::initialize()
{
	chat::m_bIsChatActive = false;
}

void chat::toggle()
{
	chat::m_bIsChatActive ^= true;
}

bool chat::isActive()
{
	return chat::m_bIsChatActive;
}

void chat::drawInput(const char* str)
{
	ImGuiIO& io = ImGui::GetIO();

	float fRadius = 70.0f;
	float fFontSizePressive = 30.0f;
	float fFontAbuse = 3.5f;
	float fBoxMargin = 30.0f;

	ImGui::GetBackgroundDrawList()->AddRectFilled({fBoxMargin, io.DisplaySize.y - fRadius}, {io.DisplaySize.x - fBoxMargin, io.DisplaySize.y - 20.0f}, ImColor(30, 30, 32), 8.f, ImDrawCornerFlags_Left | ImDrawCornerFlags_Right);

	char buffer[2048] = { '\0' };
	sprintf(buffer, "%s", str);

	ImVec2 vecText = ImVec2(fBoxMargin + 15.0f, io.DisplaySize.y - (fRadius / 2) - (fFontSizePressive - fFontAbuse));
	gui::drawText(fFontSizePressive, gui::getFont(), vecText, ImColor(255, 222, 255, 255), true, buffer);

	// debug info
	char bufferLenInfo[0xFF] = { '\0' };
	sprintf(bufferLenInfo, "length: %d", strlen(str));
	ImVec2 vecTextInfo = ImVec2(25.0f, 120.0f);
	gui::drawText(30.0f, gui::getFont(), vecTextInfo, ImColor(255, 222, 255, 255), true, bufferLenInfo);
}

std::string coastStr = std::string("");
void chat::addChar(const char* c)
{
	coastStr = coastStr + std::string(c);
}

void chat::backspaceCheck()
{
	static uint32_t bpLastTick = GetTickCount();
	static int iSpeedErence = 0;

	if (Events::pressed(GLFW_KEY_BACKSPACE) && GetTickCount() - bpLastTick >= 200 - iSpeedErence) 
	{
		if(strlen(coastStr.c_str())) 
		{
			coastStr.erase(coastStr.end()-1); 
			bpLastTick = GetTickCount();

			if(iSpeedErence < 130) {
				iSpeedErence += 30;
			}
		}
	} else if(!Events::pressed(GLFW_KEY_BACKSPACE) && GetTickCount() - bpLastTick >= 200 - iSpeedErence) iSpeedErence = 0;
}

extern bool bDebugDraw;
extern bool bDayStatus;
void chat::draw()
{
	static bool bMCPrev = true;

	if(!chat::isActive()) 
	{
		bMCPrev = true;
		return;
	}

	if(bMCPrev) 
	{
		bMCPrev = false;
		return;
	}

	ImGuiIO& io = ImGui::GetIO(); 
	
	char buf[2048] = { '\0' }; 
	sprintf(buf, "%s", coastStr.c_str());
	chat::drawInput(buf);

	static uint32_t bpLastTick = GetTickCount();
	static int iSpeedErence = 0;

	chat::backspaceCheck();

	if (Events::jpressed(GLFW_KEY_ENTER)) 
	{
		char cmd[0xFF] = { '\0' };
		char arg1[0xFF] = { '\0' };
		char arg2[0xFF] = { '\0' };
		char arg3[0xFF] = { '\0' };
		char arg4[0xFF] = { '\0' };
		sscanf(buf, "%s %s %s %s %s", cmd, arg1, arg2, arg3, arg4);

		if(strcmp(cmd, "/debug") == 0) 
		{
			bDebugDraw ^= true;
		}
		else if(strcmp(cmd, "/time") == 0) 
		{
			if(strcmp(arg1, "set") == 0) 
			{
				if(strcmp(arg2, "day") == 0 || strcmp(arg2, "d") == 0 || strcmp(arg2, "0") == 0) 
				{
					bDayStatus = true;
				}
				else if(strcmp(arg2, "night") == 0 || strcmp(arg2, "n") == 0) 
				{
					bDayStatus = false;
				}
			}
			else if(strcmp(arg1, "query") == 0) 
			{
				// ...
			}
		}
		else if(strcmp(cmd, "/loc") == 0) 
		{
			// ...
		}
		else if(strcmp(cmd, "/setblock") == 0) 
		{
			if(arg1 && arg2 && arg3 && arg4)
			{
				int x = atoi(arg1);
				int y = atoi(arg2);
				int z = atoi(arg3);
				int id = atoi(arg4);
	
				Level::setBlock(x, y, z, id);
			}
		}

		coastStr.clear();
		chat::toggle();
		Events::toogleCursor();	
		return;
	}

	bool bCaps = Events::pressed(GLFW_KEY_LEFT_SHIFT) || Events::pressed(GLFW_KEY_RIGHT_SHIFT) || Events::pressed(GLFW_KEY_CAPS_LOCK);

	if(strlen(coastStr.c_str()) >= 64) {
		return;
	}

	if (Events::jpressed(GLFW_KEY_0)) {
		chat::addChar("0");
	}

	if (Events::jpressed(GLFW_KEY_1)) {
		chat::addChar("1");
	}

	if (Events::jpressed(GLFW_KEY_2)) {
		chat::addChar("2");
	}

	if (Events::jpressed(GLFW_KEY_3)) {
		chat::addChar("3");
	}

	if (Events::jpressed(GLFW_KEY_4)) {
		chat::addChar("4");
	}

	if (Events::jpressed(GLFW_KEY_5)) {
		chat::addChar("5");
	}

	if (Events::jpressed(GLFW_KEY_6)) {
		chat::addChar("6");
	}

	if (Events::jpressed(GLFW_KEY_7)) {
		chat::addChar("7");
	}

	if (Events::jpressed(GLFW_KEY_8)) {
		chat::addChar("8");
	}

	if (Events::jpressed(GLFW_KEY_9)) {
		chat::addChar("9");
	}

	if (Events::jpressed(GLFW_KEY_Q)) {
		chat::addChar(bCaps ? "Q" : "q");
	}

	if (Events::jpressed(GLFW_KEY_W)) {
		chat::addChar(bCaps ? "W" : "w");
	}

	if (Events::jpressed(GLFW_KEY_E)) {
		chat::addChar(bCaps ? "E" : "e");
	}

	if (Events::jpressed(GLFW_KEY_R)) {
		chat::addChar(bCaps ? "R" : "r");
	}

	if (Events::jpressed(GLFW_KEY_T)) {
		chat::addChar(bCaps ? "T" : "t");
	}

	if (Events::jpressed(GLFW_KEY_Y)) {
		chat::addChar(bCaps ? "Y" : "y");
	}

	if (Events::jpressed(GLFW_KEY_U)) {
		chat::addChar(bCaps ? "U" : "u");
	}

	if (Events::jpressed(GLFW_KEY_I)) {
		chat::addChar(bCaps ? "I" : "i");
	}

	if (Events::jpressed(GLFW_KEY_O)) {
		chat::addChar(bCaps ? "O" : "o");
	}

	if (Events::jpressed(GLFW_KEY_P)) {
		chat::addChar(bCaps ? "P" : "p");
	}

	if (Events::jpressed(GLFW_KEY_A)) {
		chat::addChar(bCaps ? "A" : "a");
	}

	if (Events::jpressed(GLFW_KEY_S)) {
		chat::addChar(bCaps ? "S" : "s");
	}

	if (Events::jpressed(GLFW_KEY_D)) {
		chat::addChar(bCaps ? "D" : "d");
	}

	if (Events::jpressed(GLFW_KEY_F)) {
		chat::addChar(bCaps ? "F" : "f");
	}

	if (Events::jpressed(GLFW_KEY_G)) {
		chat::addChar(bCaps ? "G" : "g");
	}

	if (Events::jpressed(GLFW_KEY_H)) {
		chat::addChar(bCaps ? "H" : "h");
	}

	if (Events::jpressed(GLFW_KEY_J)) {
		chat::addChar(bCaps ? "J" : "j");
	}

	if (Events::jpressed(GLFW_KEY_K)) {
		chat::addChar(bCaps ? "K" : "k");
	}

	if (Events::jpressed(GLFW_KEY_L)) {
		chat::addChar(bCaps ? "L" : "l");
	}

	if (Events::jpressed(GLFW_KEY_Z)) {
		chat::addChar(bCaps ? "Z" : "z");
	}

	if (Events::jpressed(GLFW_KEY_X)) {
		chat::addChar(bCaps ? "X" : "x");
	}

	if (Events::jpressed(GLFW_KEY_C)) {
		chat::addChar(bCaps ? "C" : "c");
	}

	if (Events::jpressed(GLFW_KEY_V)) {
		chat::addChar(bCaps ? "V" : "v");
	}

	if (Events::jpressed(GLFW_KEY_B)) {
		chat::addChar(bCaps ? "B" : "b");
	}

	if (Events::jpressed(GLFW_KEY_N)) {
		chat::addChar(bCaps ? "N" : "n");
	}

	if (Events::jpressed(GLFW_KEY_M)) {
		chat::addChar(bCaps ? "M" : "m");
	}

	if (Events::jpressed(GLFW_KEY_SLASH)) {
		chat::addChar("/");
	}

	if (Events::jpressed(GLFW_KEY_SPACE)) {
		chat::addChar(" ");
	}
}