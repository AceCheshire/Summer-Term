#pragma once
#include"general_scene_sp.h"
#include"page_base.h"
#include"scene_base.h"
constexpr char kHomePageDataSource[] = "home_page_data.txt";

class HomePage : public GeneralScene {
 public:
  HomePage(Mouse*, Scene*, PageUnitEx*);
  bool prepareScene();
};