// * 文件：main.cc
// * 作者：麦天乐
// * 介绍：定义主函数。
#include <locale>

#include "inc/app_const.h"
#include "inc/base/book_base.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#include "inc/base/user_base.h"
#include "inc/inheritance/scene/detail_page/detail_page.h"
#include "inc/inheritance/scene/help_page/help_page.h"
#include "inc/inheritance/scene/home_page/home_page.h"
#include "inc/inheritance/scene/login_page/login_page.h"
#include "inc/inheritance/scene/portal_page/portal_page.h"
#include "inc/inheritance/scene/search_page/search_page.h"
int main() {
  setlocale(LC_ALL, "chs");  // 设置语言
  using namespace library_management_sys;
  Page::hideCursor(true);  // 隐藏鼠标

  // 创建拓展页面单元实例
  PageUnitEx home_page_text;
  PageUnitEx login_page_text;
  PageUnitEx help_page_text;
  PageUnitEx portal_page_text;
  PageUnitEx search_page_text;
  PageUnitEx detail_page_text_1;
  PageUnitEx detail_page_text_2;
  PageUnitEx detail_page_text_3;
  PageUnitEx detail_page_text_4;
  PageUnitEx detail_page_text_5;
  PageUnitEx detail_page_text_6;

  // 读取场景文本实例
  Reader::readForPointPaint(home_page_text, home_page::kPageDataSource);
  Reader::readForPointPaint(login_page_text, login_page::kPageDataSource);
  Reader::readForPointPaint(help_page_text, help_page::kPageDataSource);
  Reader::readForPointPaint(portal_page_text, portal_page::kPageDataSource);
  Reader::readForPointPaint(search_page_text, search_page::kPageDataSource);
  Reader::readForPointPaint(detail_page_text_1, detail_page::kPageDataSource1);
  Reader::readForPointPaint(detail_page_text_2, detail_page::kPageDataSource2);
  Reader::readForPointPaint(detail_page_text_3, detail_page::kPageDataSource3);
  Reader::readForPointPaint(detail_page_text_4, detail_page::kPageDataSource4);
  Reader::readForPointPaint(detail_page_text_5, detail_page::kPageDataSource5);
  Reader::readForPointPaint(detail_page_text_6, detail_page::kPageDataSource6);

  // 初始化调度器实例
  Scheduler global_scheduler(0);

  // 初始化场景实例
  HomePage home_page(home_page_text, global_scheduler);
  LoginPage login_page(login_page_text);
  HelpPage help_page(help_page_text);
  SearchPage search_page(search_page_text);
  PortalPage portal_page(portal_page_text, global_scheduler);
  DetailPage detail_page(detail_page_text_1, detail_page_text_2,
                         detail_page_text_3, detail_page_text_4,
                         detail_page_text_5, detail_page_text_6);

  // 挂载场景
  global_scheduler.appendScene(home_page, 0);
  global_scheduler.appendScene(login_page, 1);
  global_scheduler.appendScene(help_page, 2);
  global_scheduler.appendScene(portal_page, 3);
  global_scheduler.appendScene(search_page, 4);
  global_scheduler.appendScene(detail_page, 5);

  // 初始化链接实例（标识 当前场景 下一场景 任务指令）
  Link home_to_login(L"Login", 0, 1, 0);
  Link home_to_help(L"Help", 0, 2, 0);
  Link home_to_exit(L"Exit", 0, 0, 1);

  Link login_to_home(L"Back", 1, 0, 0);
  Link login_to_portal(L"Login", 1, 3, 1);

  Link help_to_home(L"Back", 2, 0, 0);

  Link portal_to_search_user(L"User", 3, 4, portal_page::kUser);
  Link portal_to_search_book(L"Book", 3, 4, portal_page::kBook);
  Link portal_to_exit(L"Exit", 3, 3, portal_page::kExit);

  Link search_to_portal(L"Back", 4, 3, 0);
  Link search_add(L"Add", 4, 5, search_page::kAdd);
  Link search_delete(L"Delete", 4, 4, search_page::kDelete);
  Link search_search(L"Search", 4, 4, search_page::kSearch);
  Link search_up(L"Up", 4, 4, search_page::kUp);
  Link search_down(L"Down", 4, 4, search_page::kDown);
  Link search_modify(L"Modify", 4, 5, search_page::kModify);

  Link detail_to_search(L"Back", 5, 4, 0);
  Link detail_add(L"Add", 5, 5, detail_page::kAddLink);
  Link detail_modify(L"Modify", 5, 5, detail_page::kModifyLink);
  Link detail_borrow(L"Borrow", 5, 5, detail_page::kBorrowLink);
  Link detail_return(L"Return", 5, 5, detail_page::kReturnLink);
  Link detail_cancel(L"Cancel", 5, 5, detail_page::kCancelLink);
  Link detail_name(L"Name", 5, 5, detail_page::kNameLink);
  Link detail_permission(L"Permission", 5, 5, detail_page::kPermissionLink);
  Link detail_password(L"Password", 5, 5, detail_page::kPasswordLink);
  Link detail_author(L"Author", 5, 5, detail_page::kAuthorLink);
  Link detail_type(L"Type", 5, 5, detail_page::kTypeLink);
  Link detail_description(L"Description", 5, 5, detail_page::kDescriptionLink);
  Link detail_plus(L"+", 5, 5, detail_page::kNextLink);
  Link detail_minus(L"-", 5, 5, detail_page::kLastLink);

  // 挂载链接
  global_scheduler.appendLink(home_to_login);
  global_scheduler.appendLink(home_to_help);
  global_scheduler.appendLink(home_to_exit);

  global_scheduler.appendLink(login_to_home);
  global_scheduler.appendLink(login_to_portal);

  global_scheduler.appendLink(help_to_home);

  global_scheduler.appendLink(portal_to_search_user);
  global_scheduler.appendLink(portal_to_search_book);
  global_scheduler.appendLink(portal_to_exit);

  global_scheduler.appendLink(search_to_portal);
  global_scheduler.appendLink(search_add);
  global_scheduler.appendLink(search_delete);
  global_scheduler.appendLink(search_search);
  global_scheduler.appendLink(search_up);
  global_scheduler.appendLink(search_down);
  global_scheduler.appendLink(search_modify);

  global_scheduler.appendLink(detail_to_search);
  global_scheduler.appendLink(detail_add);
  global_scheduler.appendLink(detail_modify);
  global_scheduler.appendLink(detail_borrow);
  global_scheduler.appendLink(detail_return);
  global_scheduler.appendLink(detail_cancel);
  global_scheduler.appendLink(detail_name);
  global_scheduler.appendLink(detail_permission);
  global_scheduler.appendLink(detail_password);
  global_scheduler.appendLink(detail_author);
  global_scheduler.appendLink(detail_type);
  global_scheduler.appendLink(detail_description);
  global_scheduler.appendLink(detail_plus);
  global_scheduler.appendLink(detail_minus);

  // 主控制
  global_scheduler.generalSchedule();

  // 释放拓展页面单元内存
  help_page_text.deleteAll();
  login_page_text.deleteAll();
  home_page_text.deleteAll();
  portal_page_text.deleteAll();
  search_page_text.deleteAll();
  detail_page_text_1.deleteAll();
  detail_page_text_2.deleteAll();
  return 0;
}