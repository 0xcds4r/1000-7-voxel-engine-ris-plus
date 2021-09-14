#ifndef GUI_H_
#define GUI_H_

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"
#include "chat.h"

#define SCREEN_X 1920
#define SCREEN_Y 1080
#define SCREEN_X_MULT 1/SCREEN_X
#define SCREEN_Y_MULT 1/SCREEN_Y

class gui
{
public:
	static ImFont* m_pGUIFont;

	static ImFont* loadFontFromPath(char *path, float defFontSize = 30.0f);
	static void initialize();
	static void drawText(float font_size, ImFont* font, ImVec2& posCur, ImU32 col, bool bOutline, const char* text_begin, const char* text_end = nullptr);
	
	static void draw();
	static void drawDebug();
	static void render();

	static ImFont* getFont();
};

#endif