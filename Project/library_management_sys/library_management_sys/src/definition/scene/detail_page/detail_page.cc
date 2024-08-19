// * License: Apache 2.0
// * File: detail_page.cc
// * Author: Mai Tianle
// * Date: 2024-08-17
// * Description: Define class DetailPage.
#include "inc/inheritance/scene/detail_page/detail_page.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/base/book_base.h"
#include "inc/base/error_base.h"
#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
DetailPage::DetailPage(PageUnitEx& pageunit_list_head_1,
                       PageUnitEx& pageunit_list_head_2, User& current_user,
                       User& searching_user, Book& searching_book,
                       int& shared_task)
    : Scene(pageunit_list_head_1),
      pageunit_list_head_1_(&pageunit_list_head_1),
      pageunit_list_head_2_(&pageunit_list_head_2),
      current_user_(&current_user),
      searching_user_(&searching_user),
      searching_book_(&searching_book),
      shared_task_(&shared_task) {}

bool DetailPage::prepareScene() {
  try {
    // Choose the text to display
    if (*shared_task_ / 10 == detail_page::kUser)
      setPageUnitList(*pageunit_list_head_1_);
    else if (*shared_task_ / 10 == detail_page::kBook)
      setPageUnitList(*pageunit_list_head_2_);
    layoutText();
    displayInfo({0, 0}, page::GROUND_DEFAULT);
    temp_user_.clear();
    temp_book_.clear();
    option_ = 0;
    option_text_.clear();
    password_request_.clear();
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: class DetailPage | function prepareScene | err_num "
               << err_num << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_WHITE);  // Set default color
    return false;
  }
}

void DetailPage::inputInfo() {
  if (!current_user_->checkPermission()) return;
  Page tmp_page;  // temp Page for interface
  // Find where the guidance text is by checking Scene member
  // pageunit_list_head_
  COORD tmp_coord_for_input =
      pageunit_list_head_->findByText(option_text_)->getPageUnit().pos;
  // Calculate where the input column should be
  tmp_coord_for_input.X += short(option_text_.length() + 1);
  // Clean last input
  tmp_page.returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_input);
  std::wcout.imbue(std::locale("chs"));
  if (option_ == detail_page::CheckMode::kDescriptionLink) {
    for (int i = 1; i <= max(temp_book_.getDescription().length(),
                             searching_book_->getDescription().length());
         i++) {
      std::wcout << " ";
      if (i % scene::adviceLength == 0) std::wcout << "\n";
    }
  } else
    for (int i = 0; i < scene::adviceLength; i++) std::wcout << " ";
  // Move the cursor to the beginning, display the cursor and client inputs
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_coord_for_input);
  tmp_page.hideCursor(false);
  switch (option_) {
    case detail_page::CheckMode::kNameLink:
      ((*shared_task_) / 10 == detail_page::PortalTask::kBook)
          ? temp_book_.setName(inputLine(true))
          : temp_user_.setName(inputLine(false));
      break;
    case detail_page::CheckMode::kAuthorLink:
      temp_book_.setAuthor(inputLine(true));
      break;
    case detail_page::CheckMode::kDescriptionLink: {
      while (!kKeyDown(VK_CONTROL))
        temp_book_.setDescription(temp_book_.getDescription() +
                                  inputLine(true));
      break;
    }
    case detail_page::CheckMode::kPasswordLink:
      password_request_ = inputLine(false);
      break;
    case detail_page::CheckMode::kPermissionLink: {
      std::wstring temp_string = inputLine(true);
      if (temp_string == detail_page::kAdminText)
        temp_user_.setPermission(true);
      else if (temp_string == detail_page::kGuestText)
        temp_user_.setPermission(false);
      else {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                 tmp_coord_for_input);
        std::wcout.imbue(std::locale("chs"));
        (searching_user_->checkPermission())
            ? std::wcout << detail_page::kAdminText
            : std::wcout << detail_page::kGuestText;
      }
      break;
    }
    case detail_page::CheckMode::kTagLink:
      temp_book_.setTag(inputLine(true));
      break;
    case detail_page::CheckMode::kTypeLink:
      temp_book_.setType(inputLine(true));
      break;
  }
  tmp_page.hideCursor(true);
}

bool DetailPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;
  std::wstring prevoius_option_text = option_text_;
  option_ = check_mode;
  switch (check_mode) {
    case detail_page::CheckMode::kNameLink:
      option_text_ = detail_page::kNameText;
      break;
    case detail_page::CheckMode::kAuthorLink:
      option_text_ = detail_page::kAuthorText;
      break;
    case detail_page::CheckMode::kDescriptionLink:
      option_text_ = detail_page::kDescriptionText;
      break;
    case detail_page::CheckMode::kPasswordLink:
      option_text_ = detail_page::kPasswordText;
      break;
    case detail_page::CheckMode::kPermissionLink:
      option_text_ = detail_page::kPermissionText;
      break;
    case detail_page::CheckMode::kTagLink:
      option_text_ = detail_page::kTagText;
      break;
    case detail_page::CheckMode::kTypeLink:
      option_text_ = detail_page::kTypeText;
      break;
    case detail_page::CheckMode::kBorrowLink:
    case detail_page::CheckMode::kReturnLink:
    case detail_page::CheckMode::kAddLink:;
    case detail_page::CheckMode::kModifyLink:;
    case detail_page::CheckMode::kCancelLink:
      system("cls");
      prepareScene();
      return false;
  }
  pointerDisplay(prevoius_option_text);
  return false;
}

void DetailPage::displayInfo(COORD offset, WORD color) {
  Page tmp_page;
  if (*shared_task_ % 10 == detail_page::kAdd) {
    tmp_page.pointPaint(detail_page::kAddPos,page::GROUND_DEFAULT,)
  } else {
    if (*shared_task_ / 10 == detail_page::kUser) {
      tmp_page.pointPaint(getInfoPosition(detail_page::kNameText),
                          page::GROUND_DEFAULT, searching_user_->getName());
      tmp_page.pointPaint(
          getInfoPosition(detail_page::kPermissionText), page::GROUND_DEFAULT,
          (searching_user_->checkPermission()) ? detail_page::kAdminText
                                               : detail_page::kGuestText);
      tmp_page.pointPaint(getInfoPosition(detail_page::kTagText),
                          page::GROUND_DEFAULT, searching_user_->getTag());
    } else if (*shared_task_ / 10 == detail_page::kBook) {
      tmp_page.pointPaint(getInfoPosition(detail_page::kNameText),
                          page::GROUND_DEFAULT, searching_book_->getName());
      tmp_page.pointPaint(getInfoPosition(detail_page::kAuthorText),
                          page::GROUND_DEFAULT, searching_book_->getAuthor());
      tmp_page.pointPaint(getInfoPosition(detail_page::kTypeText),
                          page::GROUND_DEFAULT, searching_book_->getType());
      tmp_page.pointPaint(getInfoPosition(detail_page::kTagText),
                          page::GROUND_DEFAULT, searching_book_->getTag());
      tmp_page.pointPaint(getInfoPosition(detail_page::kStateText),
                          page::GROUND_DEFAULT, searching_book_->getState());
      COORD tmp_position = getInfoPosition(detail_page::kDescriptionText);
      std::wstring tmp_description = searching_book_->getDescription();
      while (tmp_description.length()) {
        for (int i = 0; i < scene::adviceLength; i++) {
          tmp_page.pointPaint(tmp_position, page::GROUND_DEFAULT,
                              tmp_description.substr(0, 1));
          tmp_description = tmp_description.substr(1);
          tmp_position.X += 1;
        }
        std::wcout << std::endl;
        tmp_position.X -= scene::adviceLength;
        tmp_position.Y += 1;
      }
    }
  }
}

void DetailPage::pointerDisplay(const std::wstring& prevoius_text) {
  Page tmp_page;  // temp Page for interface
  // Calculate the initial position of pointer;
  COORD pointer_prevoius =
      pageunit_list_head_->findByText(prevoius_text)->getPageUnit().pos;
  COORD pointer_new =
      pageunit_list_head_->findByText(option_text_)->getPageUnit().pos;
  pointer_prevoius.X += detail_page::kPointerOffset.X;
  pointer_prevoius.Y += detail_page::kPointerOffset.Y;
  pointer_new.X += detail_page::kPointerOffset.X;
  pointer_new.Y += detail_page::kPointerOffset.Y;
  // Paint L" " or pointer text across the possible track of pointer
  tmp_page.pointPaint(pointer_prevoius, detail_page::kPointerColor, L" ");
  tmp_page.pointPaint(pointer_new, page::GROUND_DEFAULT,
                      detail_page::kPointerText);
}

COORD DetailPage::getInfoPosition(const std::wstring& guidance_text) {
  Page tmp_page;  // temp Page for interface
  // Find where the guidance text is by checking Scene member
  // pageunit_list_head_
  COORD tmp_coord =
      pageunit_list_head_->findByText(guidance_text)->getPageUnit().pos;
  // Calculate where the input column should be
  tmp_coord.X += short(guidance_text.length() + 1);
  return tmp_coord;
}
}  // namespace library_management_sys