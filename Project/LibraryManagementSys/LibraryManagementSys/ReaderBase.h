#pragma once
#include"PageBase.h"
#include<fstream>
#include<iostream>
#define X_BASE 0
#define Y_BASE 4
#define COLOR_BASE 8
#define STR_BASE 13

class Reader {
public:
	bool ReadForPointPaint(PageUnitEx*, std::string);
};