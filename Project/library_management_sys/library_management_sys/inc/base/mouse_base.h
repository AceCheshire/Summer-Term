// * License: Apache 2.0
// * File: mouse_base.h
// * Author: Mai Tianle
// * Date: 2024-08-06
// * Description: Declare class Mouse.
#include <windows.h>

#include <string>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_MOUSE_BASE_H_
#define LMS_BASE_MOUSE_BASE_H_
// Used to check if a key on keyboard is pressed down.
// Example: 
//    if (kKeyDown(VK_LBUTTON)) {
//      std::wcout.imbue(std::locale("chs"));
//      std::wcout << "Left button is pressed down!";
//    }
#define kKeyDown(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
namespace library_management_sys {
namespace mouse {
// Used in Mouse::hoverAndClick(), it means how often we detect mouse input
// when we are in detecting mode (not always). Larger number means slower
// answer speed, and smaller number means screen twinkling.
constexpr DWORD kDetectInterval = 250;

// Used in Mouse::hoverAndClick(), it means how many times we detect in a
// row before we get rid of detecting mode. Larger number means users may
// wait before new pages are loaded, and smaller number means unstable
// detection (sometimes no answer even your mouse is on the right place).
constexpr int kDetectGroupTimes = 1;

// Used in Mouse::hoverAndClick() as defaulted return. It means no
// std::wstring is detected where mouse is hovering.
//
// Pay attention that Link::symbol_str_ shall not crush with it.
constexpr wchar_t kDefaultReturn[] = L"__NULL__";

// It is an experienced ratio. Recommended font size is 12 (default). Then
// every letter will be 16px high and 9.3px wide on a "classic" screen.
constexpr double kFontRatio = 16 / 9.3;

// Row interval in the shell. 1.2 is the default value.
constexpr double kRowInterval = 1.2;

// Pixels that a "classic" screen shall have as width.
constexpr int kClassicWidth = 2560;

// Pixels that a "classic" screen shall have as height.
constexpr int kClassicHeight = 1440;
}  // namespace mouse

// Mouse instance records the std::wstring that mouse is hovering
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

  // Its argument is the PageUnitEx attached to the Scene.
  //
  // Returns std::wstring that mouse is hovering on if left mouse button is
  // pressed on and that std::wstring is not empty, or it will return
  // kDefaultReturn instead.
  //
  // The client has no need to delete it.
  //
  // This method is usually called in Scene functions. Example:
  //    void Scene::test_function() {
  //      std::wstring test_read_str =
  //      test_mouse.hoverAndClick(pageunit_list_head_);
  //    }
  std::wstring hoverAndClick(PageUnitEx& source_text);

 protected:
  // Returns char according to argument, which is the position of the char.
  char readChar(COORD coord_pos);

  // Assigns read_str_ with std::wstring that mouse is hovering on. Its argument
  // is for internal popLastStr() to match with.
  void readCursorChars(PageUnitEx& source_text);

  // Re-paints the std::wstring mouse hovers on if mouse position has
  // changed. Arguments include the pageunit_list_head_ of a Scene and the
  // currently hovering std::wstring.
  void popLastStr(PageUnitEx& source_text, std::wstring& new_string);

  // Usually STD_OUTPUT_HANDLE on windows.
  HANDLE handle_output_;

  // Usually the return of GetForegroundWindow() on windows.
  HWND hwnd_foreground_;

  POINT point_pos_;

  // Equivalent to point_pos_.
  COORD coord_pos_;

  // Usually the font info of client's shell.
  CONSOLE_FONT_INFO console_font_;

  // The std::wstring mouse is hovering on.
  std::wstring read_str_ = {};
};
}  // namespace library_management_sys
#endif  // LMS_BASE_MOUSE_BASE_H_

// TODO:
// kFontRatio, kRowInterval, kClassicWidth, kClassicHeight shall have
// external setting interfaces.
// HANDLE, HWND, CONSOLE_FONT_INFO shall be regarded as the mutable. 
// 