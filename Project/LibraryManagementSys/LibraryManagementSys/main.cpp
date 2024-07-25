#include"HomePageSp.h"
#include"LinkConst.h"
#include"LoginPageSp.h"
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

	PageUnitEx loginPageText;
	generalReader.ReadForPointPaint(&loginPageText, LOGIN_PAGE_DATA);
	LoginPage loginPage(&generalMouse, &homePage, loginPageText);
	Link HomePage_LoginPage("Login_as_admin", &loginPage);
	GeneralScene::AppendLink(&HomePage_LoginPage);

	homePage.PrepareScene();
	return 0;
}