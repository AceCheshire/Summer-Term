// * License: Apache 2.0
// * File: scene_base.h
// * Author: Mai Tianle
// * Date: 2024-08-07
// * Description: Declare class Scene.
#include "inc/base/page_base.h"
#ifndef LMS_BASE_SCENE_BASE_H_
#define LMS_BASE_SCENE_BASE_H_
namespace library_management_sys {
namespace scene {
// Limits the length of an input line.
constexpr int adviceLength = 80;
}  // namespace scene
// Used to be a container for basic scene components.
class Scene {
 public:
  // Constructor. Example:
  //    TestScene::TestScene(PageUnitEx& pageunit_list_head)
  //        : Scene(pageunit_list_head) {}
  Scene(PageUnitEx& pageunit_list_head);

  void setPageUnitList(const PageUnitEx& pageunit_list) {
    pageunit_list_head_ = pageunit_list_head_;
  }

  PageUnitEx* getPageUnitList() const { return pageunit_list_head_; }

  // Rends text to the screen in the serial of linked list.
  // Throw kNullPointer if pageunit_list_head_ is NULL.
  // If you use layoutText() only, you should catch it.
  // Example:
  //    test_scene.layoutText();
  void layoutText() throw(...);

  // Returns the input string once key enter is pressed.
  // Used to replace std::cin.
  std::wstring inputLine(bool space);

  // Overloaded version of inputLine() (no argument). 
  // Provides fill char option for input, like password.
  std::wstring inputLine(bool space, const char& fill_char);

  // Declares general function that is used to start a scene.
  // Usually it includes layoutText() and its catch part.
  virtual bool prepareScene() = 0;

  // Declares general function that is used to input with input column.
  virtual void inputInfo() = 0;

  // Declares general funtion that is used to realize scene transition.
  // Returns true if the next scene is allowed.
  virtual bool checkLink(unsigned short check_mode) = 0;

  // Declares general function that is used to set mouse input mode.
  virtual bool getMouseInputState() = 0;

  // Declares general function that is used to set keyboard input mode.
  virtual bool getKeyboardInputState() = 0;

 protected:
  // Used for locate the address of scene text.
  PageUnitEx* pageunit_list_head_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCENE_BASE_H_