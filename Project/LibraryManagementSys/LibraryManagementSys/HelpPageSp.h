#pragma once
#include"PageConst.h"
#include"SceneConst.h"
#include"GeneralSceneSp.h"
#define HELP_PAGE_DATA "HelpPageData.txt"

class HelpPage :public GeneralScene {
public:
	HelpPage(Mouse*, Scene*, PageUnitEx);
	bool PrepareScene();
};
