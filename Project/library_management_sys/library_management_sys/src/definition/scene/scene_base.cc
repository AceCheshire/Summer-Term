// * 文件：scene_base.cc
// * 作者：麦天乐
// * 介绍：定义 Scene 类。
#include "inc/base/scene_base.h"

#include <conio.h>

#include <iostream>
#include <string>
#include <tuple>

#include "inc/app_const.h" 
#include "inc/base/page_base.h"
namespace library_management_sys {
Scene::Scene(PageUnitEx& pageunit_list_head)
    : pageunit_list_head_(&pageunit_list_head) {}

SharedScene::SharedScene(PageUnitEx& pageunit_list_head)
    : Scene(pageunit_list_head) {}

// SharedPool 的初始化
User SharedPool::current_user_;
User SharedPool::searching_user_;
Book SharedPool::searching_book_;
int SharedPool::shared_task_ = 0;

void Scene::layoutText() {
  PageUnitEx* iterator = pageunit_list_head_;
  while (iterator != NULL) {  // 遍历链表元素
    Page::pointPaint(iterator->pos_, iterator->color_, iterator->text_);
    iterator = iterator->getNext();
  }
}

std::wstring Scene::inputLine(bool space, bool num, bool en, bool sp, bool ansi,
                              const wchar_t& fill_char) {
  std::wstring tmp_string;
  wchar_t tmp_char;
  while ((tmp_char = _getwch()) != L'\r') {  // 处理回车
    if (tmp_char == 224 || tmp_char == 0)
      std::ignore = _getwch();                             // 处理控制按键
    if (((en && L'A' <= tmp_char && tmp_char <= 'Z') ||    // 英文字母大写
         (en && L'a' <= tmp_char && tmp_char <= L'z') ||   // 英文字母小写
         (space && tmp_char == L' ') ||                    // 空格
         (num && L'0' <= tmp_char && tmp_char <= L'9') ||  // 数字
         (sp && (std::wstring(scene::kSpecialChars).find(tmp_char)) !=
                    std::wstring::npos) ||          // 特殊字符
         (ansi && scene::kAnsiStart <= tmp_char &&  // 当前语言表意字符
          tmp_char <= scene::kAnsiEnd)) &&
        tmp_string.length() <= scene::kAdviceLength) {  // 限制输入长度
      std::wcout << ((fill_char == L'\0') ? tmp_char
                                          : fill_char);  // 显示遮罩字符
      tmp_string.push_back(tmp_char);  // 向数据添加字符
    } else if (tmp_char == L'\b' && tmp_string.length()) {  // 处理退格
      if (19968U <= tmp_string.back() && tmp_string.back() <= 40895U)
        std::wcout << L"\b \b";
      std::wcout << L"\b \b";  // 删除显示字符（中文则连删两个）
      tmp_string.pop_back();   // 向数据删除字符
    }
  }
  return tmp_string;
}
}  // namespace library_management_sys