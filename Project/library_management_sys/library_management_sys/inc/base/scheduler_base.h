// * License: Apache 2.0
// * File: scheduler_base.h
// * Author: Mai Tianle
// * Date: 2024-08-07
// * Description: Declare class Scheduler.
#include <iostream>

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
//
class Scheduler {
 public:
  bool generalSwitch(unsigned short scene_serial);
  void generalSchedule();

 protected:
  void findLink(std::string);
  static void appendLink(Link*);
  Scene* schedule_match_table_[kMaxJumpNum];
  Link* button_list_[kMaxLinkNum];
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCHEDULER_BASE_H_