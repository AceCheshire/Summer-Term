#pragma once
#include"LinkBase.h"
#include"SceneBase.h"

class GeneralScene :public Scene {
public:
	GeneralScene(Mouse*, Scene*, PageUnitEx);
	void WaitInput(bool, bool) throw();
	void FindLink(std::string);
	static void AppendLink(Link*);
protected:
	virtual void KeyBinding() = 0;
	static void(*keyList[MAX_KEY_NUM])();
	static Link* buttonList[MAX_LINK_NUM];
};