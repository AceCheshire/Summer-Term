#pragma once
#include"page_base.h"
#include<fstream>
#include<iostream>
constexpr int kXBase = 0;
constexpr int kYBase = 4;
constexpr int kColorBase = 8;
constexpr int kStrBase = 13;

class Reader {
public:
	bool readForPointPaint(PageUnitEx*, std::string);
};