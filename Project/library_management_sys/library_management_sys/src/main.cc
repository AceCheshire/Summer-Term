// * License: Apache 2.0
// * File: main.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define main function.
#include "inc/base/error_base.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#include "inc/specific/scene/help_page/help_page.h"
#include "inc/specific/scene/home_page/home_page.h"
#include "inc/specific/scene/login_page/login_page.h"
using namespace library_management_sys;
int main() {
  // Init Mouse and Reader  instances & hide cursor
  Page extra_page;
  Mouse global_mouse;
  Reader global_reader;
  extra_page.hideCursor(true);

  // Create PageUnitEx instances
  PageUnitEx home_page_text;
  PageUnitEx login_page_text;
  PageUnitEx help_page_text;

  // Read for PageUnitEx assignment
  global_reader.readForPointPaint(home_page_text, kHomePageDataSource);
  global_reader.readForPointPaint(login_page_text, kLoginPageDataSource);
  global_reader.readForPointPaint(help_page_text, kHelpPageDataSource);

  // Init Scene instances
  HomePage home_page(home_page_text);
  LoginPage login_page(login_page_text);
  HelpPage help_page(help_page_text);

  // Init Scheduler instance
  Scheduler global_scheduler(global_mouse, home_page);

  // Maintain schedule_match_table_
  global_scheduler.appendScene(home_page, 0);
  global_scheduler.appendScene(login_page, 1);
  global_scheduler.appendScene(help_page, 2);

  // Init Link instances
  Link home_to_login_admin(global_scheduler, "Login_as_admin", 1);
  Link home_to_login_guest(global_scheduler, "Login_as_guest", 1);
  Link home_to_help(global_scheduler, "Help", 2);

  // Maintain button_list_
  global_scheduler.appendLink(home_to_login_admin);
  global_scheduler.appendLink(home_to_login_guest);
  global_scheduler.appendLink(home_to_help);

  // Main control
  while (true) {
    global_scheduler.generalSchedule();
  }

  // Release PageUnitEx memory.
  help_page_text.deleteAll();
  login_page_text.deleteAll();
  home_page_text.deleteAll();
  return 0;
}