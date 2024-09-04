// * 文件：scheduler_base.cc
// * 作者：麦天乐
// * 介绍：定义 Scheduler 类。
#include "inc/base/scheduler_base.h"

#include <cassert>
#include <iostream>
#include <string>

#include "inc/app_const.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
namespace library_management_sys {
Scheduler::Scheduler(unsigned short init_scene) {
  assert(init_scene < scheduler::kMaxJumpNum);
  active_scene_ = init_scene;
  current_user_.clear();
  searching_book_.clear();
  searching_user_.clear();
  shared_task_ = 0;
}

bool Scheduler::generalSwitch(unsigned short scene_number,
                              unsigned short check_mode) {
  if (scene_number < scheduler::kMaxJumpNum) {          // 避免越界
    if (schedule_match_table_[scene_number] != NULL) {  // 避免空指针
      if (!schedule_match_table_[active_scene_]->checkLink(check_mode))
        return false;  // 场景过渡并确认是否切换场景
      system("cls");
      active_scene_ = scene_number;  // 更改调度器当前场景
      is_to_break_ = true;           // 跳出场景重新准备
      return true;
    }
  }
  return false;
}

void Scheduler::generalSchedule() {
  while (!is_to_exit_) {                                   // 场景间循环
    schedule_match_table_[active_scene_]->prepareScene();  // 场景初始化
    while (!is_to_exit_) {                                 // 场景内循环
      if (!is_inputting_info_) {  // 进入非输入文本模式
        waitInput(
            schedule_match_table_[active_scene_]->getMouseInputState(),
            schedule_match_table_[active_scene_]->getKeyboardInputState());
        if (kKeyDown(VK_INSERT)) is_inputting_info_ = true;  // 按键切换模式
      } else {  // 进入输入文本模式
        schedule_match_table_[active_scene_]->inputInfo();
        is_inputting_info_ = false;  // 自动切换模式
      }
      if (is_to_break_) {          // 处理中断
        current_tab_unit_ = NULL;  // 清除选择状态
        is_to_break_ = false;
        break;
      }
    }
  }
}

void Scheduler::appendLink(Link& new_link) {
  int i = 0;
  while (button_list_[i] != NULL) i++;
  assert(i < scheduler::kMaxLinkNum);
  button_list_[i] = &new_link;  // 就近插入
}

void Scheduler::appendScene(Scene& new_scene, unsigned short target_pos) {
  assert(target_pos < scheduler::kMaxJumpNum);        // 防止越界
  assert(schedule_match_table_[target_pos] == NULL);  // 不挤占其他场景
  schedule_match_table_[target_pos] = &new_scene;
}

int Scheduler::findLink(const std::wstring& msg) {
  for (int i = 0; i < scheduler::kMaxLinkNum; i++) {
    if (button_list_[i] != NULL) {  // 遍历非空元素
      int ret = button_list_[i]->stringToSequence(msg, active_scene_);
      if (ret != -1) return ret;
    }
  }
  return -1;
}

void Scheduler::waitInput(bool is_keyboard_input_on,
                          bool is_mouse_input_on) {
  assert(is_keyboard_input_on || is_mouse_input_on);  // 防止死循环
  if (is_keyboard_input_on) {
    if (kKeyDown(VK_TAB)) keyTab();  // 高亮文本选择
    if (kKeyDown(VK_RETURN) && current_tab_unit_ != NULL) {
      int ret = findLink(current_tab_unit_->text_);
      generalSwitch(ret % 1000, ret / 1000);  // 跳转到键盘选择的场景
    }
  }
  // 1) 获得当前场景的场景文本以调用 Mouse::hoverAndClick()
  // 2) 将 hoverAndClick() 的返回值赋给 mouse_msg
  // 3) 检查鼠标输入模式和 mouse_msg 是否有效
  // 4) 为 mouse_msg 匹配链接并尝试跳转
  std::wstring mouse_msg;
  if (((mouse_msg = built_mouse_.hoverAndClick(
            *(schedule_match_table_[active_scene_]->getPageUnitList()))) !=
       mouse::kDefaultReturn) &&
      is_mouse_input_on) {
    int ret = findLink(mouse_msg);
    generalSwitch(ret % 1000, ret / 1000);
  }
}

void Scheduler::keyTab() {
  PageUnit tmp_unit;
  PageUnitEx* tmp_unit_pointer = current_tab_unit_;  // 记录旧选择
  if (current_tab_unit_ == NULL)  // 指针为空时置于场景文本链表头部
    current_tab_unit_ =
        schedule_match_table_[active_scene_]->getPageUnitList()->getNext();
  while (current_tab_unit_->getNext() !=
         NULL) {  // 跳出循环的两种可能：1）到达尾部 2）找到可高亮单元
    current_tab_unit_ = current_tab_unit_->getNext();
    if (current_tab_unit_->can_be_highlighted_) break;
  }
  // 情况一：链表中均非可高亮
  assert(tmp_unit_pointer != NULL ||
         current_tab_unit_->getPageUnit().can_be_highlighted_);
  if (!current_tab_unit_
           ->can_be_highlighted_) {  // 情况二：从链表中部到尾部均非可高亮
    tmp_unit = *tmp_unit_pointer;
    current_tab_unit_ = NULL;
  } else if (tmp_unit_pointer != NULL) {
    if (tmp_unit_pointer->getNext() == NULL) {  // 情况三：正好在链表尾部
      tmp_unit = *current_tab_unit_;
      current_tab_unit_ = NULL;
    } else {  // 情况四：从链表头部或中部向后找到了可高亮页面单元
      Page::pointPaint(*tmp_unit_pointer);
      tmp_unit = Page::highlight(*current_tab_unit_);
    }
  } else {  // 情况五：从空指针向后找到了可高亮单元
    tmp_unit = Page::highlight(*current_tab_unit_);
  }
  Page::pointPaint(tmp_unit);
}
}  // namespace library_management_sys