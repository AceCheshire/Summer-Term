#include<iostream>
#include<windows.h>
#include"PageConst.h"
#include"MouseConst.h"
using namespace std;

Mouse::Mouse() {
	hMouseOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hMouseForeground = GetForegroundWindow();
	GetCurrentConsoleFont(hMouseOutput, FALSE, &consoleFont);
	pMousePos.x = pMousePos.y = 0;
	cMousePos.X = cMousePos.Y = 0;
	MoveWindow(hMouseForeground, 0, 0, 2560, 1440, TRUE);
}

std::string Mouse::HoverAndClick() {
	short x;
	short y;
	int counter = MOUSE_DETECT_GROUPTIMES;
	string defaultReturn = DEFAULT_RETURN;
	while (counter--) {
		GetCursorPos(&pMousePos);
		ScreenToClient(hMouseForeground, &pMousePos);
		x = (short)(pMousePos.x / consoleFont.dwFontSize.Y * FONT_PROPORTION);
		y = (short)(pMousePos.y / consoleFont.dwFontSize.Y - WINDOW_TOP);
		cMousePos = { x,y };
		readStr = ReadCursorChars();
		if (KEY_DOWN(VK_LBUTTON) && !readStr.empty())return readStr;
		Sleep(MOUSE_DETECT_INTERVAL);
	}
	return defaultReturn;
}

char Mouse::ReadChar(COORD cPos) {
	TCHAR cursorChar[1];
	DWORD dwChar;
	if (ReadConsoleOutputCharacterW(hMouseOutput, cursorChar, 1, cPos, &dwChar))
		return (char)cursorChar[0];
	else return ' ';
}

std::string Mouse::ReadCursorChars() {
	COORD floatingLeftPos = cMousePos;
	COORD floatingRightPos = cMousePos;
	floatingRightPos.X++;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	string readString;
	char readChar;
	GetConsoleScreenBufferInfo(hMouseOutput, &csbi);
	while (((readChar = ReadChar(floatingRightPos)) != ' ') && (readChar != '\t') &&
		(readChar != '\n') && (readChar != '\0') &&
		(floatingRightPos.X <= csbi.srWindow.Right - csbi.srWindow.Left-1)) {
		char readChars[2] = { readChar };
		SetConsoleTextAttribute(hMouseOutput, BACKGROUND_INTENSITY);
		SetConsoleCursorPosition(hMouseOutput, floatingRightPos);
		printf("%c", readChar);
		SetConsoleTextAttribute(hMouseOutput, GROUND_DEFAULT);
		readString.append(readChars);
		floatingRightPos.X++;
	}
	while (((readChar = ReadChar(floatingLeftPos)) != ' ') && (readChar != '\t') &&
		(readChar != '\n') && (readChar != '\0') && (floatingLeftPos.X >= 0)) {
		char readChars[2] = { readChar };
		SetConsoleTextAttribute(hMouseOutput, BACKGROUND_INTENSITY);
		SetConsoleCursorPosition(hMouseOutput, floatingLeftPos);
		printf("%c", readChar);
		SetConsoleTextAttribute(hMouseOutput, GROUND_DEFAULT);
		readString.insert(0, readChars);
		floatingLeftPos.X--;
	}
	return readString;
}