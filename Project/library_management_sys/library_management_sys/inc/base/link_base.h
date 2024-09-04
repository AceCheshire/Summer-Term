// * 文件：link_base.h
// * 作者：麦天乐
// * 介绍：声明 Link 类。
#include <string>
#ifndef LMS_BASE_LINK_BASE_H_
#define LMS_BASE_LINK_BASE_H_
namespace library_management_sys {
// Link 是链接（按钮）的抽象，用于连接 Scene 实例，需要挂载于 Scheduler 。
// 示例：
//    Scheduler test_scheduler;
//    std::wstring test_str;
// 	  unsigned short test_this_scene_number, test_next_scene_number;
//    unsigned short test_mode;
//    Link test_link(test_str, test_this_scene_number,
//                   test_next_scene_number, test_mode);
//    test_scheduler.appendLink(test_link);
class Link {
 public:
  // 带初始化列表的构造函数
  Link(const std::wstring& symbol_str, unsigned short this_scene_number,
       unsigned short next_scene_number, unsigned short check_mode);
  // 重载的构造函数，参数由宽字符串改为宽字符指针。若传入空指针，symbol_str 置为
  // mouse::kDefaultReturn 。
  Link(const wchar_t* symbol_str, unsigned short this_scene_number,
       unsigned short next_scene_number, unsigned short check_mode);
  // 该方法的参数是选中的屏幕字符串和当前的场景挂载在 Scheduler
  // 的编号，这两个参数用于区分不同的链接。若当前链接匹配，会返回
  // 下一场景的编号和链接的任务指令合成的编码，否则返回 -1 。
  // 通常在不了解场景对应的编号但了解链接的标识时调用（几乎总是）。示例:
  //    constexpr int kTestMaxNumber = 256;
  //    std::wstring test_symbol_string;
  //    unsigned short test_this_scene_number = 0;
  //    Link test_link_list[kTestMaxNumber];
  //    for (int i = 0; i < kTestMaxNumber; i++) {
  //      if (stringToSequence(test_symbol_string,
  //                           test_this_scene_number) != -1)
  //        std::wcout << "There exists valid link";
  //    }
  int stringToSequence(const std::wstring& request_str,
                       unsigned short this_scene_number) const;

 protected:
  // 链接的标识文本，用户通过鼠标点击触发链接。
  std::wstring symbol_str_;
  // 当前场景的调度器挂载编号
  unsigned short this_scene_number_;
  // 下一场景的调度器挂载编号
  unsigned short next_scene_number_;
  // 用来区分不同链接被触发后 Scene::checkLink() 的响应方式。
  // 该值为零意为不触发 checkLink() 。
  unsigned short check_mode_ = 0;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_LINK_BASE_H_