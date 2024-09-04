// * �ļ���portal_page.cc
// * ���ߣ�������
// * ���ܣ����� PortalPage �ࡣ
#include "inc/inheritance/scene/portal_page/portal_page.h"

#include <windows.h>

#include "inc/app_const.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#include "inc/base/statistic_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
PortalPage::PortalPage(PageUnitEx& pageunit_list_head, Scheduler& scheduler)
    : SharedScene(pageunit_list_head), scheduler_(&scheduler) {}

bool PortalPage::prepareScene() {
  layoutText();
  displayUserName();
  displayStatistic();
  // ���ݳ�Ա��λ
  shared_task_ = 0;
  searching_book_.clear();
  searching_user_.clear();
  return true;
}

void PortalPage::displayUserName() {
  PageUnit tmp_unit;
  std::wstring user_name = current_user_.getName();
  tmp_unit = (*pageunit_list_head_)[L", hello"];  // ��ʾ�ʶ�λ
  Page::pointPaint(tmp_unit.pos_.X - (short)user_name.length(), tmp_unit.pos_.Y,
                   page::GROUND_DEFAULT,
                   user_name);  // �����ʽΪ��user_name, hello
}

void PortalPage::displayStatistic() {
  // ��ʾ���ܻ�ӭͼ��
  COORD tmp_position = (*pageunit_list_head_)[L"Best Book:"].pos_;
  tmp_position.X += portal_page::kOutputOffset.X;
  tmp_position.Y += portal_page::kOutputOffset.Y;
  Page::pointPaint(tmp_position, page::GROUND_DEFAULT,
                   Statistic::getBestBook());
  // ��ʾ��������û�
  tmp_position = (*pageunit_list_head_)[L"Best Reader:"].pos_;
  tmp_position.X += portal_page::kOutputOffset.X;
  tmp_position.Y += portal_page::kOutputOffset.Y;
  Page::pointPaint(tmp_position, page::GROUND_DEFAULT,
                   Statistic::getBestReader());
  // ��ʾ��������
  tmp_position = (*pageunit_list_head_)[L"Borrowing Number:"].pos_;
  tmp_position.X += portal_page::kOutputOffset.X;
  tmp_position.Y += portal_page::kOutputOffset.Y;
  Page::pointPaint(tmp_position, page::GROUND_DEFAULT,
                   std::to_wstring(Statistic::getBorrowNum()));
  // ��ʾ����ͼ
  Statistic::graph(portal_page::kOrigin, portal_page::kGraphSize.Y,
                   portal_page::kGraphSize.X, 1);
}

bool PortalPage::checkLink(unsigned short check_mode) {
  switch (check_mode) {
    case portal_page::kUser:
      shared_task_ = portal_page::kUser;
      break;
    case portal_page::kBook:
      shared_task_ = portal_page::kBook;
      break;
    case portal_page::kExit:
      scheduler_->exit();
      break;
  }
  return true;
}
}  // namespace library_management_sys