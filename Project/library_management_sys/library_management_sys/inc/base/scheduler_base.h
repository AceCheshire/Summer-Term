// * �ļ���scheduler_base.h
// * ���ߣ�������
// * ���ܣ����� Scheduler �ࡣ
#include <string>

#include "inc/app_const.h"
#include "inc/base/link_base.h"
#include "inc/base/mouse_base.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_BASE_SCHEDULER_BASE_H_
#define LMS_BASE_SCHEDULER_BASE_H_
namespace library_management_sys {
// ����������״̬����ʽ���ϲ�ͬ������ʾ����
//    Scheduler test_scheduler(0);
class Scheduler : public SharedPool {
 public:
  // ���캯��������Ϊʹ����ϣ�����Ƚ���ĳ����ı�š�
  Scheduler(unsigned short init_scene);
  // Ӧ�õ���Ҫ��������ʾ����
  //    Scheduler test_scheduler(test_init_scene);
  //    while (true) test_scheduler.generalSchedule();
  void generalSchedule();
  // ����������ʱ���ĳ�Ա active_scene_ �����Դ��л�������
  // �����Ա active_scene_ �������Ҽ��������ó����������档
  // ��һ������Ϊ��Ҫ��ת���ĳ�����ţ��ڶ�������Ϊ����ָ������������Ӹ�����
  bool generalSwitch(unsigned short scene_number, unsigned short check_mode);
  // ά����Ա button_list_
  // ��ͬʱ���ص������������˹��࣬�������������ʱ��ֹ�� ʾ����
  //    test_scheduler.appendScene(test_scene, 0);
  //    Link test_link("test_text", 0, 1 ,0);
  //    test_scheduler.appendLink(test_link);
  //    while (true) test_scheduler.generalSchedule();
  void appendLink(Link& new_link);
  // ά����Ա schedule_match_table_ ������������ѹ��صĳ�����ͻ��������Խ�磬
  // ����������ʱ��ֹ��ʾ����
  //    test_scheduler.appendScene(test_scene, 0);
  //    Link test_link("test_text", 0, 1, 0);
  //    test_scheduler.appendLink(test_link);
  //    while (true) test_scheduler.generalSchedule();
  void appendScene(Scene& new_scene, unsigned short target_pos);
  // ��ֹ��������
  void exit() { is_to_exit_ = true; }

 protected:
  // ���ܼ��̼�������롣����Ϊ����������ģʽ���ɳ���������
  // ע�⣺����������ܻᱻ������븲�ǡ�
  // ʾ����
  //    while (true) waitInput(true, true);
  void waitInput(bool is_keyboard_input_on, bool is_mouse_input_on);
  // Tab ����Ϊ���̰����������ѡ����Ļ�ϵ��ַ�����ѡ�е��ַ����������
  // ��ֻ���ܹ��������ַ����ᱻѡ�С�ѡ�к��»س���Ϊ������ַ�����
  // ��ΰ��� Tab ��������ѡ���˳���ǣ�
  // �� -> �����ı��е�һ�������������ַ��� -> �ڶ��� -> ...
  // ... -> ���һ�� -> �� -> ...
  // ʾ��:
  //    bool test_is_keyboard_input_on = true;
  //    if (test_is_keyboard_input_on) {
  //      if (kKeyDown(VK_TAB)) keyTab();
  //    }
  void keyTab();
  // ���������ַ������ݣ��� button_list_ ��ƥ���������������ӡ����ܹ�ƥ�䣬
  // ���ؽ��յ��ĵ�һ����Ч��������ת���룬���򷵻� -1 ��
  int findLink(const std::wstring& msg);
  // ���������������
  Mouse built_mouse_;
  // ���ڴ洢 Tab ��ѡ���ҳ�浥Ԫ
  PageUnitEx* current_tab_unit_ = NULL;
  // ������������״̬����Ϊ�����ı�ģʽ�ͷ������ı�ģʽ��
  bool is_inputting_info_ = false;
  // ��¼��ǰ����������ʵ�ֳ����Ķ�̬��
  unsigned short active_scene_;
  // ���ڼ�¼�ж��������ô˿���ʵ�ֳ����л���ִ��һ���жϺ��踴λΪ�١�
  bool is_to_break_ = false;
  // ���ڼ�¼�˳��������ô˿���ʵ����ֹ����
  bool is_to_exit_ = false;
  // ���ڹ������ӣ���Ϊ findLink() ��ƥ����Դ��
  Link* button_list_[scheduler::kMaxLinkNum] = {};
  // ��Ϊ�����б����ڹ��س�����ʵ�ֳ������ȡ�
  Scene* schedule_match_table_[scheduler::kMaxJumpNum] = {};
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCHEDULER_BASE_H_