#pragma once
#include"mouse_base.h"
#include"page_base.h"
constexpr int kMaxKeyNum = 256;
constexpr int kMaxLinkNum = 64;

class Scene {
 public:
  Scene(Mouse*, Scene*, PageUnitEx*);
  virtual bool prepareScene() = 0;

 protected:
  Mouse* attached_mouse_;
  std::string mouse_msg_;
  Scene* prev_scene_;
  PageUnitEx* pageunit_list_head_;
};