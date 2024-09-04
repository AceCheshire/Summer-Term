// * 文件：mouse_base.h
// * 作者：麦天乐
// * 介绍：声明 Mouse 类。
#include <windows.h>

#include <string>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_MOUSE_BASE_H_
#define LMS_BASE_MOUSE_BASE_H_
namespace library_management_sys {
// Mouse 类实例记录鼠标停留处屏幕上显示的字符串，此外会监测鼠标左键是否被按下。
// 示例:
//    Mouse test_mouse;
class Mouse {
 public:
  // 构造函数会为所有的成员尝试赋初值。此外该构造函数会尝试将窗口转为预设的窗口大小。
  // 若应用权限不足，窗口转化会失败。
  Mouse();
  // 参数为挂载在场景下的拓展页面单元，即场景文本数据。
  // 如果鼠标左键按下，返回鼠标停留在的非空字符串，否则返回
  // mouse::kDefaultReturn 。使用者无需为函数调用手动释放空间。
  std::wstring hoverAndClick(PageUnitEx& source_text);

 protected:
  // 返回窗口特定坐标位置的宽字符，参数为指定的坐标。
  wchar_t readChar(COORD coord_pos);
  // 返回鼠标停留的字符串
  std::wstring readCursorChars();
  // 如果鼠标位置发生变化，重新绘制过去停留的和当前停留的字符串（不高亮/高亮）。
  // 同时，更新成员 read_str_ 。参数包括当前场景的拓展页面单元与
  // readCursorChars() 的返回值。
  void popLastStr(PageUnitEx& source_text, const std::wstring& new_string);
  // POINT 类型的鼠标停留坐标
  POINT point_pos_;
  // COORD 类型的鼠标停留坐标，与 point_pos_ 等价。
  COORD coord_pos_;
  // 控制台字体信息，注意单次使用期间改变字体大小是不被允许的。
  CONSOLE_FONT_INFO console_font_;
  // 鼠标停留字符串
  std::wstring read_str_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_MOUSE_BASE_H_