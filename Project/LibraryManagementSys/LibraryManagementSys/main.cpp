#include"HomePageSp.h"
#include"LinkConst.h"
#include"MouseConst.h"
#include"PageConst.h"
#include"ReaderConst.h"
#include"SceneConst.h"
#include<iostream>
#include<windows.h>
using namespace std;

COORD screenPos;

int main() {
	Page prePage;
	Mouse generalMouse;
	Reader generalReader;
	prePage.HideCursor();
	PageUnitEx homePageText;
	generalReader.ReadForPointPaint(&homePageText, HOME_PAGE_DATA);
	HomePage homePage(&generalMouse, NULL, homePageText);
	homePage.PrepareScene();
	return 0;
}