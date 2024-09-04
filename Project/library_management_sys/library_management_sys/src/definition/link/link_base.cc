// * 文件：link_base.cc
// * 作者：麦天乐
// * 介绍：定义 Link 类。
#include "inc/base/link_base.h"

#include <string>

#include "inc/app_const.h"
namespace library_management_sys {
Link::Link(const std::wstring& symbol_str, unsigned short this_scene_number,
           unsigned short next_scene_number, unsigned short check_mode)
    : symbol_str_(symbol_str),
      this_scene_number_(this_scene_number),
      next_scene_number_(next_scene_number),
      check_mode_(check_mode) {}

Link::Link(const wchar_t* symbol_str, unsigned short this_scene_number,
           unsigned short next_scene_number, unsigned short check_mode) {
  this_scene_number_ = this_scene_number;
  next_scene_number_ = next_scene_number;
  check_mode_ = check_mode;
  if (symbol_str != NULL) {
    symbol_str_ = symbol_str;
  } else {
    symbol_str = mouse::kDefaultReturn;
  }
}

int Link::stringToSequence(const std::wstring& request_str,
                           unsigned short this_scene_number) const {
  // 匹配标识文本与当前场景以确定唯一链接
  if (request_str == symbol_str_ && this_scene_number_ == this_scene_number) {
    return 1000 * check_mode_ + next_scene_number_;  // 返回跳转编码
  } else {
    return -1;  // 未找到匹配的链接
  }
}
}  // namespace library_management_sys