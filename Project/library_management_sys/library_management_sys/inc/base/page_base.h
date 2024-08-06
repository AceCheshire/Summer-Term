// * License: Apache 2.0
// * File: mouse_base.h
// * Author: Mai Tianle
// * Date: 2024-08-06
// * Description: Define struct PageUnit, class PageUnitEx and class Page.
#include<iostream>
#include<windows.h>
#ifndef LMS_BASE_PAGE_BASE_H_
#define LMS_BASE_PAGE_BASE_H_
// In fact, color white is the combination of red, green and blue.
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
// It is equivalent to FOREGROUND_WHITE.
#define FOREGROUND_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
namespace library_management_sys {
// It is equivalent to FOREGROUND_WHITE (7U) and "BACKGROUND_BLACK" (0).
constexpr WORD GROUND_DEFAULT = 7U;
// Records text attributes for each group of letters.
// Example:
//    PageUnit test_unit;
//    test_unit.pos = {0, 0};
//    test_unit.color = GROUND_DEFAULT;
//    test_unit.text = "test_content";
struct PageUnit {
  // x range: [0, min {kClassicWidth - 1, client_screen_width}];
  // y range: [0, min {kClassicHeight - 1, client_screen_height}].
  COORD pos;
  WORD color;
  std::string text;
};

//
class PageUnitEx {
 public:
  void append(PageUnit&);
  PageUnitEx* findByText(std::string);
  PageUnit& getPageUnit() { return this_unit_; }
  PageUnitEx* getNext() { return next_unit_; }
  void deleteAll();

 private:
  PageUnit this_unit_;
  PageUnitEx* next_unit_;
};

class Page {
 public:
  Page();
  void hideCursor(bool);
  void returnDefault() throw();
  bool pointPaint(PageUnit) throw();
  bool pointPaint(COORD, WORD) throw();
  bool pointPaint(COORD, WORD, std::string) throw();
  bool pointPaint(short, short, WORD) throw();
  bool pointPaint(short, short, WORD, std::string) throw();

 protected:
  HANDLE handle_page_output_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_PAGE_BASE_H_