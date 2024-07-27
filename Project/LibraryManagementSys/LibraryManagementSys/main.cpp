#include"HomePageSp.h"
#include"HelpPageSp.h"
#include"LoginPageSp.h"
#include"ReaderBase.h"
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
	HomePage homePage(&generalMouse, NULL, &homePageText);

	PageUnitEx loginPageText;
	generalReader.ReadForPointPaint(&loginPageText, LOGIN_PAGE_DATA);
	LoginPage loginPage(&generalMouse, &homePage, &loginPageText);
	Link HomePage_LoginAdPage("Login_as_admin", &loginPage);
	Link HomePage_LoginGuPage("Login_as_guest", &loginPage);
	GeneralScene::AppendLink(&HomePage_LoginAdPage);
	GeneralScene::AppendLink(&HomePage_LoginGuPage);

	PageUnitEx helpPageText;
	generalReader.ReadForPointPaint(&helpPageText, HELP_PAGE_DATA);
	HelpPage helpPage(&generalMouse, &homePage, &helpPageText);
	Link HomePage_HelpPage("Help", &helpPage);
	GeneralScene::AppendLink(&HomePage_HelpPage);

	homePage.PrepareScene();

	helpPageText.DeleteAll();
	loginPageText.DeleteAll();
	homePageText.DeleteAll();
	
	return 0;
}