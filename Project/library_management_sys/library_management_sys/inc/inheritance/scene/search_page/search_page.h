// * License: Apache 2.0
// * File: search_page.h
// * Author: Mai Tianle
// * Date: 2024-08-15
// * Description: Declare class SearchPage.
#include <windows.h>

#include <string>

#include "inc/base/book_base.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/user_base.h"
#ifndef LMS_SPECIFIC_SCENE_SEARCH_PAGE_H_
#define LMS_SPECIFIC_SCENE_SEARCH_PAGE_H_
// Folder of user detail.
#define kUserFolderPath(USER_NAME) L"res\\user\\" + (USER_NAME) + L"\\";

// Folder of book detail.
#define kBookFolderPath(BOOK_NAME) L"res\\book\\" + (BOOK_NAME) + L"\\";
namespace library_management_sys {
namespace search_page {
// Represents the portal task serials for checkLink();
// Should be the same as search_page::PortalTask and detail_page::PortalTask.
enum PortalTask { kUser = 1, kBook };

// Represents the check mode serials for checkLink();
// Should be the same as detail_page::SearchTask.
enum CheckMode { kSearch = 1, kUp, kDown, kAdd, kDelete, kModify };

// File name that is used to load SearchPage.
constexpr wchar_t kPageDataSource[] = L"res/search_page_data.dat";

// Outline of users.
constexpr wchar_t kUserDataSource[] = L"res/user/user.dat";

// Outline of books.
constexpr wchar_t kBookDataSource[] = L"res/book/book.dat";

// Guidance text that point out the position for searching.
constexpr wchar_t kStartPointText[] = L">";

// Guidance text that point out there are no matched results.
constexpr wchar_t kNotMatchText[] = L"Sorry, there are no results found";

// How far the input column will appear from the guidance like ">".
constexpr COORD kInputOffset = {2, 0};

// How far the search results will appear from the guidance like ">".
constexpr COORD kSearchOffset = {5, 2};

// How far search results will keep from each other.
constexpr COORD kRowOffset = {0, 2};

// The appearance of pointer.
constexpr wchar_t kPointerText[] = L"*";
constexpr WORD kPointerColor = FOREGROUND_GREEN | FOREGROUND_RED;

// How far search pointer will keep from searching result.
constexpr COORD kPointerOffset = {-5, 0};

// The max number of searching results displayed on screen
constexpr unsigned short kMaxSearchNum = 10;
}  // namespace search_page

// Used to shape the norm of search pages.
// Example:
//    PageUnitEx test_unit_ex;
//    SearchPage test_search_page(test_unit_ex);
class SearchPage : public Scene {
 public:
  SearchPage(PageUnitEx& pageunit_list_head, User& current_user,
             User& searching_user, Book& searching_book,
             int& portal_task);  // Constructor.

  // Returns true if no errors are thrown.
  // Used to start a scene. Example:
  //    test_scene.prepareScene();
  bool prepareScene();

  // Works when client is inputting text of user, book or history.
  // Example:
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();

  // Realizes different replies to links like "Search" and "Delete".
  bool checkLink(unsigned short check_mode);

  bool getMouseInputState() { return true; }

  bool getKeyboardInputState() { return true; }

 private:
  // Deletes the line in outline file and the folder of the detail
  void del(const std::wstring& searching_object);

  // Searches target string in the given file, and assignes
  // the member result_ with the most similar ones.
  void search();

  // Calculate the number of matched characters, and returns the match rate.
  double getSimilarity(const std::wstring& request,
                       const std::wstring& finding);

  // Displays the searching results. Returns false always.
  bool searchDisplay();

  // Displays the pointer.
  void pointerDisplay();

  // Used to read and write current user info.
  User* current_user_;

  // Used to read and write searching user info.
  User* searching_user_;

  // Used to read and write searching book info.
  Book* searching_book_;

  // Used to record choice in portal_page and search_page.
  int* shared_task_;

  // Used to record client's input.
  std::wstring request_;

  // Used to record searching results.
  std::wstring result_[search_page::kMaxSearchNum] = {};

  // Used to record similarity of searching results.
  double similarity_value_[search_page::kMaxSearchNum] = {};

  // Used to record choosing object.
  int iterator_ = 0;

  // Used to record number of searched objects.
  unsigned short search_size_ = 0;
};
}  // namespace library_management_sys
#endif  // LMS_SPECIFIC_SCENE_SEARCH_PAGE_H_