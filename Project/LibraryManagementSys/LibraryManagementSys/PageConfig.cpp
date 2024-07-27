#include"ErrorBase.h"
#include"PageBase.h"
#include<iostream>
#include<windows.h>
using namespace std;

void PageUnitEx::Append(PageUnit& pageUnitListEnd) {
	if (nextUnit == NULL) {
		nextUnit = new PageUnitEx;
		nextUnit->thisUnit = pageUnitListEnd;
		nextUnit->nextUnit = NULL;
	}
	else nextUnit->Append(pageUnitListEnd);
}

PageUnitEx* PageUnitEx::FindByText(std::string text) {
	if (thisUnit.text == text)return this;
	else if (nextUnit != NULL)return nextUnit->FindByText(text);
	else return NULL;
}

void PageUnitEx::DeleteAll() {
	if (nextUnit != NULL)nextUnit->DeleteAll();
	delete this;
}

Page::Page() {
	hPageOutput = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Page::HideCursor() {
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = 0;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hPageOutput, &consoleCursor);
}

void Page::ReturnDefault() {
	int errnum_color = COLOR_ERROR;
	if (!SetConsoleTextAttribute(hPageOutput, GROUND_DEFAULT)) throw errnum_color;
}

bool Page::PointPaint(PageUnit requestUnit) throw() {
	int errnum_color = COLOR_ERROR;
	int errnum_coord = COORD_ERROR;
	try {
		if (!SetConsoleTextAttribute(hPageOutput, requestUnit.color)) throw errnum_color;
		if (!SetConsoleCursorPosition(hPageOutput, requestUnit.pos)) throw errnum_coord;
		if (!requestUnit.text.empty())printf("%s", requestUnit.text.c_str());
		ReturnDefault();
	}
	catch (int errnum) {
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: function PointPaint | errnum " << errnum << endl;
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_WHITE);
	}
	return true;
}

bool Page::PointPaint(COORD requestPos, WORD requestColor) throw() {
	int errnum_color = COLOR_ERROR;
	int errnum_coord = COORD_ERROR;
	try {
		if (!SetConsoleTextAttribute(hPageOutput, requestColor)) throw errnum_color;
		if (!SetConsoleCursorPosition(hPageOutput, requestPos)) throw errnum_coord;
	}
	catch (int errnum) {
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: function PointPaint | errnum " << errnum << endl;
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_WHITE);
	}
	return true;
}

bool Page::PointPaint(COORD requestPos, WORD requestColor, string requestString) throw() {
	int errnum_color = COLOR_ERROR;
	int errnum_coord = COORD_ERROR;
	try {
		if (!SetConsoleTextAttribute(hPageOutput, requestColor)) throw errnum_color;
		if (!SetConsoleCursorPosition(hPageOutput, requestPos)) throw errnum_coord;
		if (!requestString.empty())printf("%s", requestString.c_str());
		ReturnDefault();
	}
	catch (int errnum) {
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: function PointPaint | errnum " << errnum << endl;
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_WHITE);
	}
	return true;
}

bool Page::PointPaint(short i, short j, WORD requestColor) throw() {
	int errnum_color = COLOR_ERROR;
	int errnum_coord = COORD_ERROR;
	COORD requestPos = { i, j };
	try {
		if (!SetConsoleTextAttribute(hPageOutput, requestColor)) throw errnum_color;
		if (!SetConsoleCursorPosition(hPageOutput, requestPos)) throw errnum_coord;
	}
	catch (int errnum) {
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: function PointPaint | errnum " << errnum << endl;
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_WHITE);
	}
	return true;
}

bool Page::PointPaint(short i, short j, WORD requestColor, string requestString) throw() {
	int errnum_color = COLOR_ERROR;
	int errnum_coord = COORD_ERROR;
	COORD requestPos = { i, j };
	try {
		if (!SetConsoleTextAttribute(hPageOutput, requestColor)) throw errnum_color;
		if (!SetConsoleCursorPosition(hPageOutput, requestPos)) throw errnum_coord;
		if (!requestString.empty())printf("%s", requestString.c_str());
		ReturnDefault();
	}
	catch (int errnum) {
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: function PointPaint | errnum " << errnum << endl;
		SetConsoleTextAttribute(hPageOutput, FOREGROUND_WHITE);
	}
	return true;
}