// * �ļ���detail_page.cc
// * ���ߣ�������
// * ���ܣ����� DetailPage �ࡣ
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
  // ѡ����ʾ�ı�
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
  layoutText();   // ��ʾ�����ı�
  displayInfo();  // ��ʾ����ҳ��ѡ��������Ϣ
  // ˽�����ݳ�Ա��λ
  temp_user_.clear();
  temp_book_.clear();
  if (shared_task_ % 10 == detail_page::kModify) {  // ���ݼ̳�
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
  if (!current_user_.checkPermission()) return;  // ���Ȩ��
  if (option_text_ == L"") return;  // ���ѡ�����ʾ��
  COORD tmp_for_input = getInfoPosition(option_text_);  // �����λ
  // �����һ�����
  Page::returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_for_input);
  if (option_ == detail_page::CheckMode::kDescriptionLink) {  // ��ռ��
    for (int i = 1;
         i <= max(temp_book_.getDescription().length(),
                  searching_book_.getDescription().length());
         i++) {
      std::wcout << " ";
      if (i % scene::kAdviceLength == 0) std::wcout << "\n";
    }
  } else {  // ���������Ϣ
    for (int i = 1; i <= scene::kAdviceLength; i++) std::wcout << " ";
  }
  // �ƶ���겢��ʾ���û�����
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_for_input);
  Page::hideCursor(false);
  switch (option_) {
    case detail_page::CheckMode::kNameLink:  // ����ͼ����û�����
      (floor((shared_task_) / 10) ==
       detail_page::PortalTask::kBook)
          ? temp_book_.setName(inputLine(true, true, true, true, false))
          : temp_user_.setName(inputLine(false, true, true, true, false));
      break;
    case detail_page::CheckMode::kAuthorLink:  // ����ͼ������
      temp_book_.setAuthor(inputLine(true, true, true, true, false));
      break;
    case detail_page::CheckMode::kDescriptionLink: {  // ����ͼ����
      while (true) {
        std::wstring temp_line = inputLine(true, true, true, true, false);
        if (temp_line == L"") break;  // ���������س�������ֹ����
        temp_book_.setDescription((temp_book_.getDescription() + temp_line));
        tmp_for_input.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                 tmp_for_input);  // ���������һ��
      }
      break;
    }
    case detail_page::CheckMode::kPasswordLink:  // �����û�����
      password_request_ = inputLine(false, true, true, true, false);
      break;
    case detail_page::CheckMode::kPermissionLink: {  // �����û�Ȩ��
      std::wstring temp_string = inputLine(false, false, true, false, false);
      if (temp_string == detail_page::kAdminText) {  // ��Ϊ����Ա
        temp_user_.setPermission(true);
      } else if (temp_string == detail_page::kGuestText) {  // ��Ϊ��ͨ�û�
        temp_user_.setPermission(false);
      } else {  // ������ʾԭ��Ȩ��
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                                 tmp_for_input);
        (searching_user_.checkPermission())
            ? std::wcout << detail_page::kAdminText
            : std::wcout << detail_page::kGuestText;
      }
      break;
    }
    case detail_page::CheckMode::kTypeLink:  // ����ͼ������
      temp_book_.setType(inputLine(true, true, true, true, false));
      break;
  }
  Page::hideCursor(true);
}

bool DetailPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;                  // ���� checkLink()
  std::wstring prevoius_option_text = option_text_;  // Ϊָ���ƶ��ṩ����
  switch (option_ = check_mode) {  // ������ָ���ӦΪ���������ѡ���������
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
    case detail_page::CheckMode::kBorrowLink:  // ����
      borrowAction();
      return false;
    case detail_page::CheckMode::kReturnLink:  // �黹ͼ��
      returnAction();
      return false;
    case detail_page::CheckMode::kAddLink:  // ����ͼ����û�
      addAction();
      return false;
    case detail_page::CheckMode::kModifyLink:  // �޸�ͼ����û���Ϣ
      modifyAction();
      return false;
    case detail_page::CheckMode::kCancelLink:  // ȡ���޸�
      system("cls");
      layoutText();
      displayInfo();
      return false;
    case detail_page::CheckMode::kNextLink:  // ��ʷ��¼����һ��
      history_iterator++;
      system("cls");
      layoutText();
      displayInfo();
      return false;
    case detail_page::CheckMode::kLastLink:  // ��ʷ��¼����һ��
      if (history_iterator > 0) history_iterator--;
      system("cls");
      prepareScene();
      return false;
  }
  if (current_user_.checkPermission())
    pointerDisplay(prevoius_option_text);  // ����ѡ����λ�ã���������ã�
  return false;
}

void DetailPage::addAction() {
  if (floor(shared_task_ / 10) == detail_page::kUser) {  // �����û�
    std::wstring admin = current_user_.getName();
    std::wstring user_name = temp_user_.getName();
    // ���������û�
    temp_user_.appendHistory(L"Added", admin);
    temp_user_.addUser(password_request_);
    // �޸ĵ�ǰ��¼�û���ʷ������
    current_user_.appendHistory(L"Add", user_name);
    current_user_.saveUser(admin);
  }
  if (floor(shared_task_ / 10) == detail_page::kBook) {  // ����ͼ��
    std::wstring admin = current_user_.getName();
    std::wstring book_name = temp_book_.getName();
    // ��������ͼ��
    temp_book_.setState(L"Available");
    temp_book_.appendHistory(L"Added", admin);
    temp_book_.addBook();
    // �޸ĵ�ǰ��¼�û���ʷ������
    current_user_.appendHistory(L"Add", book_name);
    current_user_.saveUser(admin);
  }
  system("cls");
  prepareScene();  // ˢ����Ϣ
}

void DetailPage::modifyAction() {
  if (floor(shared_task_ / 10) == detail_page::kUser) {  // �޸��û�
    std::wstring admin = current_user_.getName();
    std::wstring user_name = searching_user_.getName();
    if (admin != user_name) {  // �޸������û�����Ϣ
      // �����޸ĵ��û���Ϣ
      temp_user_.appendHistory(L"Modified", admin);
      temp_user_.saveUser(user_name, password_request_);
      searching_user_.setName(user_name);
      // �޸ĵ�ǰ��¼�û���ʷ������
      current_user_.appendHistory(L"Modify", admin);
      current_user_.saveUser(admin);
    } else {  // �޸��Լ�����Ϣ
      // �����޸ĵ��û���Ϣ
      temp_user_.appendHistory(L"Modified", admin);
      temp_user_.saveUser(user_name, password_request_);
      searching_user_.setName(user_name);
    }
  }
  if (floor(shared_task_ / 10) == detail_page::kBook) {  // �޸�ͼ��
    std::wstring admin = current_user_.getName();
    std::wstring book_name = searching_book_.getName();
    // �����޸ĵ�ͼ����Ϣ
    temp_book_.appendHistory(L"Modified", admin);
    temp_book_.saveBook(book_name);
    searching_book_.setName(book_name);
    // �޸ĵ�ǰ��¼�û���ʷ������
    current_user_.appendHistory(L"Add", book_name);
    current_user_.saveUser(admin);
  }
  system("cls");
  prepareScene();  // ˢ����Ϣ
}

void DetailPage::returnAction() {
  if (searching_book_.getState() != L"Available") {  // У��״̬
    std::wstring user_name = current_user_.getName();
    std::wstring book_name = searching_book_.getName();
    Statistic::saveBorrowRecord(book_name, user_name);  // ������ļ�¼
    // �޸�ͼ��״̬����ʷ������
    searching_book_.setState(L"Available");
    searching_book_.appendHistory(L"Returned", user_name);
    searching_book_.saveBook(book_name);
    // �޸ĵ�ǰ��¼�û���ʷ������
    current_user_.appendHistory(L"Return", book_name);
    current_user_.saveUser(user_name);
    system("cls");
    prepareScene();  // ˢ����Ϣ
  }
}

void DetailPage::borrowAction() {
  if (searching_book_.getState() != L"Borrowed") {  // У��״̬
    std::wstring user_name = current_user_.getName();
    std::wstring book_name = searching_book_.getName();
    // �޸�ͼ��״̬����ʷ������
    searching_book_.setState(L"Borrowed");
    searching_book_.appendHistory(L"Borrowed", user_name);
    searching_book_.saveBook(book_name);
    // �޸ĵ�ǰ��¼�û���ʷ������
    current_user_.appendHistory(L"Borrow", book_name);
    current_user_.saveUser(user_name);
    system("cls");
    prepareScene();  // ˢ����Ϣ
  }
}

void DetailPage::displayInfo() {
  dataDisplay();
}

void DetailPage::pointerDisplay(const std::wstring& previous_text) {
  // ��λѡ��ָ��
  if (previous_text != L"") {
    COORD pointer_prevoius = (*pageunit_list_head_)[previous_text].pos_;
    pointer_prevoius.X += detail_page::kPointerOffset.X;
    pointer_prevoius.Y += detail_page::kPointerOffset.Y;
    Page::pointPaint(pointer_prevoius, page::GROUND_DEFAULT, L" ");
  }
  COORD pointer_new = (*pageunit_list_head_)[option_text_].pos_;
  pointer_new.X += detail_page::kPointerOffset.X;
  pointer_new.Y += detail_page::kPointerOffset.Y;
  // ��λ����ʾ�ո���λ����ʾָ��ͼ��
  Page::pointPaint(pointer_new, detail_page::kPointerColor,
                   detail_page::kPointerText);
}

bool DetailPage::dataDisplay() {
  // ����������ʾ����
  if (shared_task_ % 10 == detail_page::kAdd) return true;
  switch ((int)floor(shared_task_ / 10)) {
    case detail_page::kUser:  // ����Ա����ͨ�û����ɲ鿴���ơ�Ȩ�޺���ʷ
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
    case detail_page::kBook:  // ���ɼ����ơ����ߡ����״̬��������ʷ
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
    for (int i = 0; i < scene::kAdviceLength; i++) {  // ��ÿһ�����ַ����
      Page::pointPaint(tmp_position, page::GROUND_DEFAULT,
                       tmp_description.substr(0, 1));
      if (tmp_description.length() >= 1) {
        tmp_description = tmp_description.substr(1);
      } else {
        tmp_description = L"";
      }
      tmp_position.X += 1;
    }
    // ����
    tmp_position.X -= scene::kAdviceLength;
    tmp_position.Y += 1;
  }
}

bool DetailPage::historyDisplay() {
  COORD tmp_coord = getInfoPosition(detail_page::kHistoryText);
  COORD temp_start = tmp_coord;  // ���ڼ�¼����λ��
  std::wstring temp_history;     // ���ڶ�ȡ������ʷ
  switch ((int)floor(shared_task_ / 10)) {  // ��ȡ������ʷ
    case detail_page::kUser:
      temp_history = searching_user_.getHistory();
      break;
    case detail_page::kBook:
      temp_history = searching_book_.getHistory();
      break;
  }
  // ȥ����ʷ��¼��ͷ�Ŀո�
  while (temp_history[0] == L' ') temp_history = temp_history.substr(1);
  int i = 0, j = 0;  // i ���ڼ����Ƿ�Ϊһ�У�j ���ڼ�������
  while (temp_history.length() &&  // ��ʷ��¼��ͷ��������ʾ��������ֹͣ��ʾ
         j < history_iterator + detail_page::kMaxHistoryNum) {
    std::wstring tmp_str = temp_history.substr(0, 1);
    if (tmp_str == L" ") i++;  // ͨ������ո������ƶ���β
    if (i != detail_page::kHistoryLength &&
        j >= history_iterator) {  // ���ַ����
      Page::pointPaint(tmp_coord, page::GROUND_DEFAULT, tmp_str);
      tmp_coord.X++;
    } else {                                      // ��һ�к�
      if (j >= history_iterator) temp_start.Y++;  // ��ʼ��ʾ����Ҫ����
      tmp_coord = temp_start;
      if (i == detail_page::kHistoryLength) {
        j++;  // ���������Ͼ���������
        i = 0;
      }
    }
    temp_history = temp_history.substr(1);  // ȥ���������ַ�
  }
  return true;
}

COORD DetailPage::getInfoPosition(const std::wstring& guidance_text) {
  COORD tmp_coord = (*pageunit_list_head_)[guidance_text].pos_;  // ��λ��ʾ��
  tmp_coord.X += short(guidance_text.length() + 1);  // ������Ϣ��ʾλ��
  return tmp_coord;
}
}  // namespace library_management_sys