// * �ļ���mouse_base.cc
// * ���ߣ�������
// * ���ܣ����� Mouse �ࡣ
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
             mouse::kClassicHeight, TRUE);  // �ı䴰�ڴ�С
}

std::wstring Mouse::hoverAndClick(PageUnitEx& source_text) {
  int counter = mouse::kDetectGroupTimes;  // ����������������
  while (counter--) {
    Sleep(mouse::kDetectInterval);  // ������������ʱ��
    // ��һ������ȡ���λ��
    GetCursorPos(&point_pos_);  // point_pos_ -> �����Ļ����
    ScreenToClient(GetConsoleWindow(),
                   &point_pos_);  // point_pos_ -> �ͻ�������
    // point_pos_.x -> coord_pos_.X
    // ���¹�ʽ�ȼ���:
    //    console_font_.dwFontSize.X = console_font_.dwFontSize.Y / kFontRatio;
    //    coord_pos_.x = point_pos_.x / console_font_.dwFontSize.X.
    short x =
        (short)(mouse::kFontRatio * point_pos_.x / console_font_.dwFontSize.Y);
    // point_pos_.y -> coord_pos_.Y
    // ���¹�ʽ�ȼ���:
    //    short rowInterval = console_font_.dwFontSize.Y * kRowInterval;
    //    coord_pos.y = point_pos_.y / rowInterval.
    short y = (short)((double)point_pos_.y /
                      (console_font_.dwFontSize.Y * mouse::kRowInterval));
    coord_pos_ = {x, y};
    // �ڶ�������ȡ���ͣ�����ַ����������Ƿ�仯�������ݸ��º���ʾ����
    std::wstring ret = readCursorChars();
    if (ret != read_str_) popLastStr(source_text, ret);
    // ������������������
    if (kKeyDown(VK_LBUTTON) && read_str_.length()) return read_str_;
  }
  return mouse::kDefaultReturn;  // ���û����ǰ�������򷵻�Ĭ��ֵ
}

wchar_t Mouse::readChar(COORD coord_pos) {
  wchar_t ret;          // ��¼��õĿ��ַ�
  DWORD actual_length;  // ��¼��õ��ַ���
  return ((ReadConsoleOutputCharacterW(GetStdHandle(STD_OUTPUT_HANDLE), &ret, 1,
                                       coord_pos, &actual_length))
              ? ret     // ��ȡ�ɹ�
              : L' ');  // ��ȡʧ��
}

std::wstring Mouse::readCursorChars() {
  COORD left_float = coord_pos_;   // ���Ƹ���
  COORD right_float = coord_pos_;  // ���Ƹ���
  right_float.X++;                 // �����Ҹ���
  std::wstring ret;                // Ҫ���صĿ��ַ������
  wchar_t read_char;               // �洢 readChar() �ķ���ֵ
  // ��ȡ��Ļ��������Ϣ
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  // �ƶ����Ƹ��꣬����Ҫ���صĿ��ַ���
  while (
      // ��ȡ�ַ���������Ч�ַ���' '��'\t'��'\n'��'\0'
      ((read_char = readChar(right_float)) != L' ') && (read_char != L'\t') &&
      (read_char != L'\n') && (read_char != L'\0') &&
      // ��֤���Ƹ��겻��Խ�����ڱ߽�
      (right_float.X <= csbi.srWindow.Right - csbi.srWindow.Left)) {
    ret.push_back(read_char);
    right_float.X++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), right_float);
  }
  // �ƶ����Ƹ��꣬����Ҫ���صĿ��ַ���
  while (
      // ��ȡ�ַ���������Ч�ַ���' '��'\t'��'\n'��'\0'
      ((read_char = readChar(left_float)) != L' ') && (read_char != L'\t') &&
      (read_char != L'\n') && (read_char != L'\0') &&
      // ��֤���Ƹ��겻��Խ�����ڱ߽�
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
  if (read_str_.length()) {  // ��麯������
    if ((ret = source_text.findByText(read_str_)) != NULL) {  // Ѱ�ҳ����ı�
      Page::pointPaint(*ret);                                 // ȥ���߹�
    }
  }
  ret = NULL;
  if (new_string.length()) {  // ��麯������
    if ((ret = source_text.findByText(new_string)) != NULL) {  // Ѱ�ҳ����ı�
      PageUnit processed_ret = Page::highlight(*ret);          // �߹⴦��
      Page::pointPaint(processed_ret);
    }
  }
  read_str_ = new_string;  // ���� read_str_
}
}  // namespace library_management_sys