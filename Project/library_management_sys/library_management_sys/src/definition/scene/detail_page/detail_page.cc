// * 文件：detail_page.cc
// * 作者：麦天乐
// * 介绍：定义 DetailPage 类。
#include "inc/inheritance/scene/detail_page/detail_page.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/app_const.h"
#include "inc/base/book_base.h"
#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/statistic_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
DetailPage::DetailPage(PageUnitEx& admin_add_user,
                       PageUnitEx& admin_modify_user,
                       PageUnitEx& guest_read_user, PageUnitEx& admin_add_book,
                       PageUnitEx& admin_modify_book,
                       PageUnitEx& guest_read_book)
    : SharedScene(admin_add_user),
      pageunit_list_head_1_(&admin_add_user),
      pageunit_list_head_2_(&admin_modify_user),
      pageunit_list_head_3_(&guest_read_user),
      pageunit_list_head_4_(&admin_add_book),
      pageunit_list_head_5_(&admin_modify_book),
      pageunit_list_head_6_(&guest_read_book) {}

bool DetailPage::prepareScene() {
  // 选择显示文本
  switch (shared_task_) {
    case detail_page::kUser * 10 + detail_page::kAdd:
      setPageUnitList(*pageunit_list_head_1_);
      break;
    case detail_page::kUser * 10 + detail_page::kModify:
      (current_user_.checkPermission())
          ? setPageUnitList(*pageunit_list_head_2_)
          : setPageUnitList(*pageunit_list_head_3_);
      break;
    case detail_page::kBook * 10 + detail_page::kAdd:
      setPageUnitList(*pageunit_list_head_4_);
      break;
    case detail_page::kBook * 10 + detail_page::kModify:
      (current_user_.checkPermission())
          ? setPageUnitList(*pageunit_list_head_5_)
          : setPageUnitList(*pageunit_list_head_6_);
      break;
  }
  layoutText();   // 显示固有文本
  displayInfo();  // 显示搜索页面选择对象的信息
  // 私有数据成员复位
  temp_user_.clear();
  temp_book_.clear();
  if (shared_task_ % 10 == detail_page::kModify) {  // 数据继承
    temp_user_ = searching_user_;
    temp_book_ = searching_book_;
  }
  option_ = 0;
  option_text_.clear();
  history_iterator = 0;
  password_request_.clear();
  return true;
}

void DetailPage::inputInfo() {
  if (!current_user_.checkPermission()) return;  // 检查权限
  if (option_text_ == L"") return;  // 检查选择的提示语
  COORD tmp_for_input = getInfoPosition(option_text_);  // 输入框定位
  // 清除上一次输出
  Page::returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_for_input);
  if (option_ == detail_page::CheckMode::kDescriptionLink) {  // 清空简介
    for (int i = 1;
         i <= max(temp_book_.getDescription().length(),
                  searching_book_.getDescription().length());
         i++) {
      std::wcout << " ";
      if (i % scene::kAdviceLength == 0) std::wcout << "\n";
    }
  } else {  // 清空其余信息
    for (int i = 1; i <= scene::kAdviceLength; i++) std::wcout << " ";
  }
  // 移动光标并显示，用户输入
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_for_input);
  Page::hideCursor(false);
  switch (option_) {
    case detail_page::CheckMode::kNameLink:  // 输入图书或用户名称
      (floor((shared_task_) / 10) ==
       detail_page::PortalTask::kBook)
          ? temp_book_.setName(inputLine(true, true, true, true, false))
          : temp_user_.setName(inputLine(false, true, true, true, false));
      break;
    case detail_page::CheckMode::kAuthorLink:  // 输入图书作者
      temp_book_.setAuthor(inputLine(true, true, true, true, false));
      break;
    case detail_page::CheckMode::kDescriptionLink: {  // 输入图书简介
      while (true) {
        std::wstring temp_line = inputLine(true, true, true, true, false);
        if (temp_line == L"") break;  // 连续两个回车即可终止输入
        temp_book_.setDescription((temp_book_.getDescription() + temp_line));
        tmp_for_input.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                 tmp_for_input);  // 光标移至下一行
      }
      break;
    }
    case detail_page::CheckMode::kPasswordLink:  // 输入用户密码
      password_request_ = inputLine(false, true, true, true, false);
      break;
    case detail_page::CheckMode::kPermissionLink: {  // 输入用户权限
      std::wstring temp_string = inputLine(false, false, true, false, false);
      if (temp_string == detail_page::kAdminText) {  // 设为管理员
        temp_user_.setPermission(true);
      } else if (temp_string == detail_page::kGuestText) {  // 设为普通用户
        temp_user_.setPermission(false);
      } else {  // 重新显示原有权限
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                 tmp_for_input);
        (searching_user_.checkPermission())
            ? std::wcout << detail_page::kAdminText
            : std::wcout << detail_page::kGuestText;
      }
      break;
    }
    case detail_page::CheckMode::kTypeLink:  // 输入图书类型
      temp_book_.setType(inputLine(true, true, true, true, false));
      break;
  }
  Page::hideCursor(true);
}

bool DetailPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;                  // 无需 checkLink()
  std::wstring prevoius_option_text = option_text_;  // 为指针移动提供参数
  switch (option_ = check_mode) {  // 若任务指令对应为引导语，更新选择的引导语
    case detail_page::CheckMode::kNameLink:
      option_text_ = detail_page::kNameText;
      break;
    case detail_page::CheckMode::kAuthorLink:
      option_text_ = detail_page::kAuthorText;
      break;
    case detail_page::CheckMode::kDescriptionLink:
      option_text_ = detail_page::kDescriptionText;
      break;
    case detail_page::CheckMode::kPasswordLink:
      option_text_ = detail_page::kPasswordText;
      break;
    case detail_page::CheckMode::kPermissionLink:
      option_text_ = detail_page::kPermissionText;
      break;
    case detail_page::CheckMode::kTypeLink:
      option_text_ = detail_page::kTypeText;
      break;
    case detail_page::CheckMode::kBorrowLink:  // 借书
      borrowAction();
      return false;
    case detail_page::CheckMode::kReturnLink:  // 归还图书
      returnAction();
      return false;
    case detail_page::CheckMode::kAddLink:  // 新增图书或用户
      addAction();
      return false;
    case detail_page::CheckMode::kModifyLink:  // 修改图书或用户信息
      modifyAction();
      return false;
    case detail_page::CheckMode::kCancelLink:  // 取消修改
      system("cls");
      layoutText();
      displayInfo();
      return false;
    case detail_page::CheckMode::kNextLink:  // 历史记录翻下一条
      history_iterator++;
      system("cls");
      layoutText();
      displayInfo();
      return false;
    case detail_page::CheckMode::kLastLink:  // 历史记录翻上一条
      if (history_iterator > 0) history_iterator--;
      system("cls");
      prepareScene();
      return false;
  }
  if (current_user_.checkPermission())
    pointerDisplay(prevoius_option_text);  // 更新选择光标位置（若输入可用）
  return false;
}

void DetailPage::addAction() {
  if (floor(shared_task_ / 10) == detail_page::kUser) {  // 新增用户
    std::wstring admin = current_user_.getName();
    std::wstring user_name = temp_user_.getName();
    // 保存新增用户
    temp_user_.appendHistory(L"Added", admin);
    temp_user_.addUser(password_request_);
    // 修改当前登录用户历史并保存
    current_user_.appendHistory(L"Add", user_name);
    current_user_.saveUser(admin);
  }
  if (floor(shared_task_ / 10) == detail_page::kBook) {  // 新增图书
    std::wstring admin = current_user_.getName();
    std::wstring book_name = temp_book_.getName();
    // 保存新增图书
    temp_book_.setState(L"Available");
    temp_book_.appendHistory(L"Added", admin);
    temp_book_.addBook();
    // 修改当前登录用户历史并保存
    current_user_.appendHistory(L"Add", book_name);
    current_user_.saveUser(admin);
  }
  system("cls");
  prepareScene();  // 刷新信息
}

void DetailPage::modifyAction() {
  if (floor(shared_task_ / 10) == detail_page::kUser) {  // 修改用户
    std::wstring admin = current_user_.getName();
    std::wstring user_name = searching_user_.getName();
    if (admin != user_name) {  // 修改其他用户的信息
      // 保存修改的用户信息
      temp_user_.appendHistory(L"Modified", admin);
      temp_user_.saveUser(user_name, password_request_);
      searching_user_.setName(user_name);
      // 修改当前登录用户历史并保存
      current_user_.appendHistory(L"Modify", admin);
      current_user_.saveUser(admin);
    } else {  // 修改自己的信息
      // 保存修改的用户信息
      temp_user_.appendHistory(L"Modified", admin);
      temp_user_.saveUser(user_name, password_request_);
      searching_user_.setName(user_name);
    }
  }
  if (floor(shared_task_ / 10) == detail_page::kBook) {  // 修改图书
    std::wstring admin = current_user_.getName();
    std::wstring book_name = searching_book_.getName();
    // 保存修改的图书信息
    temp_book_.appendHistory(L"Modified", admin);
    temp_book_.saveBook(book_name);
    searching_book_.setName(book_name);
    // 修改当前登录用户历史并保存
    current_user_.appendHistory(L"Add", book_name);
    current_user_.saveUser(admin);
  }
  system("cls");
  prepareScene();  // 刷新信息
}

void DetailPage::returnAction() {
  if (searching_book_.getState() != L"Available") {  // 校验状态
    std::wstring user_name = current_user_.getName();
    std::wstring book_name = searching_book_.getName();
    Statistic::saveBorrowRecord(book_name, user_name);  // 保存借阅记录
    // 修改图书状态和历史并保存
    searching_book_.setState(L"Available");
    searching_book_.appendHistory(L"Returned", user_name);
    searching_book_.saveBook(book_name);
    // 修改当前登录用户历史并保存
    current_user_.appendHistory(L"Return", book_name);
    current_user_.saveUser(user_name);
    system("cls");
    prepareScene();  // 刷新信息
  }
}

void DetailPage::borrowAction() {
  if (searching_book_.getState() != L"Borrowed") {  // 校验状态
    std::wstring user_name = current_user_.getName();
    std::wstring book_name = searching_book_.getName();
    // 修改图书状态和历史并保存
    searching_book_.setState(L"Borrowed");
    searching_book_.appendHistory(L"Borrowed", user_name);
    searching_book_.saveBook(book_name);
    // 修改当前登录用户历史并保存
    current_user_.appendHistory(L"Borrow", book_name);
    current_user_.saveUser(user_name);
    system("cls");
    prepareScene();  // 刷新信息
  }
}

void DetailPage::displayInfo() {
  dataDisplay();
}

void DetailPage::pointerDisplay(const std::wstring& previous_text) {
  // 定位选择指针
  if (previous_text != L"") {
    COORD pointer_prevoius = (*pageunit_list_head_)[previous_text].pos_;
    pointer_prevoius.X += detail_page::kPointerOffset.X;
    pointer_prevoius.Y += detail_page::kPointerOffset.Y;
    Page::pointPaint(pointer_prevoius, page::GROUND_DEFAULT, L" ");
  }
  COORD pointer_new = (*pageunit_list_head_)[option_text_].pos_;
  pointer_new.X += detail_page::kPointerOffset.X;
  pointer_new.Y += detail_page::kPointerOffset.Y;
  // 旧位置显示空格，新位置显示指针图案
  Page::pointPaint(pointer_new, detail_page::kPointerColor,
                   detail_page::kPointerText);
}

bool DetailPage::dataDisplay() {
  // 新增对象不显示数据
  if (shared_task_ % 10 == detail_page::kAdd) return true;
  switch ((int)floor(shared_task_ / 10)) {
    case detail_page::kUser:  // 管理员和普通用户均可查看名称、权限和历史
      Page::pointPaint(getInfoPosition(detail_page::kNameText),
                       page::GROUND_DEFAULT,
                       searching_user_.getName());
      Page::pointPaint(getInfoPosition(detail_page::kPermissionText),
                       page::GROUND_DEFAULT,
                       (searching_user_.checkPermission())
                           ? detail_page::kAdminText
                           : detail_page::kGuestText);
      historyDisplay();
      break;
    case detail_page::kBook:  // 均可见名称、作者、类别、状态、简介和历史
      Page::pointPaint(getInfoPosition(detail_page::kNameText),
                       page::GROUND_DEFAULT,
                       searching_book_.getName());
      Page::pointPaint(getInfoPosition(detail_page::kAuthorText),
                       page::GROUND_DEFAULT,
                       searching_book_.getAuthor());
      Page::pointPaint(getInfoPosition(detail_page::kTypeText),
                       page::GROUND_DEFAULT,
                       searching_book_.getType());
      Page::pointPaint(getInfoPosition(detail_page::kStateText),
                       page::GROUND_DEFAULT,
                       searching_book_.getState());
      historyDisplay();
      descriptionDisplay();
      break;
    default:
      break;
  }
  return true;
}

void DetailPage::descriptionDisplay() {
  COORD tmp_position = getInfoPosition(detail_page::kDescriptionText);
  std::wstring tmp_description = searching_book_.getDescription();
  while (tmp_description.length()) {
    for (int i = 0; i < scene::kAdviceLength; i++) {  // 对每一行逐字符输出
      Page::pointPaint(tmp_position, page::GROUND_DEFAULT,
                       tmp_description.substr(0, 1));
      if (tmp_description.length() >= 1) {
        tmp_description = tmp_description.substr(1);
      } else {
        tmp_description = L"";
      }
      tmp_position.X += 1;
    }
    // 换行
    tmp_position.X -= scene::kAdviceLength;
    tmp_position.Y += 1;
  }
}

bool DetailPage::historyDisplay() {
  COORD tmp_coord = getInfoPosition(detail_page::kHistoryText);
  COORD temp_start = tmp_coord;  // 用于记录行首位置
  std::wstring temp_history;     // 用于读取借阅历史
  switch ((int)floor(shared_task_ / 10)) {  // 读取借阅历史
    case detail_page::kUser:
      temp_history = searching_user_.getHistory();
      break;
    case detail_page::kBook:
      temp_history = searching_book_.getHistory();
      break;
  }
  // 去除历史记录开头的空格
  while (temp_history[0] == L' ') temp_history = temp_history.substr(1);
  int i = 0, j = 0;  // i 用于计算是否为一行，j 用于计算行数
  while (temp_history.length() &&  // 历史记录到头或满足显示的条数则停止显示
         j < history_iterator + detail_page::kMaxHistoryNum) {
    std::wstring tmp_str = temp_history.substr(0, 1);
    if (tmp_str == L" ") i++;  // 通过计算空格数量推断行尾
    if (i != detail_page::kHistoryLength &&
        j >= history_iterator) {  // 逐字符输出
      Page::pointPaint(tmp_coord, page::GROUND_DEFAULT, tmp_str);
      tmp_coord.X++;
    } else {                                      // 满一行后
      if (j >= history_iterator) temp_start.Y++;  // 开始显示则需要换行
      tmp_coord = temp_start;
      if (i == detail_page::kHistoryLength) {
        j++;  // 计算数据上经历的行数
        i = 0;
      }
    }
    temp_history = temp_history.substr(1);  // 去除经历的字符
  }
  return true;
}

COORD DetailPage::getInfoPosition(const std::wstring& guidance_text) {
  COORD tmp_coord = (*pageunit_list_head_)[guidance_text].pos_;  // 定位提示语
  tmp_coord.X += short(guidance_text.length() + 1);  // 计算信息显示位置
  return tmp_coord;
}
}  // namespace library_management_sys