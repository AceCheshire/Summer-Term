// * License: Apache 2.0
// * File: link_base.h
// * Author: Mai Tianle
// * Date: 2024-08-05
// * Description: Declare class Link.
#include <string>

#include "inc/base/scheduler_base.h"
#ifndef LMS_BASE_LINK_BASE_H_
#define LMS_BASE_LINK_BASE_H_
namespace library_management_sys {
// Link is the abstract of buttons, and we use Link instances
// to connect Scene instances.
// Example:
//    Scheduler test_scheduler;
//    std::wstring test_str;
// 	  unsigned short test_this_scene_serial, test_next_scene_serial;
//    unsigned short test_mode;
//    Link test_link(test_scheduler, test_str, test_this_scene_serial,
//                   test_next_scene_serial, test_mode);
//    test_scheduler.appendLink(test_link);
class Link {
 public:
  // It is a constructor with initialization list.
  Link(Scheduler& attached_scheduler, const std::wstring& symbol_str,
       unsigned short this_scene_serial, unsigned short next_scene_serial,
       unsigned short check_mode);

  // It is an overloaded constructor. Different argument is char*.
  // Argument cannot be NULL, or it will throw a BasicError,
  // to be precise, kNullPointer will be thrown. Usually
  // the error will be caught by itself and it does wcerr.
  Link(Scheduler& attached_scheduler, wchar_t* symbol_str,
       unsigned short this_scene_serial, unsigned short next_scene_serial,
       unsigned short check_mode) throw(...);

  // Its argument is the target button's symbol and current scene serial.
  //
  // Returns true if the request of switching scenes has been sent.
  //
  // This method is usually called when the client only knows target
  // button but not the taarget scene serial number. Example:
  //    constexpr int kTestMaxNumber = 256;
  //    std::wstring test_symbol_string;
  //    unsigned short test_this_scene_serial = 0;
  //    Link test_link_list[kTestMaxNumber];
  //    for (int i = 0; i < kTestMaxNumber; i++)
  //    if (switchSceneRequest(test_symbol_string, test_this_scene_serial))
  //      break;
  bool switchSceneRequest(const std::wstring& request_str,
                          unsigned short this_scene_serial);

  bool getCheckState() const { return check_mode_; }

 protected:
  // Used for message delivery with relevant Scheduler.
  Scheduler* attached_scheduler_;

  // Used to match with the scene name that client requests. empty
  // std::wstring cannot be matched, so it means blank link then.
  std::wstring symbol_str_;

  // Used to figure out different Links.
  unsigned short this_scene_serial_;

  // Used to call Scheduler::generalSwitch() as its argument. Please
  // do not let it be negative, or array index may be out of bounds.
  unsigned short next_scene_serial_;

  // Used to declare the mode of reply if Scene::checkLink()
  // needs to be called. 0 means no checkLink().
  unsigned short check_mode_ = 0;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_LINK_BASE_H_