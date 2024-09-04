// * �ļ���home_page.h
// * ���ߣ�������
// * ���ܣ����� HomePage �ࡣ
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#ifndef LMS_INHERITANCE_SCENE_HOME_PAGE_H_
#define LMS_INHERITANCE_SCENE_HOME_PAGE_H_
namespace library_management_sys {
// �涨��Ӧ����ҳ�ķ�ʽ��ʾ����
//    PageUnitEx test_unit_ex;
//    HomePage test_home_page(test_unit_ex, test_scehduler);
class HomePage : public Scene {
 public:
  HomePage(PageUnitEx& pageunit_list_head, Scheduler& scheduler);  // ���캯��
  // ���������������������档ʾ����
  //    test_scene.prepareScene();
  bool prepareScene();
  void inputInfo() {}                            // ������ӿ�
  bool checkLink(unsigned short check_mode);     //  �˳�����
  bool getMouseInputState() { return true; }     // �����������
  bool getKeyboardInputState() { return true; }  // �����������
 private:
  // ���ڴ�����ֹ������Ϣ
  Scheduler* scheduler_ = NULL;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_HOME_PAGE_H_