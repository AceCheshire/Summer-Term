#pragma once
#include"../../general_scene_sp.h"
#include"../../../../base/page_base.h"
#include"../../../../base/scene_base.h"
namespace library_management_sys {
constexpr char kHomePageDataSource[] = "res/home_page_data.txt";

class HomePage : public GeneralScene {
 public:
  HomePage(Mouse*, Scene*, PageUnitEx*);
  bool prepareScene();
};
}  // namespace library_management_sys