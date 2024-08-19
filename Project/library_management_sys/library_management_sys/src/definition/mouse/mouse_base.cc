// * License: Apache 2.0
// * File: mouse_base.cc
// * Author: Mai Tianle
// * Date: 2024-08-08
// * Description: Define class Mouse.
#include "inc/base/mouse_base.h"

#include <windows.h>

#include <string>

#include "inc/base/page_base.h"
namespace library_management_sys {
Mouse::Mouse() {
  // Get handle of application window
  handle_output_ = GetStdHandle(STD_OUTPUT_HANDLE);
  // Get HWND of application window
  hwnd_foreground_ = GetForegroundWindow();
  // Init POINT-type mouse position
  point_pos_.x = point_pos_.y = 0;
  // Init COORD-type mouse position
  coord_pos_.X = coord_pos_.Y = 0;
  // Get font info
  GetCurrentConsoleFont(handle_output_, FALSE, &console_font_);
  // Try to move window. Pay attention that it is not the only chance to move
  // window, but it also does considering the mouse input convenience as its
  // reason
  MoveWindow(hwnd_foreground_, 0, 0, mouse::kClassicWidth,
             mouse::kClassicHeight, TRUE);
}

std::wstring Mouse::hoverAndClick(PageUnitEx& source_text) {
  short x, y;  // Temp variables for coord_pos
  int counter = mouse::kDetectGroupTimes;
  // Repeat for mouse::kDetectGroupTimes times
  while (counter--) {
    Sleep(mouse::kDetectInterval);  // Coordinate function running time
    // Task 1: Update mouse position
    GetCursorPos(&point_pos_);  // point_pos_ becomes mouse position on screen
    ScreenToClient(hwnd_foreground_,
                   &point_pos_);  // And becomes mouse position on client
    // Do transform from POINT to COORD for mouse position
    // Explain:
    //    console_font_.dwFontSize.X = console_font_.dwFontSize.Y / kFontRatio;
    //    coord_mouse_pos_ = point_mouse_pos_.x / console_font_.dwFontSize.X.
    x = (short)(mouse::kFontRatio * point_pos_.x /
                console_font_.dwFontSize.Y);
    // Explain:
    //    short rowInterval = console_font_.dwFontSize.Y * kRowInterval;
    //    coord_mouse_pos.y = point_mouse_pos_.y / rowInterval.
    y = (short)((double)point_pos_.y /
                (console_font_.dwFontSize.Y * mouse::kRowInterval));
    coord_pos_ = {x, y};
    // Task 2: Update std::wstring that mouse is hovering on
    readCursorChars(source_text);
    // Task 3: Detect mouse click.
    if (kKeyDown(VK_LBUTTON) && read_str_.length()) return read_str_;
  }
  return mouse::kDefaultReturn;  // If no return in the loop, which means no
                                 // valid mouse click
}

char Mouse::readChar(COORD coord_pos) {
  TCHAR cursor_hover_on_char[1];  // Used to record the target char
  DWORD dword_char;               // Used to be parameter only
  if (ReadConsoleOutputCharacterW(handle_output_, cursor_hover_on_char, 1,
                                  coord_pos, &dword_char))
    return (char)cursor_hover_on_char[0];
  else
    return ' ';  // Pay attention that it returns ' ' for default return
}

void Mouse::readCursorChars(PageUnitEx& source_text) {
  COORD floating_left_pos = coord_pos_;   // Used as cursor moving left
  COORD floating_right_pos = coord_pos_;  // Used as cursor moving right
  floating_right_pos.X++;   // Make that floating_left_pos != floating_right_pos
  std::wstring read_string;  // Final result (std::wstring)
  wchar_t read_char;           // Initial result (char)
  // Get screen buffer information.
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(handle_output_, &csbi);
  // Move cursor (floating_right_pos) to refine read_string
  while (
      // Assignment and filter invalid character: ' ', '\t', '\n', '\0'
      ((read_char = readChar(floating_right_pos)) != L' ') &&
      (read_char != L'\t') && (read_char != L'\n') && (read_char != L'\0') &&
      // Make sure that the cursor will not go beyond window
      (floating_right_pos.X <= csbi.srWindow.Right - csbi.srWindow.Left)) {
    wchar_t read_chars[2] = {read_char};  // Coordinate the parameter to char[]
    read_string.append(read_chars);    // Refine the result
    // Move the cursor for next loop
    floating_right_pos.X++;
    SetConsoleCursorPosition(handle_output_, floating_right_pos);
  }
  // Move cursor (floating_left_pos) to refine read_string
  while (
      // Assignment and filter invalid character: ' ', '\t', '\n', '\0'
      ((read_char = readChar(floating_left_pos)) != L' ') &&
      (read_char != L'\t') && (read_char != L'\n') && (read_char != L'\0') &&
      // Make sure that the cursor will not go beyond window
      (floating_left_pos.X >= 0)) {
    wchar_t read_chars[2] = {read_char};   // Coordinate the parameter to char[]
    read_string.insert(0, read_chars);  // Refine the result
    // Move the cursor for next loop
    floating_left_pos.X--;
    SetConsoleCursorPosition(handle_output_, floating_left_pos);
  }
  // Update the last highlight if the std::wstring that mouse is hovering on
  // changes and assign the member read_str_ with the new one
  if (read_string != read_str_) {
    popLastStr(source_text, read_string);
    read_str_ = read_string;
  }
}

void Mouse::popLastStr(PageUnitEx& source_text, std::wstring& new_string) {
  Page tmp_page;  // Used to apply Page interface
  // Find the relevant PageUnits from Scene member (pageunit_list_head_)
  // with a PageUnitEx pointer
  PageUnitEx* tmp_pointer = NULL;
  if (read_str_.length())
    tmp_pointer = source_text.findByText(read_str_);  // Match PageUnitEx
  // The judge condition means tmp_pointer has its linked PageUnit
  if (tmp_pointer != NULL)
    tmp_page.pointPaint(tmp_pointer->getPageUnit());  // Re-paint
  tmp_pointer = NULL;  // Reset for the next task
  if (new_string.length())
    tmp_pointer = source_text.findByText(new_string);  // Match PageUnitEx
  // The judge condition means tmp_pointer has its linked PageUnit
  if (tmp_pointer != NULL) {
    PageUnit tmp_unit = tmp_page.highlight(tmp_pointer->getPageUnit());
    tmp_page.pointPaint(tmp_unit);  // Re-paint
  }
}
}  // namespace library_management_sys