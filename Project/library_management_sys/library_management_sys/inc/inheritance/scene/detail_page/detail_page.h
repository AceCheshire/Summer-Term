// * �ļ���detail_page.h
// * ���ߣ�������
// * ���ܣ����� DetailPage �ࡣ
#include <windows.h>

#include <string>

#include "inc/base/book_base.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/user_base.h"
#ifndef LMS_INHERITANCE_SCENE_DETAIL_PAGE_H_
#define LMS_INHERITANCE_SCENE_DETAIL_PAGE_H_
namespace library_management_sys {
// �涨��Ӧ������ҳ��ķ�ʽ��ʾ����
//    PageUnitEx test_unit_ex;
//    DetailPage test_detail_page(test_unit_ex_1, test_unit_ex_2,
//                                test_unit_ex_3, test_unit_ex_4, 
//                                test_unit_ex_5, test_unit_ex_6);
class DetailPage : public SharedScene {
 public:
  // �������ֳ����ı���������ʾ�û���Ϣ��ͼ����Ϣ����Ϊ����Ա����������Ա�޸ĺ���ͨ�û��鿴
  // ������������д���ĵ�һ�ֳ����ı���������ʼ������ Scene ��
  DetailPage(PageUnitEx& admin_add_user, PageUnitEx& admin_modify_user,
             PageUnitEx& guest_read_user, PageUnitEx& admin_add_book,
             PageUnitEx& admin_modify_book, PageUnitEx& guest_read_book);  // ���캯��
  // ���������������������档ʾ����
  //    test_scene.prepareScene();
  bool prepareScene();
  // ���û������û���ͼ������ʱ��ִ�С�ʾ����
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();
  // ����ʵ�ֽ�����黹���������޸���ȡ���޸ġ�ֻ�е�����ؼ��Ż᷵���档
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // �����������
  bool getKeyboardInputState() { return true; }  // �����������

 private:
  // �����޸İ�������Ӧ�������޸��ļ��У�������ʷ��¼��
  void modifyAction();
  // ����������������Ӧ�������½��ļ��У�������ʷ��¼��
  void addAction();
  // ���½��İ�������Ӧ����������ͼ��״̬��������ʷ��¼��
  void borrowAction();
  // ���¹黹��������Ӧ����������ͼ��״̬��������ʷ��¼��
  void returnAction();
  // ������������ʾͼ����û���Ϣ����Ӧ����
  void displayInfo();
  // �ҵ������ı���λ�ã�����ѡ��ָ���λ�ò���ʾ��
  void pointerDisplay(const std::wstring& match_text);
  // ��ʾͼ����û����ݣ����Զ��жϣ�
  bool dataDisplay();
  // ��ʾͼ����
  void descriptionDisplay();
  // ��ʾͼ����û��Ľ�����ʷ�����Զ��жϣ�
  bool historyDisplay();
  // Ϊ pointPaint() ����������꣬����Ϊ���������ݡ�
  COORD getInfoPosition(const std::wstring& guidance_text);
  // ��¼����Ա�����û�ҳ��ĳ����ı�
  PageUnitEx* pageunit_list_head_1_;
  // ��¼����Ա�޸��û�ҳ��ĳ����ı�
  PageUnitEx* pageunit_list_head_2_;
  // ��¼��ͨ�û��鿴�û�ҳ��ĳ����ı�
  PageUnitEx* pageunit_list_head_3_;
  // ��¼����Ա����ͼ��ҳ��ĳ����ı�
  PageUnitEx* pageunit_list_head_4_;
  // ��¼����Ա�޸�ͼ��ҳ��ĳ����ı�
  PageUnitEx* pageunit_list_head_5_;
  // ��¼��ͨ�û��鿴ͼ��ҳ��ĳ����ı�
  PageUnitEx* pageunit_list_head_6_;
  // ��¼�û�ѡ����������Ӧ������ָ��
  int option_ = 0;
  // ��¼�û�ѡ���������
  std::wstring option_text_;
  // ��¼�û�������ʷ�ı��
  int history_iterator = 0;
  // ��¼�û�ϣ�����ĵ�����
  std::wstring password_request_;
  // ��ʱ�����û��޸Ļ��½����û���Ϣ
  User temp_user_;
  // ��ʱ�����û��޸Ļ��½���ͼ����Ϣ
  Book temp_book_;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_DETAIL_PAGE_H_