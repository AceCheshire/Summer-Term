// * �ļ���scene_base.h
// * ���ߣ�������
// * ���ܣ����� Scene �ࣨ���ࣩ��SharedScene �ࣨ�����ࣩ�� SharedPool �ࡣ
#include "inc/base/book_base.h"
#include "inc/base/page_base.h"
#include "inc/base/user_base.h"
#ifndef LMS_BASE_SCENE_BASE_H_
#define LMS_BASE_SCENE_BASE_H_
namespace library_management_sys {
// ��������Ԫ�ص�����
class Scene {
 public:
  // ���๹�캯���������๹�캯��ʾ��:
  //    TestScene::TestScene(PageUnitEx& pageunit_list_head)
  //        : Scene(pageunit_list_head) {}
  Scene(PageUnitEx& pageunit_list_head);
  void setPageUnitList(PageUnitEx& pageunit_list) {
    pageunit_list_head_ = &pageunit_list;
  }
  PageUnitEx* getPageUnitList() const { return pageunit_list_head_; }
  // ������չҳ�浥Ԫ��Ա������˳��������ʾ����Ļ�ϡ�
  void layoutText();
  // ����ʱֻ�����û�����س����˸��Լ������ַ���
  // 1���ո��Ƿ������ɲ��� space ������
  // 2������ 0~9 ���Ƿ������ɲ��� num ������
  // 3��Ӣ���ַ������� a~z ��A~Z���Ƿ������ɲ��� en ������
  // 4�������ַ������� scene::kSpecialChars�������ã����Ƿ������ɲ��� sp ������
  // 5����ǰ���Ե��ַ���Ĭ��Ϊ �� chs �������� scene::kAnsiStart ��
  //    scene::kAnsiEnd ���Ƿ������ɲ��� ansi ������
  // ע�⣺���»س��������Ƿ��������ַ��������������е����롣���ַ����˸�ʧЧ��
  // �ַ��������趨ֵ�� scene::kAdviceLength ��ʱ����ʧЧ��
  // ����������ַ��������� fill_char ָ�������ַ���������� std::wcin ��
  std::wstring inputLine(bool space, bool num, bool en, bool sp, bool ansi,
                         const wchar_t& fill_char = L'\0');
  // �����������������ĳ��󷽷���ͨ������ layoutText() ������
  virtual bool prepareScene() = 0;
  // ��������������������󷽷���ͨ���ڰ��� Insert ����ִ�С�
  virtual void inputInfo() = 0;
  // ��������ʵ�ֳ������ɵ�ͨ�÷������÷���Ҳ����������������ĳ�����Ӧ��
  // �������ת����һ�������������棬����ʵ�ֳ�����Ĺ��ɡ�
  // �����Ҫͣ���ڱ����������ؼ٣���ʱ�������������ڲ���Ӧ��
  virtual bool checkLink(unsigned short check_mode) = 0;
  // ���ڻ�ȡ�ض��������������ģʽ��ͨ�ú���
  virtual bool getMouseInputState() = 0;
  // ���ڻ�ȡ�ض������¼�������ģʽ��ͨ�ú���
  virtual bool getKeyboardInputState() = 0;

 protected:
  // ���ڴ洢�����ı���Ϣ
  PageUnitEx* pageunit_list_head_;
};
// ���ڴ洢����֮����Ҫ�������Ϣ�������㳡���������չ��
class SharedPool {
 public:
  // ���ڶ�д��ǰ��¼���û�����Ϣ
  static User current_user_;
  // ���ڶ�д��ǰ������û�����Ϣ
  static User searching_user_;
  // ���ڶ�д��ǰ�����ͼ�����Ϣ
  static Book searching_book_;
  // ���ڼ�¼�û��Ŀ糡��ѡ��
  static int shared_task_;
};
// ����ʵ�ֲ�ͬ���������Ϣ���ݡ�
class SharedScene : public Scene, public SharedPool {
 public:
  SharedScene(PageUnitEx& pageunit_list_head);
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCENE_BASE_H_