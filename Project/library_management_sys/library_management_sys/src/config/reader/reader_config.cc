// * License: Apache 2.0
// * File: reader_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-09
// * Description: Define class Reader.
#include "inc/base/reader_base.h"

#include <fstream>
#include <string>
#include <windows.h>

#include "inc/base/page_base.h"
namespace library_management_sys {
bool Reader::readForPointPaint(PageUnitEx& pageunit_list_head,
                               std::string file_name) {
  std::ifstream input_file;            // Create temp file stream
  input_file.open(file_name.c_str());  // Open the file
  // Check if the file is normally opened and do the transform
  if (input_file.is_open()) {
    std::string tmp_line;
    // Do the transform for every read lines
    while (getline(input_file, tmp_line)) {
      // 48 is the ASCII code of '0'. Example: 123(.txt)->123(short)
      // The following code is equivalent to:
      // 100 * (int)('1' - '0') + 10 * (int)('2' - '0') + (int)('3' - '0')
      short tmp_coord_x = (int)tmp_line[kXBase] * 100 +
                          (int)tmp_line[kXBase + 1] * 10 +
                          (int)tmp_line[kXBase + 2] - 48 * 111;
      // tmp_coord_y is similar to tmp_coord_x
      short tmp_coord_y = (int)tmp_line[kYBase] * 100 +
                          (int)tmp_line[kYBase + 1] * 10 +
                          (int)tmp_line[kYBase + 2] - 48 * 111;
      // Transform to int first and then transform to WORD. Example:
      // 00(.txt) ©¤©¤ 0(int) ©¤©¤ 0x00__ ©¤©¤©´
      // 07(.txt) ©¤©¤ 7(int) ©¤©¤ 0x__07 ©¤©¤©Ø©¤©¤ 0x0007(WORD)(FOREGROUND_WHITE)
      WORD tmp_color = ((((int)tmp_line[kColorBase] * 10 +
                          (int)tmp_line[kColorBase + 1] - 48 * 11) &
                         0x0F)
                        << 4) +
                       (((int)tmp_line[kColorBase + 2] * 10 +
                         (int)tmp_line[kColorBase + 3] - 48 * 11) &
                        0x0F);
      COORD tmp_coord = {tmp_coord_x, tmp_coord_y};     // Combine x and y
      std::string tmp_str = tmp_line.substr(kStrBase);  // Get the std::string
      PageUnit tmp_page_unit = {tmp_coord, tmp_color,
                                tmp_str};        // Combine all above
      pageunit_list_head.append(tmp_page_unit);  // Append as new node
    }
    return true;
  } else
    return false;  // If file fails to be opened
}
}  // namespace library_management_sys