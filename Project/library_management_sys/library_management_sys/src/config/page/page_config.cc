#include"error_base.h"
#include"page_base.h"
#include<iostream>
#include<windows.h>
using namespace std;

void PageUnitEx::append(PageUnit& pageunit_list_end) {
  if (next_unit_ == NULL) {
    next_unit_ = new PageUnitEx;
    next_unit_->this_unit_ = pageunit_list_end;
    next_unit_->next_unit_ = NULL;
  } else
    next_unit_->append(pageunit_list_end);
}

PageUnitEx* PageUnitEx::findByText(std::string text) {
  if (this_unit_.text == text)
    return this;
  else if (next_unit_ != NULL)
    return next_unit_->findByText(text);
  else
    return NULL;
}

void PageUnitEx::deleteAll() {
  if (next_unit_ != NULL) next_unit_->deleteAll();
  delete this;
}

Page::Page() { handle_page_output_ = GetStdHandle(STD_OUTPUT_HANDLE); }

void Page::hideCursor(bool is_to_hide_cursor) {
  CONSOLE_CURSOR_INFO console_cursor;
  console_cursor.bVisible = !is_to_hide_cursor;
  console_cursor.dwSize = 1;
  SetConsoleCursorInfo(handle_page_output_, &console_cursor);
}

void Page::returnDefault() {
  if (!SetConsoleTextAttribute(handle_page_output_, GROUND_DEFAULT))
    throw kColorError;
}

bool Page::pointPaint(PageUnit request_unit) throw() {
  try {
    if (!SetConsoleTextAttribute(handle_page_output_, request_unit.color))
      throw kColorError;
    if (!SetConsoleCursorPosition(handle_page_output_, request_unit.pos))
      throw kCoordError;
    if (!request_unit.text.empty()) printf("%s", request_unit.text.c_str());
    returnDefault();
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: function pointPaint | err_num " << err_num << endl;
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_WHITE);
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color) throw() {
  try {
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: function pointPaint | err_num " << err_num << endl;
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_WHITE);
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color,
                      string request_string) throw() {
  try {
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
    if (!request_string.empty()) printf("%s", request_string.c_str());
    returnDefault();
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: function pointPaint | err_num " << err_num << endl;
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_WHITE);
  }
  return true;
}

bool Page::pointPaint(short i, short j, WORD request_color) throw() {
  COORD request_pos = {i, j};
  try {
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: function pointPaint | err_num " << err_num << endl;
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_WHITE);
  }
  return true;
}

bool Page::pointPaint(short i, short j, WORD request_color,
                      string request_string) throw() {
  COORD request_pos = {i, j};
  try {
    if (!SetConsoleTextAttribute(handle_page_output_, request_color))
      throw kColorError;
    if (!SetConsoleCursorPosition(handle_page_output_, request_pos))
      throw kCoordError;
    if (!request_string.empty()) printf("%s", request_string.c_str());
    returnDefault();
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: function pointPaint | err_num " << err_num << endl;
    SetConsoleTextAttribute(handle_page_output_, FOREGROUND_WHITE);
  }
  return true;
}