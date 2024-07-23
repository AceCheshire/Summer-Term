#include"LinkConst.h"
#include"PageConst.h"
#include"SceneConst.h"
#include<conio.h>
#include<iostream>

Scene::Scene(Mouse* aattachedMouse,Scene* pprevScene,PageUnitEx ppageUnitListHead) 
	:attachedMouse(aattachedMouse),prevScene(pprevScene),pageUnitListHead(ppageUnitListHead){
}

void Scene::LayoutText() throw() {
	Page tmpPage;
	PageUnitEx* tmpPageUnitPointer = &pageUnitListHead;
	try {
		if (attachedMouse->GetTimes() >= 2) {
			system("cls");
			attachedMouse->ResetTimes();
		}
	}
	catch (...) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << std::endl;
		std::cerr << "ERR: class Page | function CleanSceen | errnum " << CLS_ERROR << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}
	if (tmpPageUnitPointer == NULL)throw;
	while (tmpPageUnitPointer != NULL) {
		tmpPage.PointPaint(tmpPageUnitPointer->GetPageUnit());
		tmpPageUnitPointer = tmpPageUnitPointer->GetNext();
	}
}

void (*Scene::keyList[MAX_KEY_NUM])() = {};