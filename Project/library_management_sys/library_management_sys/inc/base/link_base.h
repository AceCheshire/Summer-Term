// * �ļ���link_base.h
// * ���ߣ�������
// * ���ܣ����� Link �ࡣ
#include <string>
#ifndef LMS_BASE_LINK_BASE_H_
#define LMS_BASE_LINK_BASE_H_
namespace library_management_sys {
// Link �����ӣ���ť���ĳ����������� Scene ʵ������Ҫ������ Scheduler ��
// ʾ����
//    Scheduler test_scheduler;
//    std::wstring test_str;
// 	  unsigned short test_this_scene_number, test_next_scene_number;
//    unsigned short test_mode;
//    Link test_link(test_str, test_this_scene_number,
//                   test_next_scene_number, test_mode);
//    test_scheduler.appendLink(test_link);
class Link {
 public:
  // ����ʼ���б�Ĺ��캯��
  Link(const std::wstring& symbol_str, unsigned short this_scene_number,
       unsigned short next_scene_number, unsigned short check_mode);
  // ���صĹ��캯���������ɿ��ַ�����Ϊ���ַ�ָ�롣�������ָ�룬symbol_str ��Ϊ
  // mouse::kDefaultReturn ��
  Link(const wchar_t* symbol_str, unsigned short this_scene_number,
       unsigned short next_scene_number, unsigned short check_mode);
  // �÷����Ĳ�����ѡ�е���Ļ�ַ����͵�ǰ�ĳ��������� Scheduler
  // �ı�ţ������������������ֲ�ͬ�����ӡ�����ǰ����ƥ�䣬�᷵��
  // ��һ�����ı�ź����ӵ�����ָ��ϳɵı��룬���򷵻� -1 ��
  // ͨ���ڲ��˽ⳡ����Ӧ�ı�ŵ��˽����ӵı�ʶʱ���ã��������ǣ���ʾ��:
  //    constexpr int kTestMaxNumber = 256;
  //    std::wstring test_symbol_string;
  //    unsigned short test_this_scene_number = 0;
  //    Link test_link_list[kTestMaxNumber];
  //    for (int i = 0; i < kTestMaxNumber; i++) {
  //      if (stringToSequence(test_symbol_string,
  //                           test_this_scene_number) != -1)
  //        std::wcout << "There exists valid link";
  //    }
  int stringToSequence(const std::wstring& request_str,
                       unsigned short this_scene_number) const;

 protected:
  // ���ӵı�ʶ�ı����û�ͨ��������������ӡ�
  std::wstring symbol_str_;
  // ��ǰ�����ĵ��������ر��
  unsigned short this_scene_number_;
  // ��һ�����ĵ��������ر��
  unsigned short next_scene_number_;
  // �������ֲ�ͬ���ӱ������� Scene::checkLink() ����Ӧ��ʽ��
  // ��ֵΪ����Ϊ������ checkLink() ��
  unsigned short check_mode_ = 0;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_LINK_BASE_H_