#pragma once
#define screenWidth 80
#define sceenHeight 40
#define COLOR_ERROR 1
#define COORD_ERROR 2
#define FOREGOUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

class Page {
public:
	Page();
	bool PointPaint(COORD, WORD) throw(...);
private:
	HANDLE handle;
};