#include"MouseBase.h"
#include"PageBase.h"
#include<iostream>
#include<windows.h>

Mouse::Mouse() {
	hMouseOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hMouseForeground = GetForegroundWindow();
	pMousePos.x = pMousePos.y = 0;
	cMousePos.X = cMousePos.Y = 0;
	GetCurrentConsoleFont(hMouseOutput, FALSE, &consoleFont);
	MoveWindow(hMouseForeground, 0, 0, CLASSIC_WIDTH, CLASSIC_HEIGHT, TRUE);
}

std::string Mouse::HoverAndClick(PageUnitEx* sourceText) {
	short x;
	short y;
	int counter = MOUSE_DETECT_GROUPTIMES;
	std::string defaultReturn = DEFAULT_RETURN;
	while (counter--) {
		GetCursorPos(&pMousePos);
		ScreenToClient(hMouseForeground, &pMousePos);
		x = (short)(pMousePos.x / consoleFont.dwFontSize.Y * FONT_RATIO);
		y = (short)(pMousePos.y / consoleFont.dwFontSize.Y / ROW_INTERVAL);
		cMousePos = { x,y };
		readStr = ReadCursorChars(sourceText);
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

std::string Mouse::ReadCursorChars(PageUnitEx* sourceText) {
	COORD floatingLeftPos = cMousePos;
	COORD floatingRightPos = cMousePos;
	floatingRightPos.X++;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	std::string readString;
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
	if (readString != readStr)PopLastStr(sourceText);
	return readString;
}

void Mouse::PopLastStr(PageUnitEx* sourceText) {
	Page tmpPage;
	PageUnitEx* tmpPointer = NULL;
	if (!readStr.empty())tmpPointer = sourceText->FindByText(readStr);
	if (tmpPointer != NULL) tmpPage.PointPaint(tmpPointer->GetPageUnit());
}