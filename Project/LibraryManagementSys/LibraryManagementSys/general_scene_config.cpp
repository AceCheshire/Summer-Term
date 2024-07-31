#include"error_base.h"
#include"general_scene_sp.h"
#include<conio.h>
#include<iostream>
#pragma warning(disable:4996)

GeneralScene::GeneralScene(Mouse* attached_mouse, Scene* prev_scene,
                           PageUnitEx* pageunit_list_head)
    : Scene(attached_mouse, prev_scene, pageunit_list_head) {}

void GeneralScene::findLink(std::string msg) {
  for (int i = 0; i < kMaxLinkNum; i++) {
    if (button_list_[i] != NULL) {
      button_list_[i]->switchScene(msg);
    }
  }
}

void GeneralScene::appendLink(Link* new_link) {
  int i = 0;
  while (button_list_[i] != NULL) i++;
  button_list_[i] = new_link;
}

void GeneralScene::layoutText() throw() {
  Page tmp_page;
  PageUnitEx* tmp_pageunit_pointer = pageunit_list_head_;
  if (tmp_pageunit_pointer == NULL) throw HEAP_POINTER_ERROR;
  while (tmp_pageunit_pointer != NULL) {
    tmp_page.pointPaint(tmp_pageunit_pointer->getPageUnit());
    tmp_pageunit_pointer = tmp_pageunit_pointer->getNext();
  }
  keyRestore();
}

void GeneralScene::waitInput(bool isKeyboardInputOn,
                             bool isMouseInputOn) throw() {
  if (!isKeyboardInputOn && !isMouseInputOn) throw ENDLESS_LOOP_ERROR;
  if (isKeyboardInputOn) {
    if (KEY_DOWN(VK_TAB)) keyTab();
    if (KEY_DOWN(VK_RETURN) && unit_current_ != NULL)
      findLink(unit_current_->getPageUnit().text);
  }
  if (!((mouse_msg_ = (*attached_mouse_).hoverAndClick(pageunit_list_head_))
            .empty()) &&
      isMouseInputOn) {
    findLink(mouse_msg_);
  }
}

void GeneralScene::keyTab() {
  Page tmp_page;
  PageUnit tmp_unit;
  if (unit_current_ == NULL) {
    unit_current_ = pageunit_list_head_->getNext();
    tmp_unit = unit_current_->getPageUnit();
    tmp_unit.color = BACKGROUND_INTENSITY;
  } else {
    tmp_page.pointPaint(unit_current_->getPageUnit());
    if (unit_current_->getNext() == NULL) {
      tmp_unit = unit_current_->getPageUnit();
      unit_current_ = NULL;
    } else {
      unit_current_ = unit_current_->getNext();
      tmp_unit = unit_current_->getPageUnit();
      tmp_unit.color = BACKGROUND_INTENSITY;
    }
  }
  tmp_page.pointPaint(tmp_unit);
}

void GeneralScene::keyRestore() {
  Page tmp_page;
  PageUnit tmp_unit;
  if (unit_current_ != NULL) {
    tmp_unit = unit_current_->getPageUnit();
    tmp_unit.color = BACKGROUND_INTENSITY;
    tmp_page.pointPaint(tmp_unit);
  }
}

Link* GeneralScene::button_list_[kMaxLinkNum] = {};