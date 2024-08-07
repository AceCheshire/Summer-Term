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
  // Declares general function that is used to start a scene.   
  virtual bool prepareScene() = 0;

 protected:
  // Used for locate the address of scene text.
  PageUnitEx* pageunit_list_head_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_SCENE_BASE_H_