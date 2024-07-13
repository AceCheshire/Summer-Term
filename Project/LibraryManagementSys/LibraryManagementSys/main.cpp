#include<iostream>
#include<windows.h>
#include"PageConst.h"
using namespace std;

COORD screenPos;

int main() {
	Page testPage;
	screenPos = { 50,10 };
	testPage.PointPaint(screenPos, FOREGROUND_GREEN);
	printf("TEST SUCCESS");
	testPage.PointPaint(screenPos, FOREGOUND_WHITE);
	return 0;
}