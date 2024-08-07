#include"../../../inc/base/error_base.h"
#include"../../../inc/base/scene_base.h"
#include<iostream>
namespace library_management_sys {
Scene::Scene(PageUnitEx& pageunit_list_head)
    : pageunit_list_head_(&pageunit_list_head) {}
}  // namespace library_management_sys