#pragma once
#include"page_base.h"
#include<fstream>
#include<iostream>
namespace library_management_sys {
constexpr int kXBase = 0;
constexpr int kYBase = 4;
constexpr int kColorBase = 8;
constexpr int kStrBase = 13;

class Reader {
 public:
  bool readForPointPaint(PageUnitEx*, std::string);
};
}  // namespace library_management_sys