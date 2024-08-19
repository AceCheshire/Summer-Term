// * License: Apache 2.0
// * File: detail_page.h
// * Author: Mai Tianle
// * Date: 2024-08-17
// * Description: Declare class DetailPage.
#include <windows.h>

#include <string>

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/user_base.h"
#include "inc/base/book_base.h"
#ifndef LMS_SPECIFIC_SCENE_DETAIL_PAGE_H_
#define LMS_SPECIFIC_SCENE_DETAIL_PAGE_H_
namespace library_management_sys {
namespace detail_page {
// Represents the portal task serials for checkLink();
// Should be the same as search_page::PortalTask and portal_page::CheckMode.
enum PortalTask { kUser = 1, kBook };

// Represents the search task serials for checkLink();
// Should be the same as search_page::CheckMode.
enum SearchTask { kSearch = 1, kUp, kDown, kAdd, kDelete, kModify };

// Belows are guidance texts that are used to wake input column.
enum CheckMode {
  kNameLink = 1,
  kAuthorLink,
  kTypeLink,
  kTagLink,
  kDescriptionLink,
  kPermissionLink,
  kPasswordLink,
  kAddLink,
  kModifyLink,
  kCancelLink,
  kBorrowLink,
  kReturnLink
};

constexpr wchar_t kNameText[] = L"Name";
constexpr wchar_t kAuthorText[] = L"Author";
constexpr wchar_t kTypeText[] = L"Type";
constexpr wchar_t kTagText[] = L"Tag";
constexpr wchar_t kStateText[] = L"State";
constexpr wchar_t kDescriptionText[] = L"Description";
constexpr wchar_t kPasswordText[] = L"Password";
constexpr wchar_t kPermissionText[] = L"Permission";
constexpr wchar_t kAddText[] = L"Add";
constexpr wchar_t kModifyText[] = L"Modify";
constexpr wchar_t kCancelText[] = L"Cancel";
constexpr wchar_t kHistoryText[] = L"History";
constexpr wchar_t kReturnText[] = L"Return";
constexpr wchar_t kBorrowText[] = L"Borrow";

// File name that is used to load LoginPage.
constexpr wchar_t kPageDataSource[] = L"res/detail_page_data.dat";

constexpr WORD kModifyColor = FOREGROUND_BLUE;
constexpr WORD kAddColor = FOREGROUND_GREEN;
constexpr WORD kReturnColor = FOREGROUND_GREEN | FOREGROUND_RED;
constexpr WORD kBorrowColor = FOREGROUND_GREEN | FOREGROUND_RED;
constexpr WORD kCancelColor = FOREGROUND_RED;

constexpr COORD kModifyPos = {15,5};
constexpr COORD kAddPos = {15,5};
constexpr COORD kReturnPos = {25,5};
constexpr COORD kBorrowPos = {15,5};
constexpr COORD kCancelPos = {25,5};
// The appearance of pointer.
constexpr wchar_t kPointerText[] = L"*";
constexpr WORD kPointerColor = FOREGROUND_GREEN | FOREGROUND_RED;

// The symbol of administrator.
constexpr wchar_t kAdminText[] = L"Administrator";

// The symbol of guest.
constexpr wchar_t kGuestText[] = L"Guest";
 
// How far pointer will appear from the chosen text.
constexpr COORD kPointerOffset = {-4, 0};
}  // namespace detail_page

// Used to shape the norm of detail pages.
// Example:
//    PageUnitEx test_unit_ex;
//    DetailPage test_detail_page(test_unit_ex);
class DetailPage : public Scene {
 public:
  // The first pageunit_list_head_ will be used to construct the based Scene.
  DetailPage(PageUnitEx& pageunit_list_head_1, PageUnitEx& pageunit_list_head_2,
             User& current_user, User& searching_user, Book& searching_book,
             int& shared_task);  // Constructor.

  // Returns true if no errors are thrown.
  // Used to start a scene. Example:
  //    test_scene.prepareScene();
  bool prepareScene();

  // Works when client is inputting text.
  // Example:
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();

  // Returns true if User or Book is correctly modified or added.
  bool checkLink(unsigned short check_mode);

  bool getMouseInputState() { return true; }

  bool getKeyboardInputState() { return true; }

 private:
  // Displays book or user information according to guidance text.
  void displayInfo(COORD offset, WORD color);

  // Returns where the output will be for pointPaint().
  COORD getInfoPosition(const std::wstring& guidance_text);

  // Matches the given text to find approximate position and draws
  // pointer at the calculated place.
  void pointerDisplay(const std::wstring& match_text);

  // Used to record the user detail page
  PageUnitEx* pageunit_list_head_1_;

  // Used to record the book detail page
  PageUnitEx* pageunit_list_head_2_;

  // Used to read current user info.
  User* current_user_;

  // Used to read and write searching user info.
  User* searching_user_;

  // Used to read and write searching book info.
  Book* searching_book_;

  // Used to record choice in portal_page and search_page.
  int* shared_task_;

  // Used to record input option of client.
  int option_ = 0;

  // Used to record input guidance of client.
  std::wstring option_text_;

  // Used to record client's password request.
  std::wstring password_request_;

  // Used to record client's input.
  User temp_user_;
  Book temp_book_;
};
}  // namespace library_management_sys
#endif  // LMS_SPECIFIC_SCENE_LOGIN_PAGE_H_