// * License: Apache 2.0
// * File: reader_base.h
// * Author: Mai Tianle
// * Date: 2024-08-07
// * Description: Declare class Reader.
#include <string>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_READER_BASE_H_
#define LMS_BASE_READER_BASE_H_
// Path that records user's password.
#define kUserPasswordPath(USER_NAME) L"res/user/" + USER_NAME + L"/password.dat"
namespace library_management_sys {
namespace reader {
// Used in Reader::readForPointPaint(). It means the serial of
// the x value of the PageUnit::pos in each line.
constexpr int kXBase = 0;

// Used in Reader::readForPointPaint(). It means the serial of
// the y value of the PageUnit::pos in each line.
constexpr int kYBase = 4;

// Used in Reader::readForPointPaint(). It means the serial of
// the PageUnit::color in each line.
constexpr int kColorBase = 8;

// Used in Reader::readForPointPaint(). It means the serial of
// the PageUnit::color in each line.
constexpr int kHighlightBase = 13;

// Used in Reader::readForPointPaint(). It means the serial of
// the PageUnit::text in each line.
constexpr int kStrBase = 15;
}  // namespace reader

// Reads data files and makes relevant assignments.
class Reader {
 public:
  // Returns false if file cannot be normally opened.
  // When reading finishes, the pageunit_list_head is not changed.
  // Example:
  //    if (test_reader.readForPointPaint(test_pageunit_ex, L"test.txt")) {
  //      PageUnit* test_pageunit_pointer;
  //      while ((test_pageunit_pointer = test_pageunit_ex.getNext()) != NULL)
  //        test_page.pointPaint(test_pageunit_pointer->getPageUnit());
  //    }
  bool readForPointPaint(PageUnitEx& pageunit_list_head,
                         const std::wstring& file_name);

  // Returns true if inputted name and password is checkable in resource files.
  // Example:
  //    std::cin >> test_name;
  //    std::cin >> test_password;
  //    if (test_reader.readForLogin(test_name, test_password)) {
  //      std::wcout.imbue(std::locale("chs"));
  //      std::wcout << "Password is correct!" << std::endl;
  //    }
  // It is equivalent to:
  //    std::wstring password_path = L"res/user/" + name + L"/password.txt";
  //    test_reader.readFileLine(password_path, 1, correct_password);
  //    if (correct_password == password) return true;
  // We prefer readForLogin() because it finishes matching inside the
  // function, which can mean better safety.
  bool readForLogin(const std::wstring& name, const std::wstring& password);

  // Returns true if this function can work normally and successfully get
  // non-null result for its destination.
  // Example:
  //    if (test_reader.readFileLine(L"test.txt", 100, test_destination) {
  //      std::wcout.imbue(std::locale("chs"));
  //      std::wcout << test_destination << std::endl;
  //    }
  bool readFileLine(const std::wstring& file_name, unsigned int row_serial,
                    std::wstring& destination);

  // Used to delete specific line of given file name.
  // Returns true if this function can work normally.
  // Example:
  //    test_reader.deleteFileLine(L"test.txt", L"test");
  bool deleteFileLine(const std::wstring& file_name,
                      const std::wstring& request_line);

  // Used to delete non-null directory.
  // Returns true if this function can work normally.
  // Example:
  //    test_reader. 
  bool deleteDirectory(const std::wstring& directory_path);

  // Used to append a file new lines.
  bool appendLine(const std::wstring& file_name, const std::wstring& new_line);
};
}  // namespace library_management_sys
#endif  // LMS_BASE_READER_BASE_H_