#include"../../../inc/base/page_base.h"
#include"../../../inc/base/reader_base.h"
#include<fstream>
#include<string>
#include<windows.h>
namespace library_management_sys {
bool Reader::readForPointPaint(PageUnitEx& pageunit_list_head,
                               std::string file_name) {
  std::ifstream input_file;
  input_file.open(file_name.c_str());
  if (input_file.is_open()) {
    std::string tmp_line;
    while (getline(input_file, tmp_line)) {
      short tmp_coord_x = (int)tmp_line[kXBase] * 100 +
                          (int)tmp_line[kXBase + 1] * 10 +
                          (int)tmp_line[kXBase + 2] - 48 * 111;
      short tmp_coord_y = (int)tmp_line[kYBase] * 100 +
                          (int)tmp_line[kYBase + 1] * 10 +
                          (int)tmp_line[kYBase + 2] - 48 * 111;
      WORD tmp_color = ((((int)tmp_line[kColorBase] * 10 +
                          (int)tmp_line[kColorBase + 1] - 48 * 11) &
                         0x0F)
                        << 4) +
                       (((int)tmp_line[kColorBase + 2] * 10 +
                         (int)tmp_line[kColorBase + 3] - 48 * 11) &
                        0x0F);
      COORD tmp_coord = {tmp_coord_x, tmp_coord_y};
      std::string tmp_str = tmp_line.substr(kStrBase);
      PageUnit tmp_page_unit = {tmp_coord, tmp_color, tmp_str};
      pageunit_list_head.append(tmp_page_unit);
    }
    return true;
  } else
    return false;
}
}  // namespace library_management_sys