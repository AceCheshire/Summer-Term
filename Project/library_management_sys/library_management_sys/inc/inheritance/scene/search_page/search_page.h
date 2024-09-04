// * 文件：search_page.h
// * 作者：麦天乐
// * 介绍：声明 SearchPage 类。
#include <string>

#include "inc/app_const.h"
#include "inc/base/page_base.h"
#include "inc/base/scene_base.h"
#ifndef LMS_INHERITANCE_SCENE_SEARCH_PAGE_H_
#define LMS_INHERITANCE_SCENE_SEARCH_PAGE_H_
namespace library_management_sys {
// 规定了应用搜索页面的范式。示例：
//    PageUnitEx test_unit_ex;
//    SearchPage test_search_page(test_unit_ex);
class SearchPage : public SharedScene {
 public:
  SearchPage(PageUnitEx& pageunit_list_head);  // 构造函数
  // 用于启动场景，并返回真。示例：
  //    test_scene.prepareScene();
  bool prepareScene();
  // 在用户输入用户或图书名称时被执行。示例：
  //    while (is_inputting_info_) text_scene.inputInfo();
  void inputInfo();
  // 对不同的链接实现不同的响应
  bool checkLink(unsigned short check_mode);
  bool getMouseInputState() { return true; }     // 允许鼠标输入
  bool getKeyboardInputState() { return true; }  // 允许键盘输入

 private:
  // 用于删除用户或图书。该方法可以删除其在总览中的记录及用户或图书文件夹。
  // 参数为要删除的用户或图书名称。
  void del(const std::wstring& searching_object);
  // 在总览中搜索用户输入的名称，并将结果按照相似度顺序存入成员 result_ 。
  void search();
  // 计算匹配字符的个数，然后返回相似度。
  short getSimilarity(const std::wstring& request,
                       const std::wstring& finding);
  // 显示搜索结果（该方法总是返回假）
  bool searchDisplay();
  // 显示选择指针
  void pointerDisplay();
  // 用于记录用户输入
  std::wstring request_;
  // 用于记录搜索结果
  std::wstring result_[search_page::kMaxSearchNum] = {};
  // 用于记录搜索结果对应的相似度
  double similarity_value_[search_page::kMaxSearchNum] = {};
  // 用于记录选择指针指向的搜索结果序号（从 1 开始）
  int iterator_ = 0;
  // 用于记录有效的搜索结果个数
  unsigned short search_size_ = 0;
};
}  // namespace library_management_sys
#endif  // LMS_INHERITANCE_SCENE_SEARCH_PAGE_H_