// * License: Apache 2.0
// * File: search_page.cc
// * Author: Mai Tianle
// * Date: 2024-08-15
// * Description: Define class SearchPage.
#include "inc/inheritance/scene/search_page/search_page.h"

#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
SearchPage::SearchPage(PageUnitEx& pageunit_list_head, User& current_user,
                       User& searching_user, Book& searching_book,
                       int& shared_task)
    : Scene(pageunit_list_head),
      current_user_(&current_user),
      searching_user_(&searching_user),
      searching_book_(&searching_book),
      shared_task_(&shared_task) {}

bool SearchPage::prepareScene() {
  try {
    layoutText();
    if (*shared_task_ > 10) *shared_task_ /= 10;  // Back from detail_page
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: class SearchPage | function prepareScene | err_num "
              << err_num << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_WHITE);  // Set default color
    return false;
  }
  return true;
}

void SearchPage::inputInfo() {
  Page tmp_page;  // temp Page for interface
  // Find where the guidance text is by checking Scene member
  // pageunit_list_head_
  COORD tmp_coord_for_input =
      pageunit_list_head_->findByText(search_page::kStartPointText)->getPageUnit().pos;
  // Calculate where the input column should be
  tmp_coord_for_input.X += search_page::kInputOffset.X;
  tmp_coord_for_input.Y += search_page::kInputOffset.Y;
  // Clean last input
  tmp_page.returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_input);
  std::wcout.imbue(std::locale("chs"));
  for (int i = 0; i < request_.length(); i++) std::wcout << " ";
  // Move the cursor to the beginning, display the cursor and client inputs
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_input);
  tmp_page.hideCursor(false);
  request_ = inputLine(true);  // Like std::cin
  tmp_page.hideCursor(true);
}

bool SearchPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;  // Cancel checkLink()
  switch (check_mode) {
    case search_page::kSearch:
      // Reset search recorders
      for (int i = 0; i < search_page::kMaxSearchNum; i++) {
        while (result_[i].length()) result_[i].pop_back();
        similarity_value_[i] = 0;
      }
      iterator_ = search_size_ = 0;
      search();
      return searchDisplay();
    case search_page::kAdd:
      *shared_task_ = *shared_task_ * 10 + search_page::kAdd;
      return true;
    case search_page::kDelete:
      del(result_[iterator_ - 1]);
      return checkLink(search_page::kSearch);
    case search_page::kUp:
      if (iterator_ == 0) iterator_ = search_size_;
      else iterator_--;
      pointerDisplay();
      return false;
    case search_page::kDown:
      if (iterator_ == search_size_) iterator_ = 0;
      else iterator_++;
      pointerDisplay();
      return false;
    case search_page::kModify:
      if (*shared_task_ == search_page::kUser)
        searching_user_->setName(result_[iterator_ - 1]);
      if (*shared_task_ == search_page::kBook)
        searching_book_->setName(result_[iterator_ - 1]);
      *shared_task_ = *shared_task_ * 10 + search_page ::kModify;
      return true;
    default:
      return false;
  }  // switch (check_mode)
}

void SearchPage::del(const std::wstring& searching_object) {
  Reader tmp_reader;  // temp Reader for interface
  // Locate the data file and folder
  std::wstring file_name;
  std::wstring folder_name;
  switch (*shared_task_) {
    case search_page::kUser:
      file_name = search_page::kUserDataSource;
      folder_name = kBookFolderPath(searching_object);
      break;
    case search_page::kBook:
      file_name = search_page::kBookDataSource;
      folder_name = kUserFolderPath(searching_object);
      break;
  }  // switch (*shared_task_)
  tmp_reader.deleteFileLine(file_name, searching_object);
  tmp_reader.deleteDirectory(folder_name);
}

void SearchPage::search() {
  Reader tmp_reader;  // temp Reader for interface
  // Locate the data file
  std::wstring file_name;
  switch (*shared_task_) {
    case search_page::kUser:
      file_name = search_page::kUserDataSource;
      break;
    case search_page::kBook:
      file_name = search_page::kBookDataSource;
      break;
  }  // switch (*shared_task_)
  int row_iterator = 1;
  std::wstring finding;
  // Read lines in the target file
  while (tmp_reader.readFileLine(file_name,row_iterator,finding)){
    row_iterator++;
    // Calculate the similarity rate of every line with request
    double similarity_iterator = getSimilarity(request_, finding);
    // Judge if newly operated line can be put into result_
    if (similarity_value_[0] >= similarity_iterator) continue;
    else {
      similarity_value_[0] = similarity_iterator;
      result_[0] = finding;
      // Replacing does not add search_size_, but adding does
      if (search_size_ < search_page::kMaxSearchNum) search_size_++;
    }
    // Sort the result_
    for (int serial_iterator = 1; serial_iterator < search_page::kMaxSearchNum;
         serial_iterator++) {
      if (similarity_value_[serial_iterator] >= similarity_iterator) break;
      else {
        std::swap(similarity_value_[serial_iterator],
                  similarity_value_[serial_iterator - 1]);
        std::swap(result_[serial_iterator], result_[serial_iterator - 1]);
      }
    }
  }
}

double SearchPage::getSimilarity(const std::wstring& request, const std::wstring& finding) {
  std::wstring finding_sort = finding;  // Copy of finding specially for sorting
  std::wstring request_sort = request;  // Copy of request specially for sorting
  // Sorting expected result example: L"apple" -> L"aelpp"
  std::sort(request_sort.begin(), request_sort.end());
  std::sort(finding_sort.begin(), finding_sort.end());
  // Calculate the number of the same characters
  // Example:
  // request: apple  ©¤©¤ aelpp  ©¤©¤ ael    ©¤©¤ ael  ©¤©¤ a    ©¤©¤ a   ©¤©¤©´
  // finding: banana ©¤©¤ aaabnn ©¤©¤ aaabnn ©¤©¤ aaab ©¤©¤ aaab ©¤©¤ aaa ©¤©¤©Ø©¤©¤ END
  //                                                   iterator + 1 -> return 1 / 5
  int num_iterator = 0;
  // Repeat until one of the two strings has no more char
  while (request_sort.length() && finding_sort.length()) {
    // Case 1: two strings have the same characters 
    if (finding_sort.back() == request_sort.back()) {
      finding_sort.pop_back();
      request_sort.pop_back();
      num_iterator++;
      continue;
    }
    // Case 2: finding has more big characters
    if (finding_sort.back() > request_sort.back()) {
      finding_sort.pop_back();
      continue;
    }
    // Case 3: request has more big characters
    if (finding_sort.back() < request_sort.back()) {
      request_sort.pop_back();
      continue;
    }
  }
  return (double)num_iterator / (double)request.length();
}

bool SearchPage::searchDisplay() {
  Page tmp_page;  // temp Page for interface
  // Clear old searching results and re-display the request_
  system("cls");
  prepareScene();
  COORD tmp_coord_for_input =
      pageunit_list_head_->findByText(search_page::kStartPointText)
          ->getPageUnit()
          .pos;
  tmp_coord_for_input.X += search_page::kInputOffset.X;
  tmp_coord_for_input.Y += search_page::kInputOffset.Y;
  tmp_page.pointPaint(tmp_coord_for_input, FOREGROUND_DEFAULT, request_);
  // Calculate the first searching result position
  COORD searching_result_location =
      pageunit_list_head_->findByText(search_page::kStartPointText)
          ->getPageUnit()
          .pos;
  searching_result_location.X +=
      search_page::kSearchOffset.X + search_page::kRowOffset.X * search_size_;
  searching_result_location.Y +=
      search_page::kSearchOffset.Y + search_page::kRowOffset.Y * search_size_;
  // If no result to be displayed
  if (search_size_ == 0) {
    tmp_page.pointPaint(searching_result_location, FOREGROUND_RED,
                        search_page::kNotMatchText);
    return false;
  }
  iterator_ = 1;  // Reset the ierator_, which is equivalent to pointer
  pointerDisplay();
  // Display searching results
  for (int i = search_page::kMaxSearchNum - search_size_;
       i < search_page::kMaxSearchNum; i++) {
    searching_result_location.X -= search_page::kRowOffset.X;
    searching_result_location.Y -= search_page::kRowOffset.Y;
    tmp_page.pointPaint(searching_result_location, FOREGROUND_DEFAULT,
                        result_[i]);
  }
  return false;
}

void SearchPage::pointerDisplay() {
  Page tmp_page;  // temp Page for interface
  // Calculate the initial position of pointer;
  COORD pointer_coord =
      pageunit_list_head_->findByText(search_page::kStartPointText)
          ->getPageUnit()
          .pos;
  pointer_coord.X +=
      search_page::kSearchOffset.X + search_page::kPointerOffset.X;
  pointer_coord.Y +=
      search_page::kSearchOffset.Y + search_page::kPointerOffset.Y;
  // Paint L" " or pointer text across the possible track of pointer
  for (int i = 0; i < search_page::kMaxSearchNum; i++) {
    if (i == iterator_ - 1)
      tmp_page.pointPaint(pointer_coord, search_page::kPointerColor,
                          search_page::kPointerText);
    else
      tmp_page.pointPaint(pointer_coord, FOREGROUND_DEFAULT, L" ");
    pointer_coord.X += search_page::kRowOffset.X;
    pointer_coord.Y += search_page::kRowOffset.Y;
  }
}
}  // namespace library_management_sys