#pragma once
#include"LinkConst.h"
#include"SceneConst.h"

class GeneralScene :public Scene {
public:
	GeneralScene(Mouse*, Scene*, PageUnitEx);
	void WaitInput(bool, bool) throw();
	void FindLink(std::string);
	static void AppendLink(Link*);
protected:
	static Link* buttonList[MAX_LINK_NUM];
};