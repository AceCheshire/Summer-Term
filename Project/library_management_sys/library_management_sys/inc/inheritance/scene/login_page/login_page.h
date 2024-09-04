// * �ļ���login_page.h
// * ���ߣ�������
// * ���ܣ����� LoginPage �ࡣ
#include <string>

#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_INHERITANCE_SCENE_LOGIN_PAGE_H_
#define LMS_INHERITANCE_SCENE_LOGIN_PAGE_H_
namespace library_management_sys {
// �涨��Ӧ�õ�¼ҳ��ķ�ʽ��ʾ����
//    PageUnitEx test_unit_ex;
//    LoginPage test_login_page(test_unit_ex);
class LoginPage : public SharedScene {
 public:
  LoginPage(PageUnitEx& pageunit_list_head);  // ���캯��
  // ���������������������档ʾ����
  //    test_scene.prepareScene();
  bool prepareScene();
  // ���û��������ƺ������ı�ʱ��ִ�С�ʾ����
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();
  // �������������ƥ�䣬�����棬�����¹���ĵ�ǰ��¼�û���Ϣ.
  // �����ƥ�䣬���ؼ٣���ʾ������Ϣ��
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // �����������
  bool getKeyboardInputState() { return true; }  // �����������

 private:
  // ���ڼ�¼�û����������
  std::wstring name_request_ = {};
  // ���ڼ�¼�û����������
  std::wstring password_request_ = {};
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_LOGIN_PAGE_H_