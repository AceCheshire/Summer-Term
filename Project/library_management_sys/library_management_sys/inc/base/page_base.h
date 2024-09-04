// * �ļ���page_base.h
// * ���ߣ�������
// * ���ܣ����� PageUnit ��PageUnitEx ��Page �ࡣ
#include <windows.h>

#include <string>

#include <inc/app_const.h>
#ifndef LMS_BASE_PAGE_BASE_H_
#define LMS_BASE_PAGE_BASE_H_
namespace library_management_sys {
// ��¼�����ı�����Ϣ��ʾ����
//    PageUnit test_unit;
//    test_unit.pos_ = {0, 0};
//    test_unit.color_ = page::GROUND_DEFAULT;
//    test_unit.can_be_highlighted_ = false;
//    test_unit.text_ = "test_content";
class PageUnit {
 public:
  // ��Ҫʹ�������п��������ֵ��
  // x ��Χ��[0, min (kClassicWidth, �û����ڿ��) - 1]��
  // y ��Χ��[0, min (kClassicHeight, �û����ڸ߶�) - 1]��
  COORD pos_ = {0, 0};
  WORD color_ = page::GROUND_DEFAULT;
  bool can_be_highlighted_ = false;  // �����Ƿ����� highlight() ������
  std::wstring text_ = L" ";
};
// �ṩ����չ��������������ʽ����ҳ�浥Ԫ�飬��Ҫ���� deleteAll() �����ͷš�
// ʾ����
//    PageUnitEx test_pageunit_ex; PageUnit test_unit_1, test_unit_2.
//    test_pageunit_ex.append(test_unit_1);
//    test_pageunit_ex.append(test_unit_2);
//    test_pageunit_ex.deleteAll();
class PageUnitEx : public PageUnit {
 public:
  // ע�⣺ͨ��������������� append() ��������չҳ�浥Ԫ this_unit_
  // ��Աδ����ֵ�� �÷������� new �ؼ��֣�Ӧ�õ��� deleteAll() �����ͷš�
  // ʾ����
  //    PageUnitEx test_pageunit_ex;
  //    test_pageunit_ex.append(new PageUnit);
  void append(PageUnit& pageunit_list_end);
  // ����ӵ��÷�������չҳ�浥Ԫ��ʼ��δ��ƥ��ÿ��ַ���������һ����ָ�롣
  // ���򷵻�ƥ��ĵ�һ��ҳ�浥Ԫָ�롣
  // ʾ����
  //    PageUnit* test_pointer = test_pageunit_ex.findByText(L"Bingo");
  //    PageUnit test_unit_result = *test_ex_pointer;
  PageUnit* findByText(const std::wstring& text_);
  // ����ӵ��÷�������չҳ�浥Ԫ��ʼ��δ��ƥ��ÿ��ַ���������β����Ԫ��
  // ���򷵻�ƥ��ĵ�һ��ҳ�浥Ԫ���á�
  // ʾ����
  //    PageUnit test_finding = test_head[L"Bingo"];
  PageUnit& operator[](const std::wstring& index);
  PageUnitEx* getNext() { return next_unit_; }
  // ���ɾ������չҳ�浥Ԫ���÷��� Page ��ע�͡�
  void deleteAll();

 private:
  PageUnitEx* next_unit_ = NULL;
};
// ��̬�࣬������һЩ���ڸ�����ʾ�ı��ĳ�������
class Page {
 public:
  // ����һ��ҳ�浥Ԫ����������ɫ������Ϊ BACKGROUND_INTENSITY ��
  // ��������ص�ҳ�浥Ԫ�� can_be_highlighted_ ��ԱΪ�٣��ⲻ����Ч��
  static PageUnit highlight(PageUnit& source_pageunit);
  // �������Ϊ�棬�����ؿ���̨��꣬������ʾ��ꡣ
  static void hideCursor(bool is_to_hide_cursor);
  // ������ı�����ɫ��Ϊ page::GROUND_DEFAULT ���ɹ�ʱ�����档
  static bool returnDefault();
  // ���ҳ�浥Ԫ�ɹ���ʾ�������档�÷����Ὣ����ı���ɫ����Ϊ
  // page::GROUND_DEFAULT ��
  static bool pointPaint(PageUnit& request_unit);
  // pointPaint(PageUnit& request_unit) �����ı���Ա�汾����������ɫ����
  static bool pointPaint(COORD request_pos, WORD request_color);
  // pointPaint(PageUnit& request_unit) �ĳ�Ա�汾��������ɫ����
  static bool pointPaint(COORD request_pos, WORD request_color,
                         const std::wstring& request_text);
  // pointPaint(COORD request_pos, WORD request_color) �ĳ�Ա�汾��
  static bool pointPaint(short x, short y, WORD request_color);
  // pointPaint(COORD request_pos, WORD request_color, const std::wstring&
  // request_text) �ĳ�Ա�汾��
  static bool pointPaint(short x, short y, WORD request_color,
                         const std::wstring& request_text);

 private:
  Page();
};
}  // namespace library_management_sys
#endif  // LMS_BASE_PAGE_BASE_H_