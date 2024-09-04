// * 文件：home_page.cc
// * 作者：麦天乐
// * 介绍：定义 HomePage 类。
#include "inc/inheritance/scene/home_page/home_page.h"

#include "inc/app_const.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
namespace library_management_sys {
HomePage::HomePage(PageUnitEx& pageunit_list_head, Scheduler& scheduler)
    : Scene(pageunit_list_head), scheduler_(&scheduler) {}

bool HomePage::prepareScene() {
  layoutText();
  return true;
}

bool HomePage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;
  if (check_mode == home_page::kExit) scheduler_->exit();
  return false;
}
}  // namespace library_management_sys