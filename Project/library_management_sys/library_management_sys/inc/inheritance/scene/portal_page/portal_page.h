// * License: Apache 2.0
// * File: portal_page.h
// * Author: Mai Tianle
// * Date: 2024-08-11
// * Description: Declare class PortalPage.
#include <string>

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/user_base.h"
#ifndef LMS_SPECIFIC_SCENE_PORTAL_PAGE_H_
#define LMS_SPECIFIC_SCENE_PORTAL_PAGE_H_
namespace library_management_sys {
namespace portal_page {
// Represents the check mode serials for checkLink();
// Should be the same as search_page::PortalTask and detail_page::PortalTask.
enum CheckMode { kUser = 1, kBook };

// File name that is used to load PortalPage.
constexpr wchar_t kPageDataSource[] = L"res/portal_page_data.dat";
}  // namespace portal_page

// Used to shape the norm of portal pages.
// Example:
//    PageUnitEx test_unit_ex;
//    User test_user;
//    PortalPage test_portal_page(test_unit_ex, test_user);
class PortalPage : public Scene {
 public:
  PortalPage(PageUnitEx& pageunit_list_head, User& current_user,
             int& shared_task);  // Constructor.

  // Returns true if no errors are thrown.
  // Used to start a scene. Example:
  //    test_scene.prepareScene();
  bool prepareScene();

  void inputInfo() {}  // No input interface

  // Always returns true, and tells what scene_page need to operate.
  bool checkLink(unsigned short check_mode);

  bool getMouseInputState() { return true; }

  bool getKeyboardInputState() { return true; }

 private:
  // Displays user name before text ", hello".
  void displayUserName();

  // Used to read current user info.
  User* current_user_;

  // Used to record choice in portal_page.
  int* shared_task_;
};
}  // namespace library_management_sys
#endif  // LMS_SPECIFIC_SCENE_PORTAL_PAGE_H_