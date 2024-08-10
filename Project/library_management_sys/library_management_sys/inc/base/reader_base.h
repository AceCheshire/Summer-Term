// * License: Apache 2.0
// * File: reader_base.h
// * Author: Mai Tianle
// * Date: 2024-08-07
// * Description: Declare class Reader.
#include <iostream>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_READER_BASE_H_
#define LMS_BASE_READER_BASE_H_
namespace library_management_sys {
// Used in Reader::readForPointPaint(). It means the serial of
// the x value of the PageUnit.pos in each line.
constexpr int kXBase = 0;
// Used in Reader::readForPointPaint(). It means the serial of
// the y value of the PageUnit.pos in each line.
constexpr int kYBase = 4;
// Used in Reader::readForPointPaint(). It means the serial of
// the PageUnit.color in each line.
constexpr int kColorBase = 8;
// Used in Reader::readForPointPaint(). It means the serial of
// the PageUnit.text in each line.
constexpr int kStrBase = 13;

// Reads data files and makes relevant assignments.
class Reader {
 public:
  // Returns false if file cannot be normally opened.
  // When reading finishes, the pageunit_list_head is not changed.
  // Example:
  //    if (test_reader.readForPointPaint(test_pageunit_ex,"test.txt")) {
  //      PageUnit* test_pageunit_pointer;
  //      while ((test_pageunit_pointer = test_pageunit_ex.getNext()) != NULL)
  //        test_page.pointPaint(test_pageunit_pointer->getPageUnit());
  //    }
  bool readForPointPaint(PageUnitEx& pageunit_list_head, std::string file_name);
};
}  // namespace library_management_sys
#endif  // LMS_BASE_READER_BASE_H_