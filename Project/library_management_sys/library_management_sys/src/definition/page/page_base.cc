// * License: Apache 2.0
// * File: page_base.cc
// * Author: Mai Tianle
// * Date: 2024-08-09
// * Description: Define class PageUnitEx, Page.
#include "inc/base/page_base.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/base/error_base.h"
namespace library_management_sys {
void PageUnitEx::append(PageUnit& pageunit_list_end) {
  // Check if it is the end of linked list
  if (next_unit_ == NULL) {
    next_unit_ = new PageUnitEx;  // New memory
    // Init the new end of the linked list
    next_unit_->this_unit_ = pageunit_list_end;
    next_unit_->next_unit_ = NULL;
  } else
    next_unit_->append(pageunit_list_end);  // Move to next node
}

PageUnitEx* PageUnitEx::findByText(const std::wstring& text) {
  // Match
  if (this_unit_.text == text) return this;
  // Not match and not the end
  else if (next_unit_ != NULL)
    return next_unit_->findByText(text);
  // Not match and is the end
  else
    return NULL;
}

void PageUnitEx::deleteAll() {
  // delete linked list with stack.
  if (next_unit_ != NULL) next_unit_->deleteAll();
  delete this;
}

Page::Page() {
  // Get handle of application window
  handle_output_ = GetStdHandle(STD_OUTPUT_HANDLE);
}

PageUnit Page::highlight(PageUnit& source_pageunit) {
  PageUnit tmp_pageunit = source_pageunit;
  if (source_pageunit.can_be_highlighted)
    tmp_pageunit.color = BACKGROUND_INTENSITY;  // Highlight text
  return tmp_pageunit;
}

void Page::hideCursor(bool is_to_hide_cursor) {
  CONSOLE_CURSOR_INFO console_cursor;
  // bVisible and is_to_hide_cursor are opposite.
  console_cursor.bVisible = !is_to_hide_cursor;
  console_cursor.dwSize = 1;
  SetConsoleCursorInfo(handle_output_, &console_cursor);
}

void Page::returnDefault() throw(...) {
  if (!SetConsoleTextAttribute(handle_output_,
                               page::GROUND_DEFAULT))  // Set default color
    throw kColor;
}

bool Page::pointPaint(PageUnit& request_unit) throw(...) {
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_output_, request_unit.color))
      throw kColor;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_output_, request_unit.pos))
      throw kCoord;
    // print std::wstring
    if (request_unit.text.length()) {
      std::wcout << request_unit.text.c_str();
      std::wcout.imbue(std::locale("chs"));
    }
    returnDefault();  // Set default color
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_output_, FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color) throw(...) {
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_output_, request_color))
      throw kColor;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_output_, request_pos))
      throw kCoord;
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_output_, FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color,
                      const std::wstring& request_string) throw(...) {
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_output_, request_color))
      throw kColor;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_output_, request_pos))
      throw kCoord;
    // print std::wstring
    if (request_string.length()) {
      std::wcout << request_string.c_str();
      std::wcout.imbue(std::locale("chs"));
    }
    returnDefault();  // Set default color
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_output_, FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(short x, short y, WORD request_color) throw(...) {
  COORD request_pos = {x, y};
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_output_, request_color))
      throw kColor;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_output_, request_pos))
      throw kCoord;
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_output_, FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(short x, short y, WORD request_color,
                      const std::wstring& request_string) throw(...) {
  COORD request_pos = {x, y};
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_output_, request_color))
      throw kColor;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_output_, request_pos))
      throw kCoord;
    // print std::wstring
    if (request_string.length()) {
      std::wcout.imbue(std::locale("chs"));
      std::wcout << request_string.c_str();
    }
    returnDefault();  // Set default color
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_output_, FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}
}  // namespace library_management_sys