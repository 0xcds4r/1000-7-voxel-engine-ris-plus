#ifndef CHAT_H_
#define CHAT_H_

class chat
{
public:
	static bool m_bIsChatActive;

	static void initialize();
	static void drawInput(const char* str);
	static void draw();
	static bool isActive();
	static void toggle();
	static void addChar(const char* c);
	static void backspaceCheck();
	
};

#endif