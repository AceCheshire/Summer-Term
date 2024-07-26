#pragma once
#include"MouseBase.h"
#include"PageBase.h"
#define MAX_KEY_NUM 256
#define MAX_LINK_NUM 64

class Scene {
public:
	Scene(Mouse*, Scene*, PageUnitEx);
	virtual bool PrepareScene() = 0;
protected:
	void LayoutText() throw();
	Mouse* attachedMouse;
	std::string mouseMsg;
	Scene* prevScene;
	PageUnitEx pageUnitListHead;
};