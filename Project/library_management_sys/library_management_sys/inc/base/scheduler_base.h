// * 文件：scheduler_base.h
// * 作者：麦天乐
// * 介绍：声明 Scheduler 类。
#include <string>

#include "inc/app_const.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_BASE_SCHEDULER_BASE_H_
#define LMS_BASE_SCHEDULER_BASE_H_
namespace library_management_sys {
// 调度器，以状态机方式整合不同场景。示例：
//    Scheduler test_scheduler(0);
class Scheduler : public SharedPool {
 public:
  // 构造函数，参数为使用者希望优先进入的场景的编号。
  Scheduler(unsigned short init_scene);
  // 应用的主要控制器。示例：
  //    Scheduler test_scheduler(test_init_scene);
  //    while (true) test_scheduler.generalSchedule();
  void generalSchedule();
  // 用于在运行时更改成员 active_scene_ ，并以此切换场景。
  // 如果成员 active_scene_ 被更改且即将跳出该场景，返回真。
  // 第一个参数为将要跳转到的场景编号，第二个参数为任务指令，参数均由链接给出。
  bool generalSwitch(unsigned short scene_number, unsigned short check_mode);
  // 维护成员 button_list_
  // 。同时挂载的链接数量不宜过多，否则程序将在运行时终止。 示例：
  //    test_scheduler.appendScene(test_scene, 0);
  //    Link test_link("test_text", 0, 1 ,0);
  //    test_scheduler.appendLink(test_link);
  //    while (true) test_scheduler.generalSchedule();
  void appendLink(Link& new_link);
  // 维护成员 schedule_match_table_ 。如果参数与已挂载的场景冲突或导致数组越界，
  // 程序将在运行时终止。示例：
  //    test_scheduler.appendScene(test_scene, 0);
  //    Link test_link("test_text", 0, 1, 0);
  //    test_scheduler.appendLink(test_link);
  //    while (true) test_scheduler.generalSchedule();
  void appendScene(Scene& new_scene, unsigned short target_pos);
  // 终止程序运行
  void exit() { is_to_exit_ = true; }

 protected:
  // 接受键盘及鼠标输入。参数为场景的输入模式，由场景给出。
  // 注意：键盘输入可能会被鼠标输入覆盖。
  // 示例：
  //    while (true) waitInput(true, true);
  void waitInput(bool is_keyboard_input_on, bool is_mouse_input_on);
  // Tab 键作为键盘按键允许键盘选择屏幕上的字符串。选中的字符串会高亮，
  // 且只有能够高亮的字符串会被选中。选中后按下回车视为点击此字符串。
  // 多次按下 Tab 键，高亮选择的顺序是：
  // 无 -> 场景文本中第一个满足条件的字符串 -> 第二个 -> ...
  // ... -> 最后一个 -> 无 -> ...
  // 示例:
  //    bool test_is_keyboard_input_on = true;
  //    if (test_is_keyboard_input_on) {
  //      if (kKeyDown(VK_TAB)) keyTab();
  //    }
  void keyTab();
  // 传入点击的字符串内容，在 button_list_ 中匹配满足条件的链接。若能够匹配，
  // 返回接收到的第一个有效的链接跳转编码，否则返回 -1 。
  int findLink(const std::wstring& msg);
  // 用于容纳鼠标输入
  Mouse built_mouse_;
  // 用于存储 Tab 键选择的页面单元
  PageUnitEx* current_tab_unit_ = NULL;
  // 用于区分输入状态，分为输入文本模式和非输入文本模式。
  bool is_inputting_info_ = false;
  // 记录当前场景，用于实现场景的多态。
  unsigned short active_scene_;
  // 用于记录中断请求。利用此可以实现场景切换，执行一次中断后需复位为假。
  bool is_to_break_ = false;
  // 用于记录退出请求。利用此可以实现终止程序。
  bool is_to_exit_ = false;
  // 用于挂载链接，作为 findLink() 的匹配资源。
  Link* button_list_[scheduler::kMaxLinkNum] = {};
  // 作为场景列表用于挂载场景，实现场景调度。
  Scene* schedule_match_table_[scheduler::kMaxJumpNum] = {};
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCHEDULER_BASE_H_