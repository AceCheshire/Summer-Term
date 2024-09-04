// * �ļ���page_base.cc
// * ���ߣ�������
// * ���ܣ����� PageUnitEx ��� Page �ࡣ
#include "inc/base/page_base.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/app_const.h"
namespace library_management_sys {
void PageUnitEx::append(PageUnit& pageunit_list_end) {
  if (next_unit_ == NULL) {       // ����Ƿ�Ϊ����β��
    next_unit_ = new PageUnitEx;  // �½���չҳ�浥Ԫ
    next_unit_->pos_ = pageunit_list_end.pos_;
    next_unit_->color_ = pageunit_list_end.color_;
    next_unit_->can_be_highlighted_ = pageunit_list_end.can_be_highlighted_;
    next_unit_->text_ = pageunit_list_end.text_;
    next_unit_->next_unit_ = NULL;
  } else
    next_unit_->append(pageunit_list_end);  // ����ƶ�
}

PageUnit* PageUnitEx::findByText(const std::wstring& text) {
  if (text_ == text) {  // ƥ��
    return this;
  } else if (next_unit_ != NULL) {  // ��ƥ�䵫����β��
    return next_unit_->findByText(text);
  } else {  // ��ƥ����Ϊβ��
    return NULL;
  }
}

PageUnit& PageUnitEx::operator[](const std::wstring& index) {
  if (text_ == index) {  // ƥ��
    return *this;
  } else if (next_unit_ != NULL) {  // ��ƥ�䵫����β��
    return *next_unit_->findByText(index);
  } else {  // ��ƥ����Ϊβ��
    return *this;
  }
}

void PageUnitEx::deleteAll() {
  PageUnitEx* temp_next = next_unit_;
  while (temp_next != NULL) {  // ѭ��ɾ��
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
                               request_unit.color_)) {  // ������ɫ
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_unit.pos_)) {  // ��������
    return false;
  }
  if (request_unit.text_.length()) std::wcout << request_unit.text_;
  return returnDefault();
}

bool Page::pointPaint(COORD request_pos, WORD request_color) {
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // ������ɫ
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // ��������
    return false;
  }
  return true;
}

bool Page::pointPaint(COORD request_pos, WORD request_color,
                      const std::wstring& request_string) {
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // ������ɫ
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // ��������
    return false;
  }
  if (request_string.length()) std::wcout << request_string;
  return returnDefault();
}

bool Page::pointPaint(short x, short y, WORD request_color) {
  COORD request_pos = {x, y};
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // ������ɫ
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // ��������
    return false;
  }
  return true;
}

bool Page::pointPaint(short x, short y, WORD request_color,
                      const std::wstring& request_string) {
  COORD request_pos = {x, y};
  if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                               request_color)) {  // ������ɫ
    return false;
  }
  if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                request_pos)) {  // ��������
    return false;
  }
  if (request_string.length()) std::wcout << request_string;
  return returnDefault();
}
}  // namespace library_management_sys