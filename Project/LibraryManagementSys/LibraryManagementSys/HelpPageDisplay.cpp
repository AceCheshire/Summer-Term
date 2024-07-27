#include"HelpPageSp.h"
#include<iostream>
#include<windows.h>
using namespace std;

HelpPage::HelpPage(Mouse* aattachedMouse, Scene* pprevScene, PageUnitEx* ppageUnitListHead)
	:GeneralScene(aattachedMouse, pprevScene, ppageUnitListHead) {
}

bool HelpPage::PrepareScene() {
	try {
		while (true) {
			LayoutText();
			WaitInput(true, true);
		}
	}
	catch (int errnum) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: class HelpPage | function PrepareScene | errnum " << errnum << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
		return false;
	}
	return true;
}