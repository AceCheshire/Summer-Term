#pragma once
#include"page_base.h"
#include<iostream>
#include<windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
constexpr DWORD kMouseDetectInterval = 10;
constexpr int kMouseDetectGroupTimes = 30;
constexpr char kDefaultReturn[7] = "_NULL_";
constexpr double kFontRatio = 16 / 9.3;
constexpr double kRowInterval = 1.2;
constexpr int kClassicWidth = 2560;
constexpr int kClassicHeight = 1440;

class Mouse {
 public:
  Mouse();
  std::string hoverAndClick(PageUnitEx*);

 protected:
  char readChar(COORD);
  std::string readCursorChars(PageUnitEx*);
  void popLastStr(PageUnitEx*);
  HANDLE handle_mouse_output_;
  HWND hwnd_mouse_foreground_;
  POINT point_mouse_pos_;
  COORD coord_mouse_pos_;
  CONSOLE_FONT_INFO console_font_;
  std::string read_str_;
};