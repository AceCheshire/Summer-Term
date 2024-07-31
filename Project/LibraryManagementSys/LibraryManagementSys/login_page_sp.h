#pragma once
#include"general_scene_sp.h"
#include"page_base.h"
#include"scene_base.h"
constexpr char kLoginPageDataSource[20] = "login_page_data.txt";

class LoginPage :public GeneralScene {
public:
	LoginPage(Mouse*, Scene*, PageUnitEx*);
	bool prepareScene();
};
