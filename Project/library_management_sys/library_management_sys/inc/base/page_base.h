// * License: Apache 2.0
// * File: page_base.h
// * Author: Mai Tianle
// * Date: 2024-08-06
// * Description: Declare struct PageUnit, class PageUnitEx and class Page.
#include <iostream>
#include <windows.h>
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

// Provides extra functions to manage PageUnit group as linked list.
// Example:
//    PageUnitEx test_pageunit_ex; PageUnit test_unit_1, test_unit_2.
//    test_pageunit_ex.append(test_unit_1);
//    test_pageunit_ex.append(test_unit_2);
//    test_pageunit_ex.deleteAll();
class PageUnitEx {
 public:
  // Usually the PageUnitEx used to call append() has not been assigned.
  // Client shall delete it by deleteAll().
  // Example:
  //    PageUnitEx test_pageunit_ex;
  //    test_pageunit_ex.append(new PageUnit);
  void append(PageUnit& pageunit_list_end);
  // Returns NULL if the PageUnitEx head and the followings do not match.
  // Returns the first PageUnitEx* if one instance matches the text.
  // Example:
  //    PageUnitEx* test_ex_pointer = test_pageunit_ex.findByText("Bingo");
  //    PageUnit test_unit_result = test_ex_pointer->getPageUnit();
  PageUnitEx* findByText(std::string text);
  PageUnit& getPageUnit() { return this_unit_; }
  PageUnitEx* getNext() { return next_unit_; }
  // Deletes this PageUnitEx instance and the followings.
  void deleteAll();

 private:
  PageUnit this_unit_;
  PageUnitEx* next_unit_ = NULL;
};

// Collects some common functions used to change page text.
class Page {
 public:
  // Assigns the member handle_page_output_ with STD_OUTPUT_HANDLE.
  Page();
  // Argument true for hiding cursor of the shell page.
  void hideCursor(bool is_to_hide_cursor);
  // Throws BasicError(kColorError) if fails to turn to GROUND_DEFAULT.
  void returnDefault() throw();
  // Returns true if text has been correctly set, after turns to GROUND_DEFAULT.
  bool pointPaint(PageUnit& request_unit) throw();
  // Departed version of pointPaint(PageUnit& request_unit) without text.
  bool pointPaint(COORD request_pos, WORD request_color) throw();
  // Departed version of pointPaint(PageUnit& request_unit) with text.
  bool pointPaint(COORD request_pos, WORD request_color,
                  std::string request_text) throw();
  // Departed version of pointPaint(COORD request_pos, WORD request_color).
  bool pointPaint(short x, short y, WORD request_color) throw();
  // Departed version of pointPaint
  // (COORD request_pos, WORD request_color, std::string request_text).
  bool pointPaint(short x, short y, WORD request_color,
                  std::string request_text) throw();

 protected:
  // Usually STD_OUTPUT_HANDLE on windows.
  HANDLE handle_page_output_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_PAGE_BASE_H_