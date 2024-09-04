// * 文件：portal_page.h
// * 作者：麦天乐
// * 介绍：声明 PortalPage 类。
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#ifndef LMS_INHERITANCE_SCENE_PORTAL_PAGE_H_
#define LMS_INTERITANCE_SCENE_PORTAL_PAGE_H_
namespace library_management_sys {
// 规定了应用导航页面的范式。示例：
//    PageUnitEx test_unit_ex;
//    PortalPage test_portal_page(test_unit_ex, test_scheduler);
class PortalPage : public SharedScene {
 public:
  PortalPage(PageUnitEx& pageunit_list_head, Scheduler& scheduler);  // 构造函数
  // 用于启动场景，并返回真。示例：
  //    test_scene.prepareScene();
  bool prepareScene();
  void inputInfo() {}  // 无输入接口
  // 用于设置后续场景需要处理的任务，并总是返回真。
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // 允许鼠标输入
  bool getKeyboardInputState() { return true; }  // 允许键盘输入

 private:
  // 在字段 “ , hello ” 前显示当前登录用户名称。
  void displayUserName();
  // 显示统计信息
  void displayStatistic();
  // 用于传递终止程序信息
  Scheduler* scheduler_ = NULL;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_PORTAL_PAGE_H_