// * License: Apache 2.0
// * File: link_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-08
// * Description: Define class Link.
#include "inc/base/link_base.h"

#include <iostream>
#include <windows.h>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
namespace library_management_sys {
Link::Link(Scheduler& attached_scheduler, std::string symbol_str,
           unsigned short next_scene_serial)
    : attached_scheduler_(&attached_scheduler),
      symbol_str_(symbol_str),
      next_scene_serial_(next_scene_serial) {}

Link::Link(Scheduler& attached_scheduler, char* symbol_str,
           unsigned short next_scene_serial) throw() {
  try {
    attached_scheduler_ = &attached_scheduler;
    next_scene_serial_ = next_scene_serial;
    // Check if the char pointer is NULL. If is NULL, throw
    // kHeapPointerError and do std::cerr (red error output).
    if (&symbol_str != NULL)
      symbol_str_ = symbol_str;
    else
      throw kHeapPointerError;
  } catch (BasicError& err_num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED);  // Set red color.
    std::cout << std::endl;
    std::cerr << "ERR: function Link | err_num " << err_num
              << std::endl;  // Print error output.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_WHITE);  // Set default color.
  }
}

bool Link::switchSceneRequest(std::string request_str) {
  // Match the std::string to find correct next_scene_serial_.
  if (request_str == symbol_str_) {
    system("cls");  // Clean screen first, no matter whether the generalSwitch()
                    // is allowed by Scheduler.
    attached_scheduler_->generalSwitch(next_scene_serial_);
    return true;
  }
  // If not match, return false to start next match.
  return false;
}
}  // namespace library_management_sys