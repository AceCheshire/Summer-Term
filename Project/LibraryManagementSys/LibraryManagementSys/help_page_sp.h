#pragma once
#include"general_scene_sp.h"
#include"page_base.h"
#include"scene_base.h"
constexpr char kHelpPageDataSource[19] = "help_page_data.txt";

class HelpPage :public GeneralScene {
public:
	HelpPage(Mouse*, Scene*, PageUnitEx*);
	bool prepareScene();
};
