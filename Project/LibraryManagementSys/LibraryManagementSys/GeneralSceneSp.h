#pragma once
#include"LinkBase.h"
#include"SceneBase.h"

class GeneralScene :public Scene {
public:
	GeneralScene(Mouse*, Scene*, PageUnitEx*);
	void FindLink(std::string);
	static void AppendLink(Link*);
protected:
	void WaitInput(bool, bool) throw();
	void LayoutText() throw();
	void KeyTab();
	void KeyRestore();
	PageUnitEx* unitCurrent = NULL;
	static Link* buttonList[MAX_LINK_NUM];
};