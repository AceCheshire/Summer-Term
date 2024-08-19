// * License: Apache 2.0
// * File: home_page.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define class HomePage.
#include "inc/inheritance/scene/home_page/home_page.h"

#include <windows.h>

#include <iostream>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
namespace library_management_sys {
HomePage::HomePage(PageUnitEx& pageunit_list_head)
    : Scene(pageunit_list_head) {}

bool HomePage::prepareScene() {
  try {
    layoutText();
  } catch (BasicError& err_num) {
    // Red error output
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: class HomePage | function prepareScene | err_num "
              << err_num << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_WHITE);  // Set default color
    return false;
  }
  return true;
}
}  // namespace library_management_sys