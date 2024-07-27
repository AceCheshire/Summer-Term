#include"ErrorBase.h"
#include"SceneBase.h"
#include<iostream>

Scene::Scene(Mouse* aattachedMouse,Scene* pprevScene,PageUnitEx* ppageUnitListHead) 
	:attachedMouse(aattachedMouse),prevScene(pprevScene),pageUnitListHead(ppageUnitListHead){
}