#pragma once
#include<windows.h>
#include<iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define MOUSE_DETECT_INTERVAL 100
#define MOUSE_DETECT_GROUPTIMES 10
#define DEFAULT_RETURN "_NULL_"
#define FONT_RATIO 16 / 9.3
#define ROW_INTERVAL 1.2

class Mouse {
public:
	Mouse();
	std::string HoverAndClick();
	int GetTimes() const { return readTimes; }
	void ResetTimes() { readTimes = 0; }
protected:
	char ReadChar(COORD);
	std::string ReadCursorChars();
	HANDLE hMouseOutput;
	HWND hMouseForeground;
	POINT pMousePos;
	COORD cMousePos;
	CONSOLE_FONT_INFO consoleFont;
	std::string readStr;
	int readTimes = 0;
};