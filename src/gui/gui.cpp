#include "gui.h"

#include "../window/Window.h"

#include <algorithm>
#include <string>
#include <chrono>

ImFont* gui::m_pGUIFont = 0;

uint32_t GetTickCount();

void gui::initialize()
{
	// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup default font
    gui::m_pGUIFont = gui::loadFontFromPath("C:\\Windows\\Fonts\\Arial.ttf", 30.0f);

    // Setup Platform/Renderer
    ImGui_ImplGlfw_InitForOpenGL(Window::getWindow(), false);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Setup random logic
    srand(time(NULL));

    // Setup interface logic
    chat::initialize();
}

ImFont* gui::getFont()
{
	return gui::m_pGUIFont;
}

ImFont* gui::loadFontFromPath(char *path, float defFontSize)
{
    ImGuiIO &io = ImGui::GetIO();

    static const ImWchar ranges[] =
    {
            0x0020, 0x00FF, 
            0x20AC, 0x20AC, 
            0x2122, 0x2122, 
            0x2196, 0x2196, 
            0x21D6, 0x21D6, 
            0x2B01, 0x2B01, 
            0x2B09, 0x2B09, 
            0x2921, 0x2922, 
            0x263A, 0x263A, 
            0x266A, 0x266A, 
            0x2191, 0x2191, 
            0x2193, 0x2193, 
            0x2022, 0x2022, 
            0x221A, 0x221A, 
            0x03C0, 0x03C0, 
            0x00F7, 0x00F7, 
            0x00D7, 0x00D7, 
            0x00B6, 0x00B6, 
            0x2206, 0x2206, 
            0x00A3, 0x00A3, 
            0x00A2, 0x00A2, 
            0x20AC, 0x20AC, 
            0x00A5, 0x00A5, 
            0x005E, 0x005E, 
            0x00B0, 0x00B0, 
            0x003D, 0x003D, 
            0x007B, 0x007B, 
            0x007D, 0x007D, 
            0x005C, 0x005C, 
            0x0025, 0x0025, 
            0x00A9, 0x00A9, 
            0x00AE, 0x00AE, 
            0x2122, 0x2122, 
            0x2713, 0x2713, 
            0x083F, 0x083F,
            0x005B, 0x005B, 
            0x005D, 0x005D, 
            0x3000, 0x30FF, 
            0x31F0, 0x31FF, 
            0xFF00, 0xFFEF, 
            0x2010, 0x205E, 
            0x0102, 0x0103,
            0x0110, 0x0111,
            0x0128, 0x0129,
            0x0168, 0x0169,
            0x01A0, 0x01A1,
            0x01AF, 0x01B0,
            0x1EA0, 0x1EF9,
            0x0400, 0x052F, 
            0x0400, 0x04FF, 
            0x0E00, 0x0E7F, 
            0x2DE0, 0x2DFF, 
            0xA640, 0xA69F, 
            0xF020, 0xF0FF, 
            0
    };

    ImFont* pFont = io.Fonts->AddFontFromFileTTF(path, defFontSize, nullptr, ranges);

    return pFont;
}

void gui::drawText(float font_size, ImFont* font, ImVec2& posCur, ImU32 col, bool bOutline, const char* text_begin, const char* text_end)
{
	ImGuiIO& io = ImGui::GetIO();

    int iOffset = 2;

    if (bOutline)
    {
        // left
        posCur.x -= iOffset;
        ImGui::GetBackgroundDrawList()->AddText(font, font_size, posCur, ImColor(0,0,0,255), text_begin, text_end);
        posCur.x += iOffset;
        // right
        posCur.x += iOffset;
        ImGui::GetBackgroundDrawList()->AddText(font, font_size, posCur, ImColor(0,0,0,255), text_begin, text_end);
        posCur.x -= iOffset;
        // above
        posCur.y -= iOffset;
        ImGui::GetBackgroundDrawList()->AddText(font, font_size, posCur, ImColor(0,0,0,255), text_begin, text_end);
        posCur.y += iOffset;
        // below
        posCur.y += iOffset;
        ImGui::GetBackgroundDrawList()->AddText(font, font_size, posCur, ImColor(0,0,0,255), text_begin, text_end);
        posCur.y -= iOffset;
    }

    ImGui::GetBackgroundDrawList()->AddText(font, font_size, posCur, col, text_begin, text_end);
}

void gui::drawDebug()
{
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 vecText = ImVec2(133, 555);

	char frameBufferInfo[0xFF] = { '\0' };
	sprintf(frameBufferInfo, "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	gui::drawText(30.0f, gui::getFont(), vecText, ImColor(255, 222, 255, 255), true, frameBufferInfo);
}

void gui::draw()
{
	ImGuiIO& io = ImGui::GetIO();

	gui::drawDebug();
	chat::draw();
}

void gui::render()
{
	ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
   	gui::draw();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}