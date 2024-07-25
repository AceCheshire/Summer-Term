#include"LoginPageSp.h"
#include"SceneConst.h"
#include<iostream>
using namespace std;

LoginPage::LoginPage(Mouse* aattachedMouse, Scene* pprevScene, PageUnitEx ppageUnitListHead)
	:GeneralScene(aattachedMouse, pprevScene, ppageUnitListHead) {
}

bool LoginPage::PrepareScene() {
	int errnum = ENDLESS_LOOP_ERROR;
	try {
		while (true) {
			LayoutText();
			WaitInput(true, false);
		}
	}
	catch (...) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: class LoginPage | function PrepareScene | errnum " << errnum << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		return false;
	}
	return true;
}