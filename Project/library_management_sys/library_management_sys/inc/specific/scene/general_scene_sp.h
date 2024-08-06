#pragma once
#include"../../base/link_base.h"
#include"../../base/scene_base.h"
namespace library_management_sys {
class GeneralScene : public Scene {
 public:
  GeneralScene(Mouse*, Scene*, PageUnitEx*);
  void findLink(std::string);
  static void appendLink(Link*);

 protected:
  void waitInput(bool, bool) throw();
  void layoutText() throw();
  void keyTab();
  void keyRestore();
  PageUnitEx* unit_current_ = NULL;
  static Link* button_list_[kMaxLinkNum];
};
}  // namespace library_management_sys