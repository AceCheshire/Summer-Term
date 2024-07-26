#pragma once
#include"GeneralSceneSp.h"
#include"PageBase.h"
#include"SceneBase.h"
#define HELP_PAGE_DATA "HelpPageData.txt"

class HelpPage :public GeneralScene {
public:
	HelpPage(Mouse*, Scene*, PageUnitEx);
	bool PrepareScene();
protected:
	void KeyBinding() {};
};
