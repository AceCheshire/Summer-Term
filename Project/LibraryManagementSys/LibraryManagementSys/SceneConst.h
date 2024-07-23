#pragma once
#include"MouseConst.h"
#include"PageConst.h"
#define MAX_KEY_NUM 256
#define MAX_LINK_NUM 64
#define ENDLESS_LOOP_ERROR 4

class Scene {
public:
	Scene(Mouse*, Scene*, PageUnitEx);
	virtual bool PrepareScene() = 0;
protected:
	void LayoutText() throw();
	Mouse* attachedMouse;
	std::string mouseMsg;
	Scene* prevScene;
	static void(*keyList[MAX_KEY_NUM])();
	PageUnitEx pageUnitListHead;
};