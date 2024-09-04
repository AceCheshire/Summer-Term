// * 文件：mouse_base.cc
// * 作者：麦天乐
// * 介绍：定义 Mouse 类。
#include "inc/base/mouse_base.h"

#include <windows.h>

#include <string>

#include "inc/base/page_base.h"
namespace library_management_sys {
Mouse::Mouse() {
  point_pos_.x = point_pos_.y = 0;
  coord_pos_.X = coord_pos_.Y = 0;
  GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &console_font_);
  MoveWindow(GetConsoleWindow(), 0, 0, mouse::kClassicWidth,
             mouse::kClassicHeight, TRUE);  // 改变窗口大小
}

std::wstring Mouse::hoverAndClick(PageUnitEx& source_text) {
  int counter = mouse::kDetectGroupTimes;  // 定义连续监测计数器
  while (counter--) {
    Sleep(mouse::kDetectInterval);  // 调整函数运行时间
    // 第一步：获取鼠标位置
    GetCursorPos(&point_pos_);  // point_pos_ -> 鼠标屏幕坐标
    ScreenToClient(GetConsoleWindow(),
                   &point_pos_);  // point_pos_ -> 客户端坐标
    // point_pos_.x -> coord_pos_.X
    // 以下公式等价于:
    //    console_font_.dwFontSize.X = console_font_.dwFontSize.Y / kFontRatio;
    //    coord_pos_.x = point_pos_.x / console_font_.dwFontSize.X.
    short x =
        (short)(mouse::kFontRatio * point_pos_.x / console_font_.dwFontSize.Y);
    // point_pos_.y -> coord_pos_.Y
    // 以下公式等价于:
    //    short rowInterval = console_font_.dwFontSize.Y * kRowInterval;
    //    coord_pos.y = point_pos_.y / rowInterval.
    short y = (short)((double)point_pos_.y /
                      (console_font_.dwFontSize.Y * mouse::kRowInterval));
    coord_pos_ = {x, y};
    // 第二步：获取鼠标停留的字符串，根据是否变化进行数据更新和显示更新
    std::wstring ret = readCursorChars();
    if (ret != read_str_) popLastStr(source_text, ret);
    // 第三步：检测鼠标输入
    if (kKeyDown(VK_LBUTTON) && read_str_.length()) return read_str_;
  }
  return mouse::kDefaultReturn;  // 如果没有提前结束，则返回默认值
}

wchar_t Mouse::readChar(COORD coord_pos) {
  wchar_t ret;          // 记录获得的宽字符
  DWORD actual_length;  // 记录获得的字符数
  return ((ReadConsoleOutputCharacterW(GetStdHandle(STD_OUTPUT_HANDLE), &ret, 1,
                                       coord_pos, &actual_length))
              ? ret     // 读取成功
              : L' ');  // 读取失败
}

std::wstring Mouse::readCursorChars() {
  COORD left_float = coord_pos_;   // 左移浮标
  COORD right_float = coord_pos_;  // 右移浮标
  right_float.X++;                 // 错开左右浮标
  std::wstring ret;                // 要返回的宽字符串结果
  wchar_t read_char;               // 存储 readChar() 的返回值
  // 获取屏幕缓冲区信息
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  // 移动右移浮标，完善要返回的宽字符串
  while (
      // 获取字符并过滤无效字符：' '，'\t'，'\n'，'\0'
      ((read_char = readChar(right_float)) != L' ') && (read_char != L'\t') &&
      (read_char != L'\n') && (read_char != L'\0') &&
      // 保证右移浮标不会越过窗口边界
      (right_float.X <= csbi.srWindow.Right - csbi.srWindow.Left)) {
    ret.push_back(read_char);
    right_float.X++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), right_float);
  }
  // 移动左移浮标，完善要返回的宽字符串
  while (
      // 获取字符并过滤无效字符：' '，'\t'，'\n'，'\0'
      ((read_char = readChar(left_float)) != L' ') && (read_char != L'\t') &&
      (read_char != L'\n') && (read_char != L'\0') &&
      // 保证左移浮标不会越过窗口边界
      (left_float.X >= 0)) {
    ret = read_char + ret;
    left_float.X--;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), left_float);
  }
  return ret;
}

void Mouse::popLastStr(PageUnitEx& source_text,
                       const std::wstring& new_string) {
  PageUnit* ret = NULL;
  if (read_str_.length()) {  // 检查函数参数
    if ((ret = source_text.findByText(read_str_)) != NULL) {  // 寻找场景文本
      Page::pointPaint(*ret);                                 // 去除高光
    }
  }
  ret = NULL;
  if (new_string.length()) {  // 检查函数参数
    if ((ret = source_text.findByText(new_string)) != NULL) {  // 寻找场景文本
      PageUnit processed_ret = Page::highlight(*ret);          // 高光处理
      Page::pointPaint(processed_ret);
    }
  }
  read_str_ = new_string;  // 更新 read_str_
}
}  // namespace library_management_sys