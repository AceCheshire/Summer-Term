// * License: Apache 2.0
// * File: reader_base.cc
// * Author: Mai Tianle
// * Date: 2024-08-09
// * Description: Define class Reader.
#include "inc/base/reader_base.h"

#include <direct.h>
#include <windows.h>

#include <fstream>
#include <string>

#include "inc/base/page_base.h"
namespace library_management_sys {
bool Reader::readForPointPaint(PageUnitEx& pageunit_list_head,
                               const std::wstring& file_name) {
  std::wifstream input_file;
  input_file.imbue(std::locale("chs"));  // Create temp file stream
  input_file.open(file_name);            // Open the file
  // Check if the file is normally opened and do the transform
  if (input_file.is_open()) {
    std::wstring tmp_line;
    // Do the transform for every read lines
    while (getline(input_file, tmp_line)) {
      // 48 is the ASCII code of '0'. Example: 123(.txt)->123(short)
      // The following code is equivalent to:
      // 100 * (int)('1' - '0') + 10 * (int)('2' - '0') + (int)('3' - '0')
      short tmp_coord_x = (int)tmp_line[reader::kXBase] * 100 +
                          (int)tmp_line[reader::kXBase + 1] * 10 +
                          (int)tmp_line[reader::kXBase + 2] - 48 * 111;
      // tmp_coord_y is similar to tmp_coord_x
      short tmp_coord_y = (int)tmp_line[reader::kYBase] * 100 +
                          (int)tmp_line[reader::kYBase + 1] * 10 +
                          (int)tmp_line[reader::kYBase + 2] - 48 * 111;
      // Transform to int first and then transform to WORD. Example:
      // 00(.txt) ©¤©¤ 0(int) ©¤©¤ 0x00__ ©¤©¤©´
      // 07(.txt) ©¤©¤ 7(int) ©¤©¤ 0x__07 ©¤©¤©Ø©¤©¤ 0x0007(WORD)(FOREGROUND_WHITE)
      WORD tmp_color = ((((int)tmp_line[reader::kColorBase] * 10 +
                          (int)tmp_line[reader::kColorBase + 1] - 48 * 11) &
                         0x0F)
                        << 4) +
                       (((int)tmp_line[reader::kColorBase + 2] * 10 +
                         (int)tmp_line[reader::kColorBase + 3] - 48 * 11) &
                        0x0F);
      COORD tmp_coord = {tmp_coord_x, tmp_coord_y};  // Combine x and y
      bool tmp_highlight_ability = (int)tmp_line[reader::kHighlightBase] -
                                   48;  // Get the can_be_highlighted
      std::wstring tmp_str =
          tmp_line.substr(reader::kStrBase);  // Get the std::wstring
      PageUnit tmp_page_unit = {tmp_coord, tmp_color, tmp_highlight_ability,
                                tmp_str};        // Combine all above
      pageunit_list_head.append(tmp_page_unit);  // Append as new node
    }
    input_file.close();
    return true;
  } else
    return false;  // If file fails to be opened
}

bool Reader::readForLogin(const std::wstring& name,
                          const std::wstring& password) {
  std::wifstream input_file;
  input_file.imbue(std::locale("chs"));          // Create temp file stream
  std::wstring file_path = kUserPasswordPath(name);  // Get path
  input_file.open(file_path);                   // Open the file
  if (input_file.is_open()) {
    // Read and compare
    std::wstring tmp_line;
    getline(input_file, tmp_line);
    if (tmp_line.length() && tmp_line == password) {
      input_file.close();
      return true;
    }
  }
  return false;
}

bool Reader::readFileLine(const std::wstring& file_name, unsigned int row_serial,
                          std::wstring& destination) {
  std::wifstream input_file;            // Create temp file stream
  input_file.imbue(std::locale("chs"));
  int iterator = row_serial;  // Record repeat times
  input_file.open(file_name);          // Open the file
  if (input_file.is_open()) {
    while (iterator--) {
      if (!getline(input_file, destination)) break;  // EOF
    }
    input_file.close();
    return (iterator > -1) ? false : true;
  } else
    return false;  // Fails to open file
}

bool Reader::deleteFileLine(const std::wstring& file_name,
                            const std::wstring& request_line) {
  std::wifstream input_file;
  input_file.imbue(std::locale("chs"));
  std::wofstream output_file;
  output_file.imbue(std::locale("chs"));  // Create temp file stream
  std::wstring file_data;      // Used to record modified file
  std::wstring line_data;      // Used to copy data to file_data
  input_file.open(file_name);  // Open the file
  if (input_file.is_open()) {
    // Maintain the result of modified file
    while (getline(input_file, line_data)) {
      if (line_data != request_line) file_data += line_data;
      file_data += L"\n";
    }
    input_file.close();
  } else
    return false;  // Fails to open file

  output_file.open(file_name);  // Open the file
  if (output_file.is_open()) {
    output_file.flush();
    output_file << file_data;
    output_file.close();
    return true;
  } else
    return false;  // Fails to open file
}

bool Reader::deleteDirectory(const std::wstring& directory_path) {
  std::wstring tmp_file_path = directory_path + L"*.*";
  LPCWSTR file_name = tmp_file_path.c_str();  // Get file path
  HANDLE file_handle;
  WIN32_FIND_DATA next_file_info;
  file_handle = FindFirstFileW(file_name, &next_file_info);  // Get file handle
  if (file_handle == INVALID_HANDLE_VALUE) return false;
  // Delete all files found, except "." and ".."
  while (FindNextFileW(file_handle,&next_file_info)){
    if (next_file_info.cFileName[0] != L'.') DeleteFileW(next_file_info.cFileName);
  }
  deleteDirectory(directory_path); // Delete empty folder
  return true;
}
}  // namespace library_management_sys