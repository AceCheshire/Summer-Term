#pragma once
#include"PageConst.h"
#include"SceneConst.h"
#include"GeneralSceneSp.h"
#define LOGIN_PAGE_DATA "LoginPageData.txt"

class LoginPage :public GeneralScene {
public:
	LoginPage(Mouse*, Scene*, PageUnitEx);
	bool PrepareScene();
};
