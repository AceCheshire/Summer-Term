#include"ErrorBase.h"
#include"GeneralSceneSp.h"
#include<conio.h>
#include<iostream>
#pragma warning(disable:4996)

GeneralScene::GeneralScene(Mouse* aattachedMouse, Scene* pprevScene, PageUnitEx ppageUnitListHead)
	:Scene(aattachedMouse, pprevScene, ppageUnitListHead) {
}

void GeneralScene::WaitInput(bool isKeyboardInputOn, bool isMouseInputOn) throw() {
	if (!isKeyboardInputOn && !isMouseInputOn)throw ENDLESS_LOOP_ERROR;
	if (kbhit() != 0 && isKeyboardInputOn) {
		int inputKey = _getch();
		if (keyList[inputKey] != NULL) keyList[inputKey]();
	}
	if (!((mouseMsg = (*attachedMouse).HoverAndClick(&pageUnitListHead)).empty()) && isMouseInputOn) {
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

void GeneralScene::AppendLink(Link* newLink) {
	int i = 0;
	while (buttonList[i] != NULL)i++;
	buttonList[i] = newLink;
}

Link* GeneralScene::buttonList[MAX_LINK_NUM] = {};
void (*GeneralScene::keyList[MAX_KEY_NUM])() = {};