#pragma once
#include<fstream>
#include<iostream>
#include"PageConst.h"
#define HOME_PAGE_DATA "HomePageData.txt"

class Reader {
public:
	bool ReadForPointPaint(PageUnitEx*, std::string);
};
