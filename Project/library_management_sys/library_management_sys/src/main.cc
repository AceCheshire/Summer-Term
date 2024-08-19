// * License: Apache 2.0
// * File: main.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define main function.
#include "inc/base/book_base.h"
#include "inc/base/error_base.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#include "inc/base/user_base.h"
#include "inc/inheritance/scene/help_page/help_page.h"
#include "inc/inheritance/scene/home_page/home_page.h"
#include "inc/inheritance/scene/login_page/login_page.h"
#include "inc/inheritance/scene/portal_page/portal_page.h"
#include "inc/inheritance/scene/search_page/search_page.h"
int main() {
  using namespace library_management_sys;

  // Init Mouse and Reader instances & hide cursor
  Page global_page;
  Mouse global_mouse;
  Reader global_reader;
  User global_current_user;
  User global_searching_user;
  Book global_searching_book;
  int shared_task = 0;
  global_page.hideCursor(true);

  // Create
  // Ex instances
  PageUnitEx home_page_text;
  PageUnitEx login_page_text;
  PageUnitEx help_page_text;
  PageUnitEx portal_page_text;
  PageUnitEx search_page_text;

  // Read for PageUnitEx assignment
  global_reader.readForPointPaint(home_page_text, home_page::kPageDataSource);
  global_reader.readForPointPaint(login_page_text, login_page::kPageDataSource);
  global_reader.readForPointPaint(help_page_text, help_page::kPageDataSource);
  global_reader.readForPointPaint(portal_page_text,
                                  portal_page::kPageDataSource);
  global_reader.readForPointPaint(search_page_text,
                                  search_page::kPageDataSource);

  // Init Scene instances
  HomePage home_page(home_page_text);
  LoginPage login_page(login_page_text, global_current_user);
  HelpPage help_page(help_page_text);
  PortalPage portal_page(portal_page_text, global_current_user, shared_task);
  SearchPage search_page(search_page_text, global_current_user,
                         global_searching_user, global_searching_book,
                         shared_task);

  // Init Scheduler instance
  Scheduler global_scheduler(global_mouse, 0);

  // Maintain schedule_match_table_
  global_scheduler.appendScene(home_page, 0);
  global_scheduler.appendScene(login_page, 1);
  global_scheduler.appendScene(help_page, 2);
  global_scheduler.appendScene(portal_page, 3);
  global_scheduler.appendScene(search_page, 4);

  // Init Link instances (Scheduler&  string now next mode)
  Link home_to_login(global_scheduler, L"Login", 0, 1, 0);
  Link home_to_help(global_scheduler, L"Help", 0, 2, 0);
  Link login_to_home(global_scheduler, L"Back", 1, 0, 0);
  Link login_to_portal(global_scheduler, L"Login", 1, 3, 1);
  Link help_to_home(global_scheduler, L"Back", 2, 0, 0);
  Link portal_to_search_user(global_scheduler, L"User", 3, 4, portal_page::kUser);
  Link portal_to_search_book(global_scheduler, L"Book", 3, 4, portal_page::kBook);
  Link search_to_portal(global_scheduler, L"Back", 4, 3, 0);
  Link search_add(global_scheduler, L"Add", 4, 4, search_page::kAddLink);
  Link search_delete(global_scheduler, L"Delete", 4, 4, search_page::kDelete);
  Link search_search(global_scheduler, L"Search", 4, 4, search_page::kSearch);
  Link search_up(global_scheduler, L"Up", 4, 4, search_page::kUp);
  Link search_down(global_scheduler, L"Down", 4, 4, search_page::kDown);
  Link search_modify(global_scheduler, L"Modify", 4, 4, search_page::kModifyLink);

  // Maintain button_list_
  global_scheduler.appendLink(home_to_login);
  global_scheduler.appendLink(home_to_help);
  global_scheduler.appendLink(login_to_home);
  global_scheduler.appendLink(login_to_portal);
  global_scheduler.appendLink(help_to_home);
  global_scheduler.appendLink(portal_to_search_user);
  global_scheduler.appendLink(portal_to_search_book);
  global_scheduler.appendLink(search_to_portal);
  global_scheduler.appendLink(search_add);
  global_scheduler.appendLink(search_delete);
  global_scheduler.appendLink(search_search);
  global_scheduler.appendLink(search_up);
  global_scheduler.appendLink(search_down);
  global_scheduler.appendLink(search_modify);

  // Main control
  while (true) {
    global_scheduler.generalSchedule();
  }

  // Release PageUnitEx memory.
  help_page_text.deleteAll();
  login_page_text.deleteAll();
  home_page_text.deleteAll();
  portal_page_text.deleteAll();
  search_page_text.deleteAll();
  return 0;
}