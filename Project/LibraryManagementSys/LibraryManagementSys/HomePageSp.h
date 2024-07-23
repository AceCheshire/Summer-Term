#pragma once
#include"PageConst.h"
#include"SceneConst.h"
#include"GeneralSceneSp.h"
#define HOME_PAGE_DATA "HomePageData.txt"

class HomePage :public GeneralScene {
public:
	HomePage(Mouse*, Scene*, PageUnitEx);
	bool PrepareScene();
};