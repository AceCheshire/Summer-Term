#include"HomePageSp.h"
#include<iostream>
#include<windows.h>
using namespace std;

HomePage::HomePage(Mouse* aattachedMouse, Scene* pprevScene, PageUnitEx ppageUnitListHead)
	:GeneralScene(aattachedMouse, pprevScene, ppageUnitListHead) {
}

bool HomePage::PrepareScene() {
	try {
		while (true) {
			LayoutText();
			WaitInput(true, true);
		}
	}
	catch (int errnum) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: class HomePage | function PrepareScene | errnum " << errnum << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		return false;
	}
	return true;
}

void HomePage::KeyBinding() {

}

void HomePage::ActionKeyA() {

}

void HomePage::ActionKeyG() {

}

void HomePage::ActionKeyH() {

}

void HomePage::ActionKeyS() {

}

void HomePage::ActionKeyE() {

}