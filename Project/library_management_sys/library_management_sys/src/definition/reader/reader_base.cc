// * 文件：reader_base.cc
// * 作者：麦天乐
// * 介绍：定义 Reader 类。
#include "inc/base/reader_base.h"

#include <windows.h>

#include <algorithm>
#include <fstream>
#include <string>

#include "inc/app_const.h"
namespace library_management_sys {
bool Reader::readForPointPaint(PageUnitEx& pageunit_list_head,
                               const std::wstring& file_name) {
  std::wifstream input_file(file_name);
  input_file.imbue(std::locale("chs"));
  if (!input_file.is_open()) {  // 检查文件状态
    return false;
  } else {
    std::wstring tmp_line;
    while (getline(input_file, tmp_line)) {  // 获取每一行的文本
      // 示例：123(.txt)->123(short)
      // 在此示例下以下代码等价于：
      // 100 * (L'1' - L'0') + 10 * (L'2' - L'0') + (L'3' - L'0')
      short tmp_coord_x = tmp_line[reader::kXBase] * 100 +
                          tmp_line[reader::kXBase + 1] * 10 +
                          tmp_line[reader::kXBase + 2] - L'0' * 111;
      // tmp_coord_y 与 tmp_coord_x 相似
      short tmp_coord_y = tmp_line[reader::kYBase] * 100 +
                          tmp_line[reader::kYBase + 1] * 10 +
                          tmp_line[reader::kYBase + 2] - L'0' * 111;
      // 前两位为背景色取为 WORD 高位，后两位为前景色取为 WORD 低位。
      // 00(.txt) ── 0x00__ ──┐
      // 07(.txt) ── 0x__07 ──┴── 0x0007(WORD)(page::GROUND_DEFAULT)
      WORD tmp_color = (((tmp_line[reader::kColorBase] * 10 +
                          tmp_line[reader::kColorBase + 1] - 48 * 11) &
                         0x0F)
                        << 4) +
                       ((tmp_line[reader::kColorBase + 2] * 10 +
                         tmp_line[reader::kColorBase + 3] - 48 * 11) &
                        0x0F);
      COORD tmp_coord = {tmp_coord_x, tmp_coord_y};  // 获得坐标
      bool tmp_highlight_ability =
          tmp_line[reader::kHighlightBase] - L'0';  // 获得能否高亮
      std::wstring tmp_str = tmp_line.substr(reader::kStrBase);  // 获得文本
      PageUnit tmp_page_unit = {tmp_coord, tmp_color, tmp_highlight_ability,
                                tmp_str};        // 组合为 PageUnit 对象
      pageunit_list_head.append(tmp_page_unit);  // 插入链表尾部
    }
    input_file.close();
    return true;
  }
}

bool Reader::readForLogin(const std::wstring& name,
                          const std::wstring& password) {
  std::wifstream input_file(kUserPasswordPath(name));
  if (!input_file.is_open()) {  // 检查文件状态
    return false;
  } else {
    std::wstring tmp_line;
    getline(input_file, tmp_line);  // 获取文件第一行
    input_file.close();
    return (tmp_line.length() && tmp_line == password) ? true : false;
  }
}

bool Reader::readFileLine(const std::wstring& file_name,
                          unsigned int row_number, std::wstring& destination) {
  std::wifstream input_file(file_name);
  int counter = row_number;     // 设置重复次数
  if (!input_file.is_open()) {  // 检查文件状态
    return false;
  } else {
    while (counter--) {  // 正常读取则 counter 最终为 -1
      if (!getline(input_file, destination)) break;  // EOF 会提前跳出
    }
    input_file.close();
    return (counter > -1) ? false : true;
  }
}

bool Reader::deleteFileLine(const std::wstring& file_name,
                            const std::wstring& request_line) {
  std::wstring file_data;  // 记录修改过的文件内容
  std::wstring line_data;  // 用作复制文件内容的媒介
  std::wifstream input_file(file_name);
  if (!input_file.is_open()) {  // 检查文件状态
    return false;
  } else {
    while (getline(input_file, line_data)) {
      if (line_data != request_line)
        file_data += line_data;  // 无需删除的行正常转移，需删除的行不转移
      file_data += L"\n";
    }
    input_file.close();
  }
  if (file_data.back() == L'\n') file_data.pop_back();  // 删除文件末尾的换行
  std::wofstream output_file(file_name);
  if (!output_file.is_open()) {  // 检查文件状态
    return false;
  } else {
    output_file.flush();
    output_file << file_data;  // 清空并写入
    output_file.close();
    return true;
  }
}

bool Reader::deleteDirectory(const std::wstring& directory_path) {
  // 获取带通配符的绝对路径
  wchar_t buffer[1000];
  GetCurrentDirectoryW(1000, buffer);
  std::wstring tmp_file_group = buffer + directory_path + L"\\*.*";
  LPCWSTR file_group = tmp_file_group.c_str();
  // 准备其他参数
  HANDLE file_handle;
  WIN32_FIND_DATA next_file_info;
  // 获取文件句柄
  file_handle = FindFirstFileW(file_group, &next_file_info);
  if (file_handle == INVALID_HANDLE_VALUE) return false;
  // 删除找到的所有文件
  while (FindNextFileW(file_handle, &next_file_info)) {
    if (next_file_info.cFileName[0] != L'.') {  // 过滤 . 和 ..
      std::wstring tmp_file_full_path =
          buffer + directory_path + L"\\" + next_file_info.cFileName;
      _wremove(tmp_file_full_path.c_str());
    }
  }
  // 删除空文件夹
  return RemoveDirectoryW((buffer + directory_path).c_str());
}

bool Reader::appendLine(const std::wstring& file_name,
                        const std::wstring& new_line) {
  std::wstring file_data;                // 记录修改过的内容
  std::wstring line_data;                // 用作复制文件内容的媒介
  std::wifstream input_file(file_name);  // 检查文件状态
  if (!input_file.is_open()) {
    return false;
  } else {
    while (getline(input_file, line_data)) {  // 复制文件内容
      file_data += line_data;
      file_data += L"\n";
    }
    input_file.close();
  }
  file_data += new_line;  // 追加内容
  std::wofstream output_file(file_name);
  if (!output_file.is_open()) {
    return false;
  } else {
    output_file.flush();
    output_file << file_data;  // 清空并写入
    output_file.close();
    return true;
  }
}

bool Reader::changeFileLine(const std::wstring& file_name,
                            unsigned int row_number,
                            const std::wstring& request_line) {
  std::wstring file_data;                // 记录修改过的内容
  std::wstring line_data;                // 用作复制文件内容的媒介
  std::wifstream input_file(file_name);  // 检查文件状态
  if (!input_file.is_open()) {
    return false;
  } else {
    int counter = 0;
    while (getline(input_file, line_data)) {
      counter++;  // 获取当前行号
      file_data += (counter == row_number) ? request_line : line_data;
      file_data += L"\n";  // 恰为需修改的行号时进行修改
    }
    input_file.close();
  }
  if (file_data.back() == L'\n') file_data.pop_back();  // 删除文件末尾的换行
  std::wofstream output_file(file_name);
  if (!output_file.is_open()) {
    return false;
  } else {
    output_file.flush();
    output_file << file_data;  // 清空并写入
    output_file.close();
    return true;
  }
}

bool Reader::createDirectory(const std::wstring& directory_path) {
  // 获取绝对路径
  wchar_t buffer[1000];
  GetCurrentDirectoryW(1000, buffer);
  std::wstring tmp_directory = buffer + directory_path;
  LPCWSTR directory_pointer = tmp_directory.c_str();
  return CreateDirectoryW(directory_pointer, NULL);
}

bool Reader::createFile(const std::wstring& file_name) {
  std::wofstream new_file(file_name);
  if (!new_file.is_open()) {
    return false;
  } else {
    new_file.close();
    return true;
  }
}

bool Reader::moveFile(const std::wstring& new_name,
                      const std::wstring& old_name) {
  // 获取绝对路径
  wchar_t buffer[1000];
  GetCurrentDirectoryW(1000, buffer);
  std::wstring tmp_new_name = buffer + new_name;
  std::wstring tmp_old_name = buffer + old_name;
  LPCWSTR new_pointer = tmp_new_name.c_str();
  LPCWSTR old_pointer = tmp_old_name.c_str();
  return MoveFileW(old_pointer, new_pointer);
}
}  // namespace library_management_sys