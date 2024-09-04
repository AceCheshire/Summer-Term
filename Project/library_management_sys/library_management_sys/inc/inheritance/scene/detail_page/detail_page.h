// * 文件：detail_page.h
// * 作者：麦天乐
// * 介绍：声明 DetailPage 类。
#include <windows.h>

#include <string>

#include "inc/base/book_base.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/user_base.h"
#ifndef LMS_INHERITANCE_SCENE_DETAIL_PAGE_H_
#define LMS_INHERITANCE_SCENE_DETAIL_PAGE_H_
namespace library_management_sys {
// 规定了应用详情页面的范式。示例：
//    PageUnitEx test_unit_ex;
//    DetailPage test_detail_page(test_unit_ex_1, test_unit_ex_2,
//                                test_unit_ex_3, test_unit_ex_4, 
//                                test_unit_ex_5, test_unit_ex_6);
class DetailPage : public SharedScene {
 public:
  // 包含六种场景文本，用来显示用户信息和图书信息，分为管理员新增、管理员修改和普通用户查看
  // 三种情况。其中传入的第一种场景文本会用来初始化基类 Scene 。
  DetailPage(PageUnitEx& admin_add_user, PageUnitEx& admin_modify_user,
             PageUnitEx& guest_read_user, PageUnitEx& admin_add_book,
             PageUnitEx& admin_modify_book, PageUnitEx& guest_read_book);  // 构造函数
  // 用于启动场景，并返回真。示例：
  //    test_scene.prepareScene();
  bool prepareScene();
  // 在用户输入用户或图书名称时被执行。示例：
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();
  // 用于实现借阅与归还，新增、修改与取消修改。只有点击返回键才会返回真。
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // 允许鼠标输入
  bool getKeyboardInputState() { return true; }  // 允许键盘输入

 private:
  // 按下修改按键的响应，包括修改文件夹，新增历史记录。
  void modifyAction();
  // 按下新增按键的响应，包括新建文件夹，新增历史记录。
  void addAction();
  // 按下借阅按键的响应，包括调整图书状态，新增历史记录。
  void borrowAction();
  // 按下归还按键的响应，包括调整图书状态，新增历史记录。
  void returnAction();
  // 根据引导语显示图书或用户信息和相应按键
  void displayInfo();
  // 找到给定文本的位置，计算选择指针的位置并显示。
  void pointerDisplay(const std::wstring& match_text);
  // 显示图书或用户数据（可自动判断）
  bool dataDisplay();
  // 显示图书简介
  void descriptionDisplay();
  // 显示图书或用户的借阅历史（可自动判断）
  bool historyDisplay();
  // 为 pointPaint() 返回输出坐标，参数为引导语内容。
  COORD getInfoPosition(const std::wstring& guidance_text);
  // 记录管理员新增用户页面的场景文本
  PageUnitEx* pageunit_list_head_1_;
  // 记录管理员修改用户页面的场景文本
  PageUnitEx* pageunit_list_head_2_;
  // 记录普通用户查看用户页面的场景文本
  PageUnitEx* pageunit_list_head_3_;
  // 记录管理员新增图书页面的场景文本
  PageUnitEx* pageunit_list_head_4_;
  // 记录管理员修改图书页面的场景文本
  PageUnitEx* pageunit_list_head_5_;
  // 记录普通用户查看图书页面的场景文本
  PageUnitEx* pageunit_list_head_6_;
  // 记录用户选择的引导语对应的任务指令
  int option_ = 0;
  // 记录用户选择的引导语
  std::wstring option_text_;
  // 记录用户查阅历史的编号
  int history_iterator = 0;
  // 记录用户希望更改的密码
  std::wstring password_request_;
  // 暂时储存用户修改或新建的用户信息
  User temp_user_;
  // 暂时储存用户修改或新建的图书信息
  Book temp_book_;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_DETAIL_PAGE_H_