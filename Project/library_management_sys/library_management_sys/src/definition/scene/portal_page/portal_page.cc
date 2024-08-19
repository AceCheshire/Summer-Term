// * License: Apache 2.0
// * File: portal_page.cc
// * Author: Mai Tianle
// * Date: 2024-08-11
// * Description: Define class PortalPage.
#include "inc/inheritance/scene/portal_page/portal_page.h"

#include <windows.h>

#include <iostream>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
PortalPage::PortalPage(PageUnitEx& pageunit_list_head, User& current_user,
                       int& shared_task)
    : Scene(pageunit_list_head),
      current_user_(&current_user),
      shared_task_(&shared_task) {}

bool PortalPage::prepareScene() {
  try {
    layoutText();
    displayUserName();
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: class PortalPage | function prepareScene | err_num "
              << err_num << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_WHITE);  // Set default color
    return false;
  }
  return true;
}

void PortalPage::displayUserName() {
  Page tmp_page;                 // Used for Page interface
  PageUnitEx* tmp_unit_pointer;  // Used as the return of findByText()
  std::wstring user_name = current_user_->getName();
  // If the return of findByText() is not NULL, which means found
  if ((tmp_unit_pointer = pageunit_list_head_->findByText(L", hello")) != NULL)
    tmp_page.pointPaint(
        // The ideal format is "user_name, hello", below are the calculation
        tmp_unit_pointer->getPageUnit().pos.X - (short)user_name.length(),
        tmp_unit_pointer->getPageUnit().pos.Y, page::GROUND_DEFAULT, user_name);
}

bool PortalPage::checkLink(unsigned short check_mode) {
  switch (check_mode) {
    case portal_page::kUser:
      *shared_task_ = portal_page::kUser;
      break;
    case portal_page::kBook:
      *shared_task_ = portal_page::kBook;
      break;
  }
  return true;
}
}  // namespace library_management_sys