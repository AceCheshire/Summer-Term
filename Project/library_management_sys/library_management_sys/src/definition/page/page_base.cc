// * 文件：page_base.cc
// * 作者：麦天乐
// * 介绍：定义 PageUnitEx 类和 Page 类。
#include "inc/base/page_base.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/app_const.h"
namespace library_management_sys {
void PageUnitEx::append(PageUnit& pageunit_list_end) {
  if (next_unit_ == NULL) {       // 检测是否为链表尾部
    next_unit_ = new PageUnitEx;  // 新建拓展页面单元
    next_unit_->pos_ = pageunit_list_end.pos_;
    next_unit_->color_ = pageunit_list_end.color_;
    next_unit_->can_be_highlighted_ = pageunit_list_end.can_be_highlighted_;
    next_unit_->text_ = pageunit_list_end.text_;
    next_unit_->next_unit_ = NULL;
  } else
    next_unit_->append(pageunit_list_end);  // 向后移动
}

PageUnit* PageUnitEx::findByText(const std::wstring& text) {
  if (text_ == text) {  // 匹配
    return this;
  } else if (next_unit_ != NULL) {  // 不匹配但不是尾部
    return next_unit_->findByText(text);
  } else {  // 不匹配且为尾部
    return NULL;
  }
}

PageUnit& PageUnitEx::operator[](const std::wstring& index) {
  if (text_ == index) {  // 匹配
    return *this;
  } else if (next_unit_ != NULL) {  // 不匹配但不是尾部
    return *next_unit_->findByText(index);
  } else {  // 不匹配且为尾部
    return *this;
  }
}

void PageUnitEx::deleteAll() {
  PageUnitEx* temp_next = next_unit_;
  while (temp_next != NULL) {  // 循环删除
    PageUnitEx* temp_this = temp_next;
    temp_next = temp_next->next_unit_;
    delete temp_this;
  }
}

PageUnit Page::highlight(PageUnit& source_pageunit) {
  PageUnit tmp_pageunit = source_pageunit;
  if (source_pageunit.can_be_highlighted_)
    tmp_pageunit.color_ = BACKGROUND_INTENSITY;
  return tmp_pageunit;
}

void Page::hideCursor(bool is_to_hide_cursor) {
  CONSOLE_CURSOR_INFO console_cursor;
  console_cursor.bVisible = !is_to_hide_cursor;
  console_cursor.dwSize = 1;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_cursor);
}

bool Page::returnDefault() {
  return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                 page::GROUND_DEFAULT);
}

bool Page::pointPaint(PageUnit& request_unit) {
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_unit.color_)) {  // 设置颜色
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_unit.pos_)) {  // 设置坐标
    return false;
  }
  if (request_unit.text_.length()) std::wcout << request_unit.text_;
  return returnDefault();
}

bool Page::pointPaint(COORD request_pos, WORD request_color) {
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // 设置颜色
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // 设置坐标
    return false;
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color,
                      const std::wstring& request_string) {
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // 设置颜色
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // 设置坐标
    return false;
  }
  if (request_string.length()) std::wcout << request_string;
  return returnDefault();
}

bool Page::pointPaint(short x, short y, WORD request_color) {
  COORD request_pos = {x, y};
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // 设置颜色
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // 设置坐标
    return false;
  }
  return true;
}

bool Page::pointPaint(short x, short y, WORD request_color,
                      const std::wstring& request_string) {
  COORD request_pos = {x, y};
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // 设置颜色
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // 设置坐标
    return false;
  }
  if (request_string.length()) std::wcout << request_string;
  return returnDefault();
}
}  // namespace library_management_sys