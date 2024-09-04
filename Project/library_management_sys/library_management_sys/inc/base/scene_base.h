// * 文件：scene_base.h
// * 作者：麦天乐
// * 介绍：声明 Scene 类（基类），SharedScene 类（派生类）和 SharedPool 类。
#include "inc/base/book_base.h"
#include "inc/base/page_base.h"
#include "inc/base/user_base.h"
#ifndef LMS_BASE_SCENE_BASE_H_
#define LMS_BASE_SCENE_BASE_H_
namespace library_management_sys {
// 常见场景元素的容器
class Scene {
 public:
  // 基类构造函数。派生类构造函数示例:
  //    TestScene::TestScene(PageUnitEx& pageunit_list_head)
  //        : Scene(pageunit_list_head) {}
  Scene(PageUnitEx& pageunit_list_head);
  void setPageUnitList(PageUnitEx& pageunit_list) {
    pageunit_list_head_ = &pageunit_list;
  }
  PageUnitEx* getPageUnitList() const { return pageunit_list_head_; }
  // 按照拓展页面单元成员的链表顺序将文字显示在屏幕上。
  void layoutText();
  // 输入时只允许用户输入回车和退格，以及五类字符。
  // 1）空格，是否启用由参数 space 给出；
  // 2）数字 0~9 ，是否启用由参数 num 给出；
  // 3）英文字符，包括 a~z ，A~Z，是否启用由参数 en 给出；
  // 4）特殊字符，引用 scene::kSpecialChars（可设置），是否启用由参数 sp 给出；
  // 5）当前语言的字符，默认为 “ chs ”，引用 scene::kAnsiStart 和
  //    scene::kAnsiEnd 。是否启用由参数 ansi 给出。
  // 注意：按下回车后无论是否曾输入字符，都将结束本行的输入。空字符串退格失效。
  // 字符串超过设定值（ scene::kAdviceLength ）时输入失效。
  // 返回输入的字符串。参数 fill_char 指定遮罩字符。用于替代 std::wcin 。
  std::wstring inputLine(bool space, bool num, bool en, bool sp, bool ansi,
                         const wchar_t& fill_char = L'\0');
  // 声明用于启动场景的抽象方法。通常包含 layoutText() 方法。
  virtual bool prepareScene() = 0;
  // 声明类似输入框的输入抽象方法，通常在按下 Insert 键后被执行。
  virtual void inputInfo() = 0;
  // 声明用于实现场景过渡的通用方法。该方法也用于设计链接引发的场景响应。
  // 如果即将转到下一个场景，返回真，表明实现场景间的过渡。
  // 如果需要停留于本场景，返回假，此时链接引发场景内部响应。
  virtual bool checkLink(unsigned short check_mode) = 0;
  // 用于获取特定场景下鼠标输入模式的通用函数
  virtual bool getMouseInputState() = 0;
  // 用于获取特定场景下键盘输入模式的通用函数
  virtual bool getKeyboardInputState() = 0;

 protected:
  // 用于存储场景文本信息
  PageUnitEx* pageunit_list_head_;
};
// 用于存储场景之间需要分享的信息，并方便场景需求的拓展。
class SharedPool {
 public:
  // 用于读写当前登录的用户的信息
  static User current_user_;
  // 用于读写当前处理的用户的信息
  static User searching_user_;
  // 用于读写当前处理的图书的信息
  static Book searching_book_;
  // 用于记录用户的跨场景选择
  static int shared_task_;
};
// 用于实现不同场景间的信息传递。
class SharedScene : public Scene, public SharedPool {
 public:
  SharedScene(PageUnitEx& pageunit_list_head);
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCENE_BASE_H_