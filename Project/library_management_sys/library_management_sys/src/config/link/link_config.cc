#include"../../../inc/base/link_base.h"
#include"../../../inc/base/error_base.h"
#include<iostream>
#include<windows.h>
using namespace std;
namespace library_management_sys {
Link::Link(Scheduler& attached_scheduler, std::string symbol_str,
           unsigned short next_scene_serial)
    : attached_scheduler_(&attached_scheduler),
      symbol_str_(symbol_str),
      next_scene_serial_(next_scene_serial) {}

Link::Link(Scheduler& attached_scheduler, char* symbol_str,
           unsigned short next_scene_serial) throw(...) {
  try {
    attached_scheduler_ = &attached_scheduler;
    next_scene_serial_ = next_scene_serial;
    if (symbol_str != NULL)
      symbol_str_ = symbol_str;
    else
      throw kHeapPointerError;
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: function Link | err_num " << err_num << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
  }
}

bool Link::switchSceneRequest(std::string request_str) {
  if (request_str == symbol_str_) {
    system("cls");
    attached_scheduler_->generalSwitch(next_scene_serial_);
    return true;
  }
  return false;
}
}  // namespace library_management_sys