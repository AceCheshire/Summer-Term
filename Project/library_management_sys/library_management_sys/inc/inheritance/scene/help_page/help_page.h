// * �ļ���help_page.h
// * ���ߣ�������
// * ���ܣ����� HelpPage �ࡣ
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_INHERITANCE_SCENE_HELP_PAGE_H_
#define LMS_INHERITANCE_SCENE_HELP_PAGE_H_
namespace library_management_sys {
// �涨��Ӧ�ð���ҳ��ķ�ʽ��ʾ����
//    PageUnitEx test_unit_ex;
//    HelpPage test_help_page(test_unit_ex);
class HelpPage : public Scene {
 public:
  HelpPage(PageUnitEx& pageunit_list_head);  // ���캯��
  // ���������������������档ʾ����
  //    test_scene.prepareScene();
  bool prepareScene();
  void inputInfo() {}                                         // ������ӿ�
  bool checkLink(unsigned short check_mode) { return true; }  // �޳�������
  bool getMouseInputState() { return true; }     // �����������
  bool getKeyboardInputState() { return true; }  // �����������
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_HELP_PAGE_H_