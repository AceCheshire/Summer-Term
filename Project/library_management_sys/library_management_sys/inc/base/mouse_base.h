// * �ļ���mouse_base.h
// * ���ߣ�������
// * ���ܣ����� Mouse �ࡣ
#include <windows.h>

#include <string>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_MOUSE_BASE_H_
#define LMS_BASE_MOUSE_BASE_H_
namespace library_management_sys {
// Mouse ��ʵ����¼���ͣ������Ļ����ʾ���ַ�������������������Ƿ񱻰��¡�
// ʾ��:
//    Mouse test_mouse;
class Mouse {
 public:
  // ���캯����Ϊ���еĳ�Ա���Ը���ֵ������ù��캯���᳢�Խ�����תΪԤ��Ĵ��ڴ�С��
  // ��Ӧ��Ȩ�޲��㣬����ת����ʧ�ܡ�
  Mouse();
  // ����Ϊ�����ڳ����µ���չҳ�浥Ԫ���������ı����ݡ�
  // ������������£��������ͣ���ڵķǿ��ַ��������򷵻�
  // mouse::kDefaultReturn ��ʹ��������Ϊ���������ֶ��ͷſռ䡣
  std::wstring hoverAndClick(PageUnitEx& source_text);

 protected:
  // ���ش����ض�����λ�õĿ��ַ�������Ϊָ�������ꡣ
  wchar_t readChar(COORD coord_pos);
  // �������ͣ�����ַ���
  std::wstring readCursorChars();
  // ������λ�÷����仯�����»��ƹ�ȥͣ���ĺ͵�ǰͣ�����ַ�����������/��������
  // ͬʱ�����³�Ա read_str_ ������������ǰ��������չҳ�浥Ԫ��
  // readCursorChars() �ķ���ֵ��
  void popLastStr(PageUnitEx& source_text, const std::wstring& new_string);
  // POINT ���͵����ͣ������
  POINT point_pos_;
  // COORD ���͵����ͣ�����꣬�� point_pos_ �ȼۡ�
  COORD coord_pos_;
  // ����̨������Ϣ��ע�ⵥ��ʹ���ڼ�ı������С�ǲ�������ġ�
  CONSOLE_FONT_INFO console_font_;
  // ���ͣ���ַ���
  std::wstring read_str_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_MOUSE_BASE_H_