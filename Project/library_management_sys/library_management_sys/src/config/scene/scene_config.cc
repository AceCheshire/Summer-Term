#include"../../../inc/base/error_base.h"
#include"../../../inc/base/scene_base.h"
#include<iostream>
namespace library_management_sys {
Scene::Scene(Mouse* attached_mouse, Scene* prev_scene,
             PageUnitEx* pageunit_list_head)
    : attached_mouse_(attached_mouse),
      prev_scene_(prev_scene),
      pageunit_list_head_(pageunit_list_head) {}
}  // namespace library_management_sys