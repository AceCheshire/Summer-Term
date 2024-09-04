// * 文件：home_page.h
// * 作者：麦天乐
// * 介绍：声明 HomePage 类。
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#ifndef LMS_INHERITANCE_SCENE_HOME_PAGE_H_
#define LMS_INHERITANCE_SCENE_HOME_PAGE_H_
namespace library_management_sys {
// 规定了应用主页的范式。示例：
//    PageUnitEx test_unit_ex;
//    HomePage test_home_page(test_unit_ex, test_scehduler);
class HomePage : public Scene {
 public:
  HomePage(PageUnitEx& pageunit_list_head, Scheduler& scheduler);  // 构造函数
  // 用于启动场景，并返回真。示例：
  //    test_scene.prepareScene();
  bool prepareScene();
  void inputInfo() {}                            // 无输入接口
  bool checkLink(unsigned short check_mode);     //  退出程序
  bool getMouseInputState() { return true; }     // 允许鼠标输入
  bool getKeyboardInputState() { return true; }  // 允许键盘输入
 private:
  // 用于传递终止程序信息
  Scheduler* scheduler_ = NULL;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_HOME_PAGE_H_