// * 文件：help_page.h
// * 作者：麦天乐
// * 介绍：声明 HelpPage 类。
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_INHERITANCE_SCENE_HELP_PAGE_H_
#define LMS_INHERITANCE_SCENE_HELP_PAGE_H_
namespace library_management_sys {
// 规定了应用帮助页面的范式。示例：
//    PageUnitEx test_unit_ex;
//    HelpPage test_help_page(test_unit_ex);
class HelpPage : public Scene {
 public:
  HelpPage(PageUnitEx& pageunit_list_head);  // 构造函数
  // 用于启动场景，并返回真。示例：
  //    test_scene.prepareScene();
  bool prepareScene();
  void inputInfo() {}                                         // 无输入接口
  bool checkLink(unsigned short check_mode) { return true; }  // 无场景过渡
  bool getMouseInputState() { return true; }     // 允许鼠标输入
  bool getKeyboardInputState() { return true; }  // 允许键盘输入
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_HELP_PAGE_H_