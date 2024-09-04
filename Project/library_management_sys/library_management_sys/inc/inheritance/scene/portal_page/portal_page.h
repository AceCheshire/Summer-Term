// * �ļ���portal_page.h
// * ���ߣ�������
// * ���ܣ����� PortalPage �ࡣ
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/scheduler_base.h"
#ifndef LMS_INHERITANCE_SCENE_PORTAL_PAGE_H_
#define LMS_INTERITANCE_SCENE_PORTAL_PAGE_H_
namespace library_management_sys {
// �涨��Ӧ�õ���ҳ��ķ�ʽ��ʾ����
//    PageUnitEx test_unit_ex;
//    PortalPage test_portal_page(test_unit_ex, test_scheduler);
class PortalPage : public SharedScene {
 public:
  PortalPage(PageUnitEx& pageunit_list_head, Scheduler& scheduler);  // ���캯��
  // ���������������������档ʾ����
  //    test_scene.prepareScene();
  bool prepareScene();
  void inputInfo() {}  // ������ӿ�
  // �������ú���������Ҫ��������񣬲����Ƿ����档
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // �����������
  bool getKeyboardInputState() { return true; }  // �����������

 private:
  // ���ֶ� �� , hello �� ǰ��ʾ��ǰ��¼�û����ơ�
  void displayUserName();
  // ��ʾͳ����Ϣ
  void displayStatistic();
  // ���ڴ�����ֹ������Ϣ
  Scheduler* scheduler_ = NULL;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_PORTAL_PAGE_H_