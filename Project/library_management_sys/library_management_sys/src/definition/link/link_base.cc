
// * License: Apache 2.0
// * File: link_base.cc
// * Author: Mai Tianle
// * Date: 2024-08-08
// * Description: Define class Link.
#include "inc/base/link_base.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
namespace library_management_sys {
Link::Link(Scheduler& attached_scheduler, const std::wstring& symbol_str,
           unsigned short this_scene_serial, unsigned short next_scene_serial,
           unsigned short check_mode)
    : attached_scheduler_(&attached_scheduler),
      symbol_str_(symbol_str),
      this_scene_serial_(this_scene_serial),
      next_scene_serial_(next_scene_serial),
      check_mode_(check_mode) {}

Link::Link(Scheduler& attached_scheduler, wchar_t* symbol_str,
           unsigned short this_scene_serial, unsigned short next_scene_serial,
           unsigned short check_mode) throw(...) {
  try {
    attached_scheduler_ = &attached_scheduler;
    this_scene_serial_ = this_scene_serial;
    next_scene_serial_ = next_scene_serial;
    check_mode_ = check_mode;
    // Check if the char pointer is NULL. If is NULL, throw
    // kNullPointer and do std::wcerr (red error output).
    if (&symbol_str != NULL)
      symbol_str_ = symbol_str;
    else
      throw BasicError::kNullPointer;
  } catch (BasicError& err_num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED);  // Set red color.
    std::wcout.imbue(std::locale("chs"));
    std::wcout << std::endl;
    std::wcerr << L"ERR: function Link | err_num " << err_num
              << std::endl;  // Print error output.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_WHITE);  // Set default color.
  }
}

bool Link::switchSceneRequest(const std::wstring& request_str,
                              unsigned short this_scene_serial) {
  // Match the std::wstring to find correct next_scene_serial_.
  if (request_str == symbol_str_ && this_scene_serial_ == this_scene_serial) {
    attached_scheduler_->generalSwitch(next_scene_serial_, check_mode_);
    return true;
  }
  // If not match, return false to start next match.
  return false;
}
}  // namespace library_management_sys