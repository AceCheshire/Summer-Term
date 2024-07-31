#include"home_page_sp.h"
#include"help_page_sp.h"
#include"login_page_sp.h"
#include"reader_base.h"
#include<iostream>
#include<windows.h>
using namespace std;

COORD screenPos;

int main() {
	Page pre_page;
	Mouse general_mouse;
	Reader general_reader;
	pre_page.hideCursor();

	PageUnitEx home_page_text;
	general_reader.readForPointPaint(&home_page_text, kHomePageDataSource);
	HomePage home_page(&general_mouse, NULL, &home_page_text);

	PageUnitEx login_page_text;
	general_reader.readForPointPaint(&login_page_text, kLoginPageDataSource);
	LoginPage login_page(&general_mouse, &home_page, &login_page_text);
	Link home_page_to_login_admin_page("Login_as_admin", &login_page);
	Link home_page_to_login_guest_page("Login_as_guest", &login_page);
	GeneralScene::appendLink(&home_page_to_login_admin_page);
	GeneralScene::appendLink(&home_page_to_login_guest_page);

	PageUnitEx help_page_text;
	general_reader.readForPointPaint(&help_page_text, kHelpPageDataSource);
	HelpPage help_page(&general_mouse, &home_page, &help_page_text);
	Link home_page_to_help_page("Help", &help_page);
	GeneralScene::appendLink(&home_page_to_help_page);

	home_page.prepareScene();

	help_page_text.deleteAll();
	login_page_text.deleteAll();
	home_page_text.deleteAll();
	
	return 0;
}