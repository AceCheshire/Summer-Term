#pragma once
#include"general_scene_sp.h"
#include"page_base.h"
#include"scene_base.h"
constexpr char kLoginPageDataSource[] = "login_page_data.txt";
constexpr char kLoginAdminNameText[] = "Admin_ID_/_name: ";
constexpr char kLoginAdminPasswordText[] = "Admin_password:";
constexpr COORD kInputOffset = {20, 0};

class LoginPage : public GeneralScene {
 public:
  LoginPage(Mouse*, Scene*, PageUnitEx*);
  bool prepareScene();
  void inputLoginInfo();

 private:
  bool is_inputting_login_info_ = false;
  std::string admin_name_request_ = {};
  std::string admin_password_request_ = {};
};