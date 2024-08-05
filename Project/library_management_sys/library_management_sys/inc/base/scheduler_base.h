#include <iostream>
#ifndef LMS_BASE_SCHEDULER_BASE_H_
#define LMS_BASE_SCHEDULER_BASE_H_
namespace library_management_sys {
class Scheduler {
 public:
  void generalSchedule(int i){}
 protected:
  static std::string schrdule_check_table_[256];
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCHEDULER_BASE_H_