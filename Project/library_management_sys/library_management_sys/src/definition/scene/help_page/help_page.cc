// * �ļ���help_page.cc
// * ���ߣ�������
// * ���ܣ����� HelpPage �ࡣ
#include "inc/inheritance/scene/help_page/help_page.h"

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
namespace library_management_sys {
HelpPage::HelpPage(PageUnitEx& pageunit_list_head)
    : Scene(pageunit_list_head) {}

bool HelpPage::prepareScene() {
  layoutText();
  return true;
}
}  // namespace library_management_sys