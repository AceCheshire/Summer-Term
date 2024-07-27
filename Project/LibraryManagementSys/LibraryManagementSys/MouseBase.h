#pragma once
#include"PageBase.h"
#include<windows.h>
#include<iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define MOUSE_DETECT_INTERVAL 10
#define MOUSE_DETECT_GROUPTIMES 30
#define DEFAULT_RETURN "_NULL_"
#define FONT_RATIO 16 / 9.3
#define ROW_INTERVAL 1.2
#define CLASSIC_WIDTH 2560
#define CLASSIC_HEIGHT 1440

class Mouse {
public:
	Mouse();
	std::string HoverAndClick(PageUnitEx*);
protected:
	char ReadChar(COORD);
	std::string ReadCursorChars(PageUnitEx*);
	void PopLastStr(PageUnitEx*);
	HANDLE hMouseOutput;
	HWND hMouseForeground;
	POINT pMousePos;
	COORD cMousePos;
	CONSOLE_FONT_INFO consoleFont;
	std::string readStr;
};