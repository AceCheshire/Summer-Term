// * License: Apache 2.0
// * File: mouse_base.h
// * Author: Mai Tianle
// * Date: 2024-08-06
// * Description: Declare class Mouse.
#include <iostream>
#include <windows.h>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_MOUSE_BASE_H_
#define LMS_BASE_MOUSE_BASE_H_
// Used to check if a key on keyboard is pressed down.
// Example: 
//    if (KEY_DOWN(VK_LBUTTON)) 
//      std::cout << "Left button is pressed down!";
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
namespace library_management_sys {
// Used in Mouse::hoverAndClick(), it means how often we detect mouse input
// when we are in detecting mode (not always). Larger number means slower
// answer speed, and smaller number means screen twinkling.
constexpr DWORD kMouseDetectInterval = 10;
// Used in Mouse::hoverAndClick(), it means how many times we detect in a
// row before we get rid of detecting mode. Larger number means users may
// wait before new pages are loaded, and smaller number means unstable 
// detection (sometimes no answer even your mouse is on the right place).
constexpr int kMouseDetectGroupTimes = 30;
// Used in Mouse::hoverAndClick() as defaulted return. It means no
// std::string is detected where mouse is hovering.
//
// Pay attention that Link::symbol_str_ shall not crush with it.
constexpr char kDefaultReturn[] = "__NULL__";
// It is an experienced ratio. Recommended font size is 12 (default). Then
// every letter will be 16px high and 9.3px wide on a "classic" screen. 
constexpr double kFontRatio = 16 / 9.3;
// Row interval in the shell. 1.2 is the default value.
constexpr double kRowInterval = 1.2;
// Pixels that a "classic" screen shall have as width.
constexpr int kClassicWidth = 2560;
// Pixels that a "classic" screen shall have as height.
constexpr int kClassicHeight = 1440;
// Mouse instance records the std::string that mouse is hovering
// on. Besides, it detects whether left mouse button is pressed down.
// Example:
//    Mouse test_mouse;
class Mouse {
 public:
  // It will try to assign all its menbers initial values. Besides, this 
  // constructor will try to change the window into a "classic" screen window.
  // Pay attention that MoveWindow() cannot work while debugging because of
  // permission limit.
  Mouse();
  // Its augment is the PageUnitEx attached to the Scene.
  //
  // Returns std::string that mouse is hovering on if left mouse button is
  // pressed on and that std::string is not empty, or it will return 
  // kDefaultReturn instead.
  //
  // The client has no need to delete it.
  //
  // This method is usually called in Scene functions. Example:
  //    void Scene::test_function() {
  //      std::string test_read_str = test_mouse.hoverAndClick(pageunit_list_head_);
  //    }
  std::string hoverAndClick(PageUnitEx& source_text);

 protected:
  // Returns char according to augment, which is the position of the char.
  char readChar(COORD coord_pos);
  // Return std::string that mouse is hovering on. Its augment is for internal
  // popLastStr to match with.
  std::string readCursorChars(PageUnitEx& source_text);
  // Re - paints the std::string mouse used to hover on if mouse position has changed. 
  // Augment is the pageunit_list_head_ of a Scene.
  void popLastStr(PageUnitEx& source_text);
  // Usually STD_OUTPUT_HANDLE on windows.
  HANDLE handle_mouse_output_;
  // Usually the return of GetForegroundWindow() on windows.
  HWND hwnd_mouse_foreground_;
  POINT point_mouse_pos_;  // ©¤©´
  COORD coord_mouse_pos_;  // ©¤©Ø©¤ These two members are equivalent.
  // Usually the font info of client's shell.
  CONSOLE_FONT_INFO console_font_;
  // The std::string mouse is hovering on.
  std::string read_str_;
};
}  // namespace namespace library_management_sys
#endif  // LMS_BASE_MOUSE_BASE_H_

// TODO:
// kFontRatio, kRowInterval, kClassicWidth, kClassicHeight shall have
// external setting interfaces.
// HANDLE, HWND, CONSOLE_FONT_INFO shall be regarded as the mutable. 
//   