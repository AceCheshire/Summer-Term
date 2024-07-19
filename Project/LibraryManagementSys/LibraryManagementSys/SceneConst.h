#pragma once
#include"PageConst.h"
#include"MouseConst.h"

class Scene {
public:
	virtual bool PrepareScene() = 0;
private:
	Mouse* attachedMouse;
	Scene* prevScene;
	std::string* buttonList;
	int buttonListCount;
	PageUnitEx pageUnitListHead;
};