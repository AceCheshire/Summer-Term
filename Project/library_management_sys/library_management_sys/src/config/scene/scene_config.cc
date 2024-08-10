// * License: Apache 2.0
// * File: scene_config.cc
// * Author: Mai Tianle
// * Date: 2024-08-10
// * Description: Define class Scene.
#include "inc/base/scene_base.h"

#include <iostream>

#include "inc/base/error_base.h"
#include "inc/base/page_base.h"
namespace library_management_sys {
Scene::Scene(PageUnitEx& pageunit_list_head)
    : pageunit_list_head_(&pageunit_list_head) {}

void Scene::layoutText() throw() {
  Page tmp_page;  // Create temp Page to use Page interface.
  PageUnitEx* tmp_pageunit_pointer = pageunit_list_head_;  // Used as iterator
  // Equivalent to pageunit_list_head_ == NULL
  if (tmp_pageunit_pointer == NULL) throw kHeapPointerError;
  while (tmp_pageunit_pointer != NULL) {
    tmp_page.pointPaint(tmp_pageunit_pointer->getPageUnit());  // Get and paint
    tmp_pageunit_pointer = tmp_pageunit_pointer->getNext();    // Iterate
  }
}
}  // namespace library_management_sys