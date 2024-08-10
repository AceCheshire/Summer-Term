// * License: Apache 2.0
// * File: page_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-09
// * Description: Define class PageUnitEx, Page.
#include "inc/base/page_base.h"

#include <iostream>
#include <windows.h>

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

PageUnitEx* PageUnitEx::findByText(std::string text) {
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
  handle_page_output_ = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Page::hideCursor(bool is_to_hide_cursor) {
  CONSOLE_CURSOR_INFO console_cursor;
  // bVisible and is_to_hide_cursor are opposite.
  console_cursor.bVisible = !is_to_hide_cursor;
  console_cursor.dwSize = 1;
  SetConsoleCursorInfo(handle_page_output_, &console_cursor);
}

void Page::returnDefault() throw() {
  if (!SetConsoleTextAttribute(handle_page_output_,
                               GROUND_DEFAULT))  // Set default color
    throw kColorError;
}

bool Page::pointPaint(PageUnit& request_unit) throw() {
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_page_output_, request_unit.color))
      throw kColorError;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_page_output_, request_unit.pos))
      throw kCoordError;
    // print std::string
    if (!request_unit.text.empty()) printf("%s", request_unit.text.c_str());
    returnDefault();  // Set default color
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    std::cout << std::endl;
    std::cerr << "ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_page_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color) throw() {
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    std::cout << std::endl;
    std::cerr << "ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_page_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color,
                      std::string request_string) throw() {
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
    // print std::string
    if (!request_string.empty()) printf("%s", request_string.c_str());
    returnDefault();  // Set default color
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    std::cout << std::endl;
    std::cerr << "ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_page_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(short x, short y, WORD request_color) throw() {
  COORD request_pos = {x, y};
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    std::cout << std::endl;
    std::cerr << "ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_page_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}

bool Page::pointPaint(short x, short y, WORD request_color,
                      std::string request_string) throw() {
  COORD request_pos = {x, y};
  try {
    // Set text color
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    // Set cursor position
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
    // print std::string
    if (!request_string.empty()) printf("%s", request_string.c_str());
    returnDefault();  // Set default color
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    std::cout << std::endl;
    std::cerr << "ERR: function pointPaint | err_num " << err_num << std::endl;
    SetConsoleTextAttribute(handle_page_output_,
                            FOREGROUND_WHITE);  // Set default color
  }
  return true;
}
}  // namespace library_management_sys