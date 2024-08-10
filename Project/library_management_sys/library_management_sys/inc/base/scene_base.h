// * License: Apache 2.0
// * File: scene_base.h
// * Author: Mai Tianle
// * Date: 2024-08-07
// * Description: Declare class Scene.
#include "inc/base/page_base.h"
#ifndef LMS_BASE_SCENE_BASE_H_
#define LMS_BASE_SCENE_BASE_H_
namespace library_management_sys {
// Used to be a container for basic scene components.
class Scene {
 public:
  // Constructor. Example:
  //    TestScene::TestScene(PageUnitEx& pageunit_list_head)
  //        : Scene(pageunit_list_head) {}
  Scene(PageUnitEx& pageunit_list_head);
  PageUnitEx* getPageUnitList() const { return pageunit_list_head_; }
  // Rends text to the screen in the serial of linked list.
  // Throw kHeapPointerError if pageunit_list_head_ is NULL.
  // If you use layoutText() only, you should catch it.
  // Example:
  //    test_scene.layoutText();
  void layoutText() throw();
  // Declares general function that is used to start a scene.
  // Usually it includes layoutText() and its catch part.
  virtual bool prepareScene() = 0;
  // Declares general function that is used to input with input column.
  virtual void inputInfo() = 0;
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