// * License: Apache 2.0
// * File: general_scene_sp.h
// * Author: Mai Tianle
// * Date: 2024-08-07
// * Description: Declare class GeneralScene.
#include "inc/base/page_base.h"
#ifndef LMS_SPECIFIC_SCENE_GENERAL_SCENE_H_
#define LMS_SPECIFIC_SCENE_GENERAL_SCENE_H_
namespace library_management_sys {
//
class GeneralScene : public Scene {
 public:
  GeneralScene(PageUnitEx& pageunit_list_head);

 protected:
  void waitInput(bool, bool) throw();
  void layoutText() throw();
  void keyTab();
  void keyRestore();
  PageUnitEx* unit_current_ = NULL;
};
}  // namespace library_management_sys
#endif  // LMS_SPECIFIC_SCENE_GENERAL_SCENE_H_