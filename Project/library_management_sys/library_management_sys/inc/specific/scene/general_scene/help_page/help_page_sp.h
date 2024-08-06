#pragma once
#include"../../general_scene_sp.h"
#include"../../../../base/page_base.h"
#include"../../../../base/scene_base.h"
namespace library_management_sys {
constexpr char kHelpPageDataSource[] = "res/help_page_data.txt";

class HelpPage : public GeneralScene {
 public:
  HelpPage(Mouse*, Scene*, PageUnitEx*);
  bool prepareScene();
};
}  // namespace library_management_sys
