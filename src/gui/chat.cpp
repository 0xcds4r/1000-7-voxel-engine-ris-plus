#include "gui.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../window/Events.h"

#include <algorithm>
#include <string>
#include <chrono>

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

void chat::draw()
{                  
	if(!chat::isActive()) {
		return;
	}

	ImGuiIO& io = ImGui::GetIO();

	static std::string coastStr = std::string("");
	
	char buf[2048] = { '\0' }; 
	sprintf(buf, "%s", coastStr.c_str());
	chat::drawInput(buf);

	static uint32_t bpLastTick = GetTickCount();
	static int iSpeedErence = 0;

	if (Events::pressed(GLFW_KEY_BACKSPACE) && GetTickCount() - bpLastTick >= 90 - iSpeedErence) 
	{
		if(strlen(coastStr.c_str())) 
		{
			coastStr.erase(coastStr.end()-1); 
			bpLastTick = GetTickCount();

			if(iSpeedErence < 55) {
				iSpeedErence += 5;
			}
		}
	} else if(!Events::pressed(GLFW_KEY_BACKSPACE) && GetTickCount() - bpLastTick >= 90 - iSpeedErence) iSpeedErence = 0;

	if(strlen(coastStr.c_str()) >= 64) {
		return;
	}

	if (Events::jpressed(GLFW_KEY_Q)) {
		coastStr = coastStr + std::string("q");
	}

	if (Events::jpressed(GLFW_KEY_W)) {
		coastStr = coastStr + std::string("w");
	}

	if (Events::jpressed(GLFW_KEY_E)) {
		coastStr = coastStr + std::string("e");
	}

	if (Events::jpressed(GLFW_KEY_R)) {
		coastStr = coastStr + std::string("r");
	}

	if (Events::jpressed(GLFW_KEY_T)) {
		coastStr = coastStr + std::string("t");
	}

	if (Events::jpressed(GLFW_KEY_Y)) {
		coastStr = coastStr + std::string("y");
	}
}