// * License: Apache 2.0
// * File: link_base.h
// * Author: Mai Tianle
// * Date: 2024-08-05
// * Description: Declare class Link.
#include <iostream>

#include "inc/base/scheduler_base.h"
#ifndef LMS_BASE_LINK_BASE_H_
#define LMS_BASE_LINK_BASE_H_
namespace library_management_sys {
// Link is the abstract of buttons, and we use Link instances
// to connect Scene instances.
// Example:
//    Scheduler test_scheduler;
//    std::string test_str;
// 	  unsigned short test_next_scene_serial;
//    Link test_link(test_scheduler, test_str, test_next_scene_serial);
class Link {
 public:
  // It is a constructor with initialization list.
  Link(Scheduler& attached_scheduler, std::string symbol_str,
       unsigned short next_scene_serial);
  // It is an overloaded constructor. Different argument is char*.
  // Argument cannot be NULL, or it will throw a BasicError,
  // to be precise, kHeapPointerError will be thrown. Usually
  // the error will be caught by itself and it does cerr.
  Link(Scheduler& attached_scheduler, char* symbol_str,
       unsigned short next_scene_serial) throw();
  // Its argument is the name of scene which you wanna turn to.
  //
  // Returns true if the request of switching scenes has been sent.
  //
  // The client has no need to delete it.
  //
  // This method is usually called when the client only knows the
  // name but not the relevant serial number. Example:
  //    constexpr int kTestMaxNumber = 256;
  //    std::string test_scene_name;
  //    Link test_link_list[kTestMaxNumber];
  //    for (int i = 0; i < kTestMaxNumber; i++)
  //    if (switchSceneRequest(test_scene_name)) break;
  bool switchSceneRequest(std::string request_str);

 protected:
  // Used for message delivery with relevant Scheduler.
  Scheduler* attached_scheduler_;
  // Used to match with the scene name that client requests. empty
  // std::string cannot be matched, so it means blank link then.
  std::string symbol_str_;
  // Used to call Scheduler::generalSwitch() as its argument. Please
  // do not let it be negative, or array index may be out of bounds.
  unsigned short next_scene_serial_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_LINK_BASE_H_