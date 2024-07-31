#pragma once
#include"link_base.h"
#include"scene_base.h"

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