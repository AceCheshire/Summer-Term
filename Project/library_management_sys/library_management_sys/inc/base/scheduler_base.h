// * License: Apache 2.0
// * File: scheduler_base.h
// * Author: Mai Tianle
// * Date: 2024-08-07
// * Description: Declare class Scheduler.
#include <iostream>

#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_BASE_SCHEDULER_BASE_H_
#define LMS_BASE_SCHEDULER_BASE_H_
namespace library_management_sys {
class Link;
// It means how many scenes can be jumped to by Scheduler.
constexpr int kMaxJumpNum = 64;
// It means how many keys on keyboard are allowed to
// define interactive operations in one scene.
constexpr int kMaxKeyNum = 256;
// It means how many std::strings appear on one page
// can be Link.
constexpr int kMaxLinkNum = 64;

// Coordinate different scenes like finite - state machine.
// Example:
//    Scheduler test_scheduler;
class Scheduler {
 public:
  // Constructor. The second argument should be the scene client wanna display
  // first.
  Scheduler(Mouse& attached_mouse, Scene& init_scene);
  // Used to change member active_scene_ in running time.
  // Returns true if active_scene_ is changed and the break request is sent.
  bool generalSwitch(unsigned short scene_serial);
  // Main controller of the application. Example:
  //    Scheduler test_scheduler(test_mouse, test_init_scene);
  //    while (true) test_scheduler.generalSchedule();
  void generalSchedule();
  // Maintains member button_list_. If it is to be out of bounds, the program
  // will run abort(). Usually called before generalSchedule();
  // Example:
  //    test_scheduler.appendLink(test_link);
  //    while (true) test_scheduler.generalSchedule();
  void appendLink(Link& new_link);
  // Maintains member schedule_match_table_. If its Argument crushes or is to be
  // out of bounds, the program will run abort(). Usually called before
  // generalSchedule(); Example:
  //    test_scheduler.appendScene(test_scene, 0);
  //    Link test_link(test_scheduler, "test_text", 0);
  void appendScene(Scene& new_scene, int target_pos);

 protected:
  // Matches the argument with button_list_. If matched, sent a request
  // from the Link to switch scene.
  bool findLink(std::string msg);
  // Answers to keyboard and mouse input. Arguments are input states (mostly true)
  // Pay attention that keyboard input may be overridden by mouse input.
  // Example:
  //    while (true) waitInput(true, true);
  void waitInput(bool is_keyboard_input_on, bool is_mouse_input_on) throw();
  // Tab can be a key to keep choosing some texts. Its order is:
  // non -> 1st in page_unit_list_head -> 2nd -> ... -> the last -> non -> ...
  // Example:
  //    bool test_is_keyboard_input_on = true;
  //    if (test_is_keyboard_input_on) {
  //      if (KEY_DOWN(VK_TAB)) keyTab();
  //    }
  void keyTab();
  // Used to bind Mouse instance as input interface.
  Mouse* attached_mouse_;
  // Used to realize scene polymorphism.
  Scene* active_scene_;
  // Used to record tab-chosen text position.
  PageUnitEx* current_tab_unit_ = NULL;
  // Used to record the input state, which can be divided into
  // inputting-text mode and not-inputting-text mode.
  bool is_inputting_info_ = false;
  // Used to record break request. Usually reset to false when
  // break is confirmed to be carried out.
  bool is_to_break = false;
  // Used to record Links for findLink() as matching source.
  Link* button_list_[kMaxLinkNum] = {};
  // Used as scene list to realize polymorphism.
  Scene* schedule_match_table_[kMaxJumpNum] = {};
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCHEDULER_BASE_H_