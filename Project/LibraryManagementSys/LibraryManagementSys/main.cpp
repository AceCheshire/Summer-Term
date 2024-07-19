#include<iostream>
#include<windows.h>
#include"PageConst.h"
#include"MouseConst.h"
#include"SceneConst.h"
#include"LinkConst.h"
#include"ReaderConst.h"
using namespace std;

COORD screenPos;

int main() {
	Page testPage;
	Mouse testMouse;
	testPage.HideCursor();
	while (true) {
		while (true) {
			screenPos = { 0,5 };
			testPage.PointPaint(screenPos, FOREGROUND_GREEN);
			cout << "When he returned, the boy was able to describe everything he had seen to the old man.the boy was able to describe everything he had seen to the old man.";
			screenPos = { 0,11 };
			testPage.PointPaint(screenPos, FOREGROUND_WHITE);
			cout << "                                                       ";
			if (testMouse.HoverAndClick() != "_NULL_") break;
		}
		Sleep(1000);
		while (true) {
			screenPos = { 0,5 };
			testPage.PointPaint(screenPos, FOREGROUND_GREEN);
			cout << "The company Jackie chose planned to employ only one person, but more than twenty people applied for the job.                                            ";
			screenPos = { 0,11 };
			testPage.PointPaint(screenPos, FOREGROUND_WHITE);
			cout << "                                                       ";
			if (testMouse.HoverAndClick() != "_NULL_") break;
		}
		Sleep(1000);
	}
	return 0;
}