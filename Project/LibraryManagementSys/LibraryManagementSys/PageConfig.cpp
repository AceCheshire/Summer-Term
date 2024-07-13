#include<iostream>
#include<windows.h>
#include"PageConst.h"
using namespace std;

Page::Page() {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

bool Page::PointPaint(COORD requestPos, WORD requestColor) throw(...) {
	int errnum_color = COLOR_ERROR;
	int errnum_coord = COORD_ERROR;
	try {
		if (!SetConsoleTextAttribute(handle, requestColor))
			throw errnum_color;
		if (!SetConsoleCursorPosition(handle, requestPos))
			throw errnum_coord;
	}
	catch (int errnum) {
		SetConsoleTextAttribute(handle, FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: function PointPaint errnum " << errnum << endl;
		SetConsoleTextAttribute(handle, FOREGOUND_WHITE);
	}
	return true;
}