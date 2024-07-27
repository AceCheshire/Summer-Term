#include"ErrorBase.h"
#include"GeneralSceneSp.h"
#include<conio.h>
#include<iostream>
#pragma warning(disable:4996)

GeneralScene::GeneralScene(Mouse* aattachedMouse, Scene* pprevScene, PageUnitEx* ppageUnitListHead)
	:Scene(aattachedMouse, pprevScene, ppageUnitListHead) {
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

void GeneralScene::LayoutText() throw() {
	Page tmpPage;
	PageUnitEx* tmpPageUnitPointer = pageUnitListHead;
	if (tmpPageUnitPointer == NULL)throw HEAP_POINTER_ERROR;
	while (tmpPageUnitPointer != NULL) {
		tmpPage.PointPaint(tmpPageUnitPointer->GetPageUnit());
		tmpPageUnitPointer = tmpPageUnitPointer->GetNext();
	}
	KeyRestore();
}

void GeneralScene::WaitInput(bool isKeyboardInputOn, bool isMouseInputOn) throw() {
	if (!isKeyboardInputOn && !isMouseInputOn)throw ENDLESS_LOOP_ERROR;
	if (isKeyboardInputOn) {
		if (KEY_DOWN(VK_TAB))KeyTab();
		if (KEY_DOWN(VK_RETURN) && unitCurrent != NULL)FindLink(unitCurrent->GetPageUnit().text);
	}
	if (!((mouseMsg = (*attachedMouse).HoverAndClick(pageUnitListHead)).empty()) && isMouseInputOn) {
		FindLink(mouseMsg);
	}
}

void GeneralScene::KeyTab() {
	Page tmpPage;
	PageUnit tmpUnit;
	if (unitCurrent == NULL) {
		unitCurrent = pageUnitListHead->GetNext();
		tmpUnit = unitCurrent->GetPageUnit();
		tmpUnit.color = BACKGROUND_INTENSITY;
	}
	else {
		tmpPage.PointPaint(unitCurrent->GetPageUnit());
		if (unitCurrent->GetNext() == NULL) {
			tmpUnit = unitCurrent->GetPageUnit();
			unitCurrent = NULL;
		}
		else {
			unitCurrent = unitCurrent->GetNext();
			tmpUnit = unitCurrent->GetPageUnit();
			tmpUnit.color = BACKGROUND_INTENSITY;
		}
	}
	tmpPage.PointPaint(tmpUnit);
}

void GeneralScene::KeyRestore() {
	Page tmpPage;
	PageUnit tmpUnit;
	if (unitCurrent != NULL) {
		tmpUnit = unitCurrent->GetPageUnit();
		tmpUnit.color = BACKGROUND_INTENSITY;
		tmpPage.PointPaint(tmpUnit);
	}
}

Link* GeneralScene::buttonList[MAX_LINK_NUM] = {};