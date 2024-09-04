// * �ļ���search_page.h
// * ���ߣ�������
// * ���ܣ����� SearchPage �ࡣ
#include <string>

#include "inc/app_const.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_INHERITANCE_SCENE_SEARCH_PAGE_H_
#define LMS_INHERITANCE_SCENE_SEARCH_PAGE_H_
namespace library_management_sys {
// �涨��Ӧ������ҳ��ķ�ʽ��ʾ����
//    PageUnitEx test_unit_ex;
//    SearchPage test_search_page(test_unit_ex);
class SearchPage : public SharedScene {
 public:
  SearchPage(PageUnitEx& pageunit_list_head);  // ���캯��
  // ���������������������档ʾ����
  //    test_scene.prepareScene();
  bool prepareScene();
  // ���û������û���ͼ������ʱ��ִ�С�ʾ����
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();
  // �Բ�ͬ������ʵ�ֲ�ͬ����Ӧ
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // �����������
  bool getKeyboardInputState() { return true; }  // �����������

 private:
  // ����ɾ���û���ͼ�顣�÷�������ɾ�����������еļ�¼���û���ͼ���ļ��С�
  // ����ΪҪɾ�����û���ͼ�����ơ�
  void del(const std::wstring& searching_object);
  // �������������û���������ƣ���������������ƶ�˳������Ա result_ ��
  void search();
  // ����ƥ���ַ��ĸ�����Ȼ�󷵻����ƶȡ�
  short getSimilarity(const std::wstring& request,
                       const std::wstring& finding);
  // ��ʾ����������÷������Ƿ��ؼ٣�
  bool searchDisplay();
  // ��ʾѡ��ָ��
  void pointerDisplay();
  // ���ڼ�¼�û�����
  std::wstring request_;
  // ���ڼ�¼�������
  std::wstring result_[search_page::kMaxSearchNum] = {};
  // ���ڼ�¼���������Ӧ�����ƶ�
  double similarity_value_[search_page::kMaxSearchNum] = {};
  // ���ڼ�¼ѡ��ָ��ָ������������ţ��� 1 ��ʼ��
  int iterator_ = 0;
  // ���ڼ�¼��Ч�������������
  unsigned short search_size_ = 0;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_SEARCH_PAGE_H_