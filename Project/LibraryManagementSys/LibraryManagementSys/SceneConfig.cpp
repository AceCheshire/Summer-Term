#include"ErrorBase.h"
#include"SceneBase.h"
#include<iostream>

Scene::Scene(Mouse* aattachedMouse,Scene* pprevScene,PageUnitEx ppageUnitListHead) 
	:attachedMouse(aattachedMouse),prevScene(pprevScene),pageUnitListHead(ppageUnitListHead){
}

void Scene::LayoutText() throw() {
	Page tmpPage;
	PageUnitEx* tmpPageUnitPointer = &pageUnitListHead;
	if (tmpPageUnitPointer == NULL)throw HEAP_POINTER_ERROR;
	while (tmpPageUnitPointer != NULL) {
		tmpPage.PointPaint(tmpPageUnitPointer->GetPageUnit());
		tmpPageUnitPointer = tmpPageUnitPointer->GetNext();
	}
}