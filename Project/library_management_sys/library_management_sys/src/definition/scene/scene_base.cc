// * License: Apache 2.0
// * File: scene_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define class Scene.
#include "inc/base/scene_base.h"

#include <conio.h>

#include <iostream>
#include <string>
#include <tuple>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
namespace library_management_sys {
Scene::Scene(PageUnitEx& pageunit_list_head)
    : pageunit_list_head_(&pageunit_list_head) {}

void Scene::layoutText() throw(...) {
  Page tmp_page;  // Create temp Page to use Page interface.
  PageUnitEx* tmp_pageunit_pointer = pageunit_list_head_;  // Used as iterator
  // Equivalent to pageunit_list_head_ == NULL
  if (tmp_pageunit_pointer == NULL) throw kNullPointer;
  while (tmp_pageunit_pointer != NULL) {
    tmp_page.pointPaint(tmp_pageunit_pointer->getPageUnit());  // Get and paint
    tmp_pageunit_pointer = tmp_pageunit_pointer->getNext();    // Iterate
  }
}

std::wstring Scene::inputLine(bool space) {
  std::wstring tmp_string;  // Result to be maintained
  wchar_t tmp_char;         // Return of _getch()
  while ((tmp_char = _getwch()) != L'\r') {
    // 224 and 0 mean special function keys. 0 and 224 are their first return.
    if (tmp_char == 224 || tmp_char == 0) std::ignore = _getwch();
    // Append the string something new
    if (((L'A' <= tmp_char && tmp_char <= L'Z') ||
         (L'a' <= tmp_char && tmp_char <= L'z') ||
         (space && tmp_char == L' ') ||
         (L'0' <= tmp_char && tmp_char <= L'9') || tmp_char == L'_') &&
        tmp_string.length() <= scene::adviceLength) {
      std::wcout.imbue(std::locale("chs"));
      std::wcout << tmp_char;
      tmp_string.push_back(tmp_char);
      // Belows are deleting the end of string
    } else if (tmp_char == L'\b' && tmp_string.length()) {
      std::wcout.imbue(std::locale("chs"));
      std::wcout << L"\b \b";
      tmp_string.pop_back();
    }
  }
  return tmp_string;
}

std::wstring Scene::inputLine(bool space, const char& fill_char) {
  std::wstring tmp_string;
  wchar_t tmp_char;
  while ((tmp_char = _getwch()) != L'\r') {
    if (((L'A' <= tmp_char && tmp_char <= 'Z') ||
         (L'a' <= tmp_char && tmp_char <= L'z') ||
         (space && tmp_char == L' ') ||
         (L'0' <= tmp_char && tmp_char <= L'9') || tmp_char == L'_') &&
        tmp_string.length() <= scene::adviceLength) {
      std::wcout.imbue(std::locale("chs"));
      std::wcout << fill_char;  // Difference
      tmp_string.push_back(tmp_char);
    } else if (tmp_char == L'\b' && tmp_string.length()) {
      std::wcout.imbue(std::locale("chs"));
      std::wcout << L"\b \b";
      tmp_string.pop_back();
    }
  }
  return tmp_string;
}
}  // namespace library_management_sys