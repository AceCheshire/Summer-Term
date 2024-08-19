// * License: Apache 2.0
// * File: scheduler_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define class Scheduler.
#include "inc/base/scheduler_base.h"

#include <cassert>
#include <iostream>
#include <string>

#include "inc/base/error_base.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
namespace library_management_sys {
Scheduler::Scheduler(Mouse& attached_mouse, unsigned short init_scene)
    : attached_mouse_(&attached_mouse) {
  assert(init_scene < scheduler::kMaxJumpNum);
  active_scene_ = init_scene;
}

bool Scheduler::generalSwitch(unsigned short scene_serial,
                              unsigned short check_mode) {
  // Avoid out of bounds
  if (scene_serial < scheduler::kMaxJumpNum) {
    // Avoid null pointer
    if (schedule_match_table_[scene_serial] != NULL) {
      // Figure whether checkLink() is needed and carry out
      if (!schedule_match_table_[active_scene_]->checkLink(check_mode))
        return false;
      // Switch scene by change active_scene_
      system("cls");
      active_scene_ = scene_serial;
      is_to_break_ = true;  // Make a break request to re-prepare
      return true;
    }
  }
  return false;
}

void Scheduler::generalSchedule() {
  schedule_match_table_[active_scene_]->prepareScene();  // Start a scene
  while (true) {
    if (!is_inputting_info_) {
      // Under not-inputting-text mode
      waitInput(schedule_match_table_[active_scene_]->getMouseInputState(),
                schedule_match_table_[active_scene_]->getKeyboardInputState());
      if (kKeyDown(VK_INSERT)) is_inputting_info_ = true;  // Mode Switch

    } else {
      // Under inputting-text mode
      schedule_match_table_[active_scene_]->inputInfo();
      is_inputting_info_ = false;  // Rollback to not-inputting-text mode
    }
    // If receive request, break once
    if (is_to_break_) {
      current_tab_unit_ = NULL;  // Clear previous choice
      is_to_break_ = false;
      break;
    }
  }
}

void Scheduler::appendLink(Link& new_link) {
  int i = 0;
  while (button_list_[i] != NULL) i++;
  assert(i < scheduler::kMaxLinkNum);
  button_list_[i] = &new_link;  // Append the link to the nearest position.
}

void Scheduler::appendScene(Scene& new_scene, int target_pos) {
  assert(target_pos < scheduler::kMaxJumpNum);        // Avoid out of bounds.
  assert(schedule_match_table_[target_pos] == NULL);  // Forced condition
  schedule_match_table_[target_pos] = &new_scene;     // Append the scene
}

bool Scheduler::findLink(const std::wstring& msg) {
  // Search non-null elements of button_list_
  for (int i = 0; i < scheduler::kMaxLinkNum; i++) {
    if (button_list_[i] != NULL) {
      // Return true if it exists matched Link.
      if (button_list_[i]->switchSceneRequest(msg, active_scene_)) return true;
    }
  }
  return false;
}

void Scheduler::waitInput(bool is_keyboard_input_on,
                          bool is_mouse_input_on) throw(...) {
  // No valid input means application cannot interact with client.
  assert(is_keyboard_input_on || is_mouse_input_on);
  if (is_keyboard_input_on) {
    if (kKeyDown(VK_TAB)) keyTab();  // Switch highlighted text
    if (kKeyDown(VK_RETURN) && current_tab_unit_ != NULL)
      findLink(current_tab_unit_->getPageUnit()
                   .text);  // Try to switch to target scene of highlighted text
  }
  // 1) Get member pageunit_list_head_ of active scene as the
  //    parameter of Mouse::hoverAndClick()
  // 2) Assign mouse_msg with the return value of hoverAndClick()
  // 3) Check whether mouse_msg is a valid click return and the input state_
  // 4) Match Links for mouse_msg
  std::wstring mouse_msg;
  if (((mouse_msg = attached_mouse_->hoverAndClick(
             *(schedule_match_table_[active_scene_]->getPageUnitList())))
            .length()) &&
      is_mouse_input_on) {
    findLink(mouse_msg);
  }
}

void Scheduler::keyTab() {
  Page tmp_page;      // Used to use Page interface
  PageUnit tmp_unit;  // Used to record PageUnit info
  PageUnitEx* tmp_unit_pointer = current_tab_unit_;// Used to record the previous
  // Put current_tab_unit_ on the beginning of the linked list.
  if (current_tab_unit_ == NULL)
    current_tab_unit_ =
        schedule_match_table_[active_scene_]->getPageUnitList()->getNext();
  // Iterate until the end or current_tab_unit_ is proper
  while (current_tab_unit_->getNext() != NULL) {
    current_tab_unit_ = current_tab_unit_->getNext();
    if (current_tab_unit_->getPageUnit().can_be_highlighted) break;
  }
  // Case 1: no proper ones in the linked list
  assert(tmp_unit_pointer != NULL ||
         current_tab_unit_->getPageUnit().can_be_highlighted);
  // Case 2: from middle position to the end there are no proper ones 
  if (!current_tab_unit_->getPageUnit().can_be_highlighted) {
    tmp_unit = tmp_unit_pointer->getPageUnit();
    current_tab_unit_ = NULL;
  } else if (tmp_unit_pointer != NULL) {
    if (tmp_unit_pointer->getNext() == NULL) {
      // Case 3: right at the end of the linked list
      tmp_unit = current_tab_unit_->getPageUnit();
      current_tab_unit_ = NULL;
    } else {
      // Case 4: from the middle position
      tmp_page.pointPaint(tmp_unit_pointer->getPageUnit());
      tmp_unit = tmp_page.highlight(current_tab_unit_->getPageUnit());
    }
  } else {
    // Case 5: from the beginning to the middle position or the end
    tmp_unit = tmp_page.highlight(current_tab_unit_->getPageUnit());
  }
  tmp_page.pointPaint(tmp_unit);  // Send the PageUnit to Page and paint
}
}  // namespace library_management_sys