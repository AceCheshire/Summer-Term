// * License: Apache 2.0
// * File: help_page.h
// * Author: Mai Tianle
// * Date: 2024-08-08
// * Description: Declare class HelpPage.
#include <string>

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_SPECIFIC_SCENE_HELP_PAGE_H_
#define LMS_SPECIFIC_SCENE_HELP_PAGE_H_
namespace library_management_sys {
namespace help_page {
// File name that is used to load HelpPage.
constexpr wchar_t kPageDataSource[] = L"res/help_page_data.dat";
}  // namespace help_page

// Used to shape the norm of help pages.
// Example:
//    PageUnitEx test_unit_ex;
//    HelpPage test_help_page(test_unit_ex);
class HelpPage : public Scene {
 public:
  HelpPage(PageUnitEx& pageunit_list_head);  // Constructor.

  // Returns true if no errors are thrown.
  // Used to start a scene. Example:
  //    test_scene.prepareScene();
  bool prepareScene();

  void inputInfo() {}  // No input interface

  bool checkLink(unsigned short check_mode) {
    return true;
  }  // No check interface

  bool getMouseInputState() { return true; }

  bool getKeyboardInputState() { return true; }
};
}  // namespace library_management_sys
#endif  // LMS_SPECIFIC_SCENE_HELP_PAGE_H_