// * License: Apache 2.0
// * File: mouse_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-08
// * Description: Define class Mouse.
#include "inc/base/mouse_base.h"

#include<iostream>
#include<windows.h>

#include "inc/base/page_base.h"
namespace library_management_sys {
Mouse::Mouse() {
  // Get handle of application window
  handle_mouse_output_ = GetStdHandle(STD_OUTPUT_HANDLE);
  // Get HWND of application window
  hwnd_mouse_foreground_ = GetForegroundWindow();
  // Init POINT-type mouse position
  point_mouse_pos_.x = point_mouse_pos_.y = 0;
  // Init COORD-type mouse position
  coord_mouse_pos_.X = coord_mouse_pos_.Y = 0;
  // Get font info
  GetCurrentConsoleFont(handle_mouse_output_, FALSE, &console_font_);
  // Try to move window. Pay attention that it is not the only chance to move
  // window, but it also does considering the mouse input convenience as its
  // reason
  MoveWindow(hwnd_mouse_foreground_, 0, 0, kClassicWidth, kClassicHeight, TRUE);
}

std::string Mouse::hoverAndClick(PageUnitEx& source_text) {
  short x, y;  // Temp variables for coord_mouse_pos
  int counter = kMouseDetectGroupTimes;
  // Repeat for kMouseDetectGroupTimes times
  while (counter--) {
    // Task 1: Update mouse position
    GetCursorPos(&point_mouse_pos_);  // point_mouse_pos_ becomes mouse position
                                      // on screen
    ScreenToClient(hwnd_mouse_foreground_,
                   &point_mouse_pos_);  // And becomes mouse position on client
    // Do transform from POINT to COORD for mouse position
    // Explain:
    //    console_font_.dwFontSize.X = console_font_.dwFontSize.Y / kFontRatio;
    //    coord_mouse_pos_ = point_mouse_pos_.x / console_font_.dwFontSize.X.
    x = (short)(kFontRatio * point_mouse_pos_.x / console_font_.dwFontSize.Y);
    // Explain:
    //    short rowInterval = console_font_.dwFontSize.Y * kRowInterval;
    //    coord_mouse_pos.y = point_mouse_pos_.y / pointrowInterval.
    y = (short)((double)point_mouse_pos_.y /
                (console_font_.dwFontSize.Y * kRowInterval));
    coord_mouse_pos_ = {x, y};
    // Task 2: Update std::string that mouse is hovering on
    readCursorChars(source_text);
    // Task 3: Detect mouse click.
    if (KEY_DOWN(VK_LBUTTON) && !read_str_.empty()) return read_str_;
    Sleep(kMouseDetectInterval);  // Coordinate function running time
  }
  return kDefaultReturn;  // If no return in the loop, which means no valid
                          // mouse click
}

char Mouse::readChar(COORD coord_pos) {
  TCHAR cursor_hover_on_char[1];  // Used to record the target char
  DWORD dword_char;               // Used to be parameter only
  if (ReadConsoleOutputCharacterW(handle_mouse_output_, cursor_hover_on_char, 1,
                                  coord_pos, &dword_char))
    return (char)cursor_hover_on_char[0];
  else
    return ' ';  // Pay attention that it returns ' ' for default return
}

void Mouse::readCursorChars(PageUnitEx& source_text) {
  COORD floating_left_pos = coord_mouse_pos_;   // Used as cursor moving left
  COORD floating_right_pos = coord_mouse_pos_;  // Used as cursor moving right
  floating_right_pos.X++;   // Make that floating_left_pos != floating_right_pos
  std::string read_string;  // Final result (std::string)
  char read_char;           // Initial result (char)
  // Get screen buffer information.
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(handle_mouse_output_, &csbi);
  // Move cursor (floating_right_pos) to refine read_string and highlight the
  // track
  while (
      // Assignment and filter invalid character: ' ', '\t', '\n', '\0'
      ((read_char = readChar(floating_right_pos)) != ' ') &&
      (read_char != '\t') && (read_char != '\n') && (read_char != '\0') &&
      // Make sure that the cursor will not go beyond window
      (floating_right_pos.X <= csbi.srWindow.Right - csbi.srWindow.Left)) {
    char read_chars[2] = {read_char};  // Coordinate the parameter to char[]
    // Highlight the track to realize the visual effects
    SetConsoleTextAttribute(handle_mouse_output_, BACKGROUND_INTENSITY);
    SetConsoleCursorPosition(handle_mouse_output_, floating_right_pos);
    printf("%c", read_char);
    SetConsoleTextAttribute(handle_mouse_output_,
                            GROUND_DEFAULT);  // Reset color to avoid errors
    read_string.append(read_chars);           // Refine the result
    floating_right_pos.X++;                   // Move the cursor for next loop
  }
  // Move cursor (floating_left_pos) to refine read_string and highlight the
  // track
  while (
      // Assignment and filter invalid character: ' ', '\t', '\n', '\0'
      ((read_char = readChar(floating_left_pos)) != ' ') &&
      (read_char != '\t') && (read_char != '\n') && (read_char != '\0') &&
      // Make sure that the cursor will not go beyond window
      (floating_left_pos.X >= 0)) {
    char read_chars[2] = {read_char};  // Coordinate the parameter to char[]
    // Highlight the track to realize the visual effects
    SetConsoleTextAttribute(handle_mouse_output_, BACKGROUND_INTENSITY);
    SetConsoleCursorPosition(handle_mouse_output_, floating_left_pos);
    printf("%c", read_char);
    SetConsoleTextAttribute(handle_mouse_output_,
                            GROUND_DEFAULT);  // Reset color to avoid errors
    read_string.insert(0, read_chars);        // Refine the result
    floating_left_pos.X--;                    // Move the cursor for next loop
  }
  // Clean the last highlight if the std::string that mouse is hovering on
  // changes and assign the member read_str_ with the new one
  if (read_string != read_str_) {
    popLastStr(source_text);
    read_str_ = read_string;
  }
}

void Mouse::popLastStr(PageUnitEx& source_text) {
  Page tmp_page;  // Used to apply Page interface
  // Find the relevant PageUnit from Scene member (pageunit_list_head_)
  // with a PageUnitEx pointer
  PageUnitEx* tmp_pointer = NULL;
  if (!read_str_.empty())
    tmp_pointer = source_text.findByText(read_str_);  // Match PageUnitEx
  // The judge condition means tmp_pointer has its linked PageUnit
  if (tmp_pointer != NULL)
    tmp_page.pointPaint(tmp_pointer->getPageUnit());  // Re-paint
}
}  // namespace library_management_sys