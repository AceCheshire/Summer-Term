// * 文件：page_base.h
// * 作者：麦天乐
// * 介绍：声明 PageUnit ，PageUnitEx ，Page 类。
#include <windows.h>

#include <string>

#include <inc/app_const.h>
#ifndef LMS_BASE_PAGE_BASE_H_
#define LMS_BASE_PAGE_BASE_H_
namespace library_management_sys {
// 记录连续文本的信息。示例：
//    PageUnit test_unit;
//    test_unit.pos_ = {0, 0};
//    test_unit.color_ = page::GROUND_DEFAULT;
//    test_unit.can_be_highlighted_ = false;
//    test_unit.text_ = "test_content";
class PageUnit {
 public:
  // 需要使用者自行控制坐标的值。
  // x 范围：[0, min (kClassicWidth, 用户窗口宽度) - 1]；
  // y 范围：[0, min (kClassicHeight, 用户窗口高度) - 1]。
  COORD pos_ = {0, 0};
  WORD color_ = page::GROUND_DEFAULT;
  bool can_be_highlighted_ = false;  // 标明是否允许被 highlight() 高亮。
  std::wstring text_ = L" ";
};
// 提供了拓展方法来以链表形式管理页面单元组，需要调用 deleteAll() 进行释放。
// 示例：
//    PageUnitEx test_pageunit_ex; PageUnit test_unit_1, test_unit_2.
//    test_pageunit_ex.append(test_unit_1);
//    test_pageunit_ex.append(test_unit_2);
//    test_pageunit_ex.deleteAll();
class PageUnitEx : public PageUnit {
 public:
  // 注意：通常情况下用来调用 append() 方法的拓展页面单元 this_unit_
  // 成员未被赋值。 该方法内蕴 new 关键字，应该调用 deleteAll() 进行释放。
  // 示例：
  //    PageUnitEx test_pageunit_ex;
  //    test_pageunit_ex.append(new PageUnit);
  void append(PageUnit& pageunit_list_end);
  // 如果从调用方法的拓展页面单元开始均未能匹配该宽字符串，返回一个空指针。
  // 否则返回匹配的第一个页面单元指针。
  // 示例：
  //    PageUnit* test_pointer = test_pageunit_ex.findByText(L"Bingo");
  //    PageUnit test_unit_result = *test_ex_pointer;
  PageUnit* findByText(const std::wstring& text_);
  // 如果从调用方法的拓展页面单元开始均未能匹配该宽字符串，返回尾部单元。
  // 否则返回匹配的第一个页面单元引用。
  // 示例：
  //    PageUnit test_finding = test_head[L"Bingo"];
  PageUnit& operator[](const std::wstring& index);
  PageUnitEx* getNext() { return next_unit_; }
  // 向后删除该拓展页面单元，用法见 Page 类注释。
  void deleteAll();

 private:
  PageUnitEx* next_unit_ = NULL;
};
// 静态类，集成了一些用于更改显示文本的常见方法
class Page {
 public:
  // 返回一个页面单元拷贝，其颜色被更改为 BACKGROUND_INTENSITY 。
  // 如果将返回的页面单元其 can_be_highlighted_ 成员为假，这不会起效。
  static PageUnit highlight(PageUnit& source_pageunit);
  // 如果参数为真，将隐藏控制台光标，否则显示光标。
  static void hideCursor(bool is_to_hide_cursor);
  // 将输出文本的颜色置为 page::GROUND_DEFAULT ，成功时返回真。
  static bool returnDefault();
  // 如果页面单元成功显示，返回真。该方法会将输出文本颜色重置为
  // page::GROUND_DEFAULT 。
  static bool pointPaint(PageUnit& request_unit);
  // pointPaint(PageUnit& request_unit) 的无文本成员版本（不重置颜色）。
  static bool pointPaint(COORD request_pos, WORD request_color);
  // pointPaint(PageUnit& request_unit) 的成员版本（重置颜色）。
  static bool pointPaint(COORD request_pos, WORD request_color,
                         const std::wstring& request_text);
  // pointPaint(COORD request_pos, WORD request_color) 的成员版本。
  static bool pointPaint(short x, short y, WORD request_color);
  // pointPaint(COORD request_pos, WORD request_color, const std::wstring&
  // request_text) 的成员版本。
  static bool pointPaint(short x, short y, WORD request_color,
                         const std::wstring& request_text);

 private:
  Page();
};
}  // namespace library_management_sys
#endif  // LMS_BASE_PAGE_BASE_H_