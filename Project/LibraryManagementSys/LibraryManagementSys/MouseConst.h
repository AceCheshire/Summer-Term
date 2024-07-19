#pragma once
#include<windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define MOUSE_DETECT_INTERVAL 5
#define MOUSE_DETECT_GROUPTIMES 5
#define DEFAULT_RETURN "_NULL_"
#define FONT_PROPORTION 16 / 9.3
#define WINDOW_TOP 4

class Mouse {
public:
	Mouse();
	std::string HoverAndClick();
protected:
	char ReadChar(COORD);
	std::string ReadCursorChars();
	HANDLE hMouseOutput;
	HWND hMouseForeground;
	POINT pMousePos;
	COORD cMousePos;
	CONSOLE_FONT_INFO consoleFont;
	std::string readStr;
};