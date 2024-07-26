#pragma once
#include"GeneralSceneSp.h"
#include"PageBase.h"
#include"SceneBase.h"
#define HOME_PAGE_DATA "HomePageData.txt"

class HomePage :public GeneralScene {
public:
	HomePage(Mouse*, Scene*, PageUnitEx);
	bool PrepareScene();
protected:
	void KeyBinding();
private:
	void ActionKeyA();
	void ActionKeyG();
	void ActionKeyH();
	void ActionKeyS();
	void ActionKeyE();
};