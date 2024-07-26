#pragma once
#include"GeneralSceneSp.h"
#include"PageBase.h"
#include"SceneBase.h"
#define LOGIN_PAGE_DATA "LoginPageData.txt"

class LoginPage :public GeneralScene {
public:
	LoginPage(Mouse*, Scene*, PageUnitEx);
	bool PrepareScene();
protected:
	void KeyBinding() {};
};
