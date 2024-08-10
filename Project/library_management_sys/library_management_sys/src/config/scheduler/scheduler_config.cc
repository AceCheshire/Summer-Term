// * License: Apache 2.0
// * File: scheduler_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define class Scheduler.
#include "inc/base/scheduler_base.h"

#include <cassert>
#include <iostream>

#include "inc/base/error_base.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
namespace library_management_sys {
Scheduler::Scheduler(Mouse& attached_mouse, Scene& init_scene)
    : attached_mouse_(&attached_mouse), active_scene_(&init_scene) {}

bool Scheduler::generalSwitch(unsigned short scene_serial) {
  // Avoid out of bounds
  if (scene_serial < kMaxJumpNum) {
    // Avoid heap pointer
    if (schedule_match_table_[scene_serial] != NULL) {
      // Switch scene by change active_scene_ attribute
      active_scene_ = schedule_match_table_[scene_serial];
      is_to_break = true;  // Make a break request to re-prepare
      return true;
    }
  }
  return false;
}

void Scheduler::generalSchedule() {
  active_scene_->prepareScene();  // Start a scene
  while (true) {
    if (!is_inputting_info_) {
      // Under not-inputting-text mode
      waitInput(active_scene_->getMouseInputState(),
                active_scene_->getKeyboardInputState());
      if (KEY_DOWN(VK_INSERT)) is_inputting_info_ = true;  // Mode Switch

    } else {
      // Under inputting-text mode
      active_scene_->inputInfo();
      is_inputting_info_ = false;  // Rollback to not-inputting-text mode
    }
    // If receive request, break once
    if (is_to_break) {
      is_to_break = false;
      break;
    }
  }
}

void Scheduler::appendLink(Link& new_link) {
  int i = 0;
  while (button_list_[i] != NULL) i++;
  assert(i < kMaxLinkNum);
  button_list_[i] = &new_link;  // Append the link to the nearest position.
}

void Scheduler::appendScene(Scene& new_scene, int target_pos) {
  assert(target_pos < kMaxJumpNum);                   // Avoid out of bounds.
  assert(schedule_match_table_[target_pos] == NULL);  // Forced condition
  schedule_match_table_[target_pos] = &new_scene;     // Append the scene
}

bool Scheduler::findLink(std::string msg) {
  // Search non-null elements of button_list_
  for (int i = 0; i < kMaxLinkNum; i++) {
    if (button_list_[i] != NULL) {
      // Return true if it exists matched Link.
      if (button_list_[i]->switchSceneRequest(msg)) return true;
    }
  }
  return false;
}

void Scheduler::waitInput(bool is_keyboard_input_on,
                          bool is_mouse_input_on) throw() {
  // No valid input means application cannot interact with client.
  assert(is_keyboard_input_on || is_mouse_input_on);
  if (is_keyboard_input_on) {
    if (KEY_DOWN(VK_TAB)) keyTab();  // Switch highlighted text
    if (KEY_DOWN(VK_RETURN) && current_tab_unit_ != NULL)
      findLink(current_tab_unit_->getPageUnit()
                   .text);  // Try to switch to target scene of highlighted text
  }
  // 1) Get member pageunit_list_head_ of active scene as the
  //    parameter of Mouse::hoverAndClick()
  // 2) Assign mouse_msg with the return value of hoverAndClick()
  // 3) Check whether mouse_msg is a valid click return and the input state
  // 4) Match Links for mouse_msg
  std::string mouse_msg;
  if (!((mouse_msg = attached_mouse_->hoverAndClick(
             *(active_scene_->getPageUnitList())))
            .empty()) &&
      is_mouse_input_on) {
    findLink(mouse_msg);
  }
}

void Scheduler::keyTab() {
  Page tmp_page;      // Used to use Page interface
  PageUnit tmp_unit;  // Used to record PageUnit info
  // Case 1: the first time Tab is pressed
  if (current_tab_unit_ == NULL) {
    current_tab_unit_ =
        active_scene_->getPageUnitList()->getNext();  // Move pointer
    tmp_unit = current_tab_unit_->getPageUnit();      // PageUnit copy
    tmp_unit.color = BACKGROUND_INTENSITY;            // Highlight text
  } else {
    tmp_page.pointPaint(current_tab_unit_->getPageUnit());  // Move pointer
    // Case 2: the end of linked list, let highlight fade
    if (current_tab_unit_->getNext() == NULL) {
      // Use re-painting the PageUnit to cancel highlight
      tmp_unit = current_tab_unit_->getPageUnit();
      current_tab_unit_ = NULL;  // Reset the pointer for next loop
    } else {
      // Case 3: not the end or the beginning
      current_tab_unit_ = current_tab_unit_->getNext();  // Iterate
      tmp_unit = current_tab_unit_->getPageUnit();       // PageUnit copy
      tmp_unit.color = BACKGROUND_INTENSITY;             // Highlight text
    }
  }
  tmp_page.pointPaint(tmp_unit);  // Send the PageUnit to Page and paint
}
}  // namespace library_management_sys