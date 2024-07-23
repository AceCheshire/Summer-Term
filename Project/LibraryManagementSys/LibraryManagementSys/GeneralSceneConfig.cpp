#include"GeneralSceneSp.h"
#include"MouseConst.h"
#include"PageConst.h"
#include"SceneConst.h"
#include<conio.h>
#include<iostream>
#pragma warning(disable:4996)

GeneralScene::GeneralScene(Mouse* aattachedMouse, Scene* pprevScene, PageUnitEx ppageUnitListHead)
	:Scene(aattachedMouse, pprevScene, ppageUnitListHead) {
}

void GeneralScene::WaitInput(bool isKeyboardInputOn, bool isMouseInputOn) throw() {
	if (!isKeyboardInputOn && !isMouseInputOn)throw;
	if (kbhit() != 0 && isKeyboardInputOn) {
		int inputKey = _getch();
		if (keyList[inputKey] != NULL) keyList[inputKey]();
	}
	if (!(mouseMsg = (*attachedMouse).HoverAndClick()).empty() && isMouseInputOn) {
		FindLink(mouseMsg);
	}
}

void GeneralScene::FindLink(std::string msg) {
	for (int i = 0; i < MAX_LINK_NUM; i++) {
		if (buttonList[i] != NULL) {
			buttonList[i]->SwitchScene(msg);
		}
	}
}

Link* GeneralScene::buttonList[MAX_LINK_NUM] = {};