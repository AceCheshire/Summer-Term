#pragma once
#include<iostream>
#include<windows.h>
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define GROUND_DEFAULT 7

struct PageUnit {
	COORD pos;
	WORD color;
	std::string text;
};

class PageUnitEx {
public:
	void Append(PageUnit&);
	PageUnitEx* FindByText(std::string);
	PageUnit& GetPageUnit() { return thisUnit; }
	PageUnitEx* GetNext() { return nextUnit; }
	void DeleteAll();
private:
	PageUnit thisUnit;
	PageUnitEx* nextUnit;
};

class Page {
public:
	Page();
	void HideCursor();
	void ReturnDefault() throw();
	bool PointPaint(PageUnit) throw();
	bool PointPaint(COORD, WORD) throw();
	bool PointPaint(COORD, WORD, std::string) throw();
	bool PointPaint(short, short, WORD) throw();
	bool PointPaint(short, short, WORD, std::string) throw();
protected:
	HANDLE hPageOutput;
};