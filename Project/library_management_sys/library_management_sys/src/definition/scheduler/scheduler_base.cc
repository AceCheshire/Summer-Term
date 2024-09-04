// * �ļ���scheduler_base.cc
// * ���ߣ�������
// * ���ܣ����� Scheduler �ࡣ
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
  if (scene_number < scheduler::kMaxJumpNum) {          // ����Խ��
    if (schedule_match_table_[scene_number] != NULL) {  // �����ָ��
      if (!schedule_match_table_[active_scene_]->checkLink(check_mode))
        return false;  // �������ɲ�ȷ���Ƿ��л�����
      system("cls");
      active_scene_ = scene_number;  // ���ĵ�������ǰ����
      is_to_break_ = true;           // ������������׼��
      return true;
    }
  }
  return false;
}

void Scheduler::generalSchedule() {
  while (!is_to_exit_) {                                   // ������ѭ��
    schedule_match_table_[active_scene_]->prepareScene();  // ������ʼ��
    while (!is_to_exit_) {                                 // ������ѭ��
      if (!is_inputting_info_) {  // ����������ı�ģʽ
        waitInput(
            schedule_match_table_[active_scene_]->getMouseInputState(),
            schedule_match_table_[active_scene_]->getKeyboardInputState());
        if (kKeyDown(VK_INSERT)) is_inputting_info_ = true;  // �����л�ģʽ
      } else {  // ���������ı�ģʽ
        schedule_match_table_[active_scene_]->inputInfo();
        is_inputting_info_ = false;  // �Զ��л�ģʽ
      }
      if (is_to_break_) {          // �����ж�
        current_tab_unit_ = NULL;  // ���ѡ��״̬
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
  button_list_[i] = &new_link;  // �ͽ�����
}

void Scheduler::appendScene(Scene& new_scene, unsigned short target_pos) {
  assert(target_pos < scheduler::kMaxJumpNum);        // ��ֹԽ��
  assert(schedule_match_table_[target_pos] == NULL);  // ����ռ��������
  schedule_match_table_[target_pos] = &new_scene;
}

int Scheduler::findLink(const std::wstring& msg) {
  for (int i = 0; i < scheduler::kMaxLinkNum; i++) {
    if (button_list_[i] != NULL) {  // �����ǿ�Ԫ��
      int ret = button_list_[i]->stringToSequence(msg, active_scene_);
      if (ret != -1) return ret;
    }
  }
  return -1;
}

void Scheduler::waitInput(bool is_keyboard_input_on,
                          bool is_mouse_input_on) {
  assert(is_keyboard_input_on || is_mouse_input_on);  // ��ֹ��ѭ��
  if (is_keyboard_input_on) {
    if (kKeyDown(VK_TAB)) keyTab();  // �����ı�ѡ��
    if (kKeyDown(VK_RETURN) && current_tab_unit_ != NULL) {
      int ret = findLink(current_tab_unit_->text_);
      generalSwitch(ret % 1000, ret / 1000);  // ��ת������ѡ��ĳ���
    }
  }
  // 1) ��õ�ǰ�����ĳ����ı��Ե��� Mouse::hoverAndClick()
  // 2) �� hoverAndClick() �ķ���ֵ���� mouse_msg
  // 3) ����������ģʽ�� mouse_msg �Ƿ���Ч
  // 4) Ϊ mouse_msg ƥ�����Ӳ�������ת
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
  PageUnitEx* tmp_unit_pointer = current_tab_unit_;  // ��¼��ѡ��
  if (current_tab_unit_ == NULL)  // ָ��Ϊ��ʱ���ڳ����ı�����ͷ��
    current_tab_unit_ =
        schedule_match_table_[active_scene_]->getPageUnitList()->getNext();
  while (current_tab_unit_->getNext() !=
         NULL) {  // ����ѭ�������ֿ��ܣ�1������β�� 2���ҵ��ɸ�����Ԫ
    current_tab_unit_ = current_tab_unit_->getNext();
    if (current_tab_unit_->can_be_highlighted_) break;
  }
  // ���һ�������о��ǿɸ���
  assert(tmp_unit_pointer != NULL ||
         current_tab_unit_->getPageUnit().can_be_highlighted_);
  if (!current_tab_unit_
           ->can_be_highlighted_) {  // ��������������в���β�����ǿɸ���
    tmp_unit = *tmp_unit_pointer;
    current_tab_unit_ = NULL;
  } else if (tmp_unit_pointer != NULL) {
    if (tmp_unit_pointer->getNext() == NULL) {  // �����������������β��
      tmp_unit = *current_tab_unit_;
      current_tab_unit_ = NULL;
    } else {  // ����ģ�������ͷ�����в�����ҵ��˿ɸ���ҳ�浥Ԫ
      Page::pointPaint(*tmp_unit_pointer);
      tmp_unit = Page::highlight(*current_tab_unit_);
    }
  } else {  // ����壺�ӿ�ָ������ҵ��˿ɸ�����Ԫ
    tmp_unit = Page::highlight(*current_tab_unit_);
  }
  Page::pointPaint(tmp_unit);
}
}  // namespace library_management_sys