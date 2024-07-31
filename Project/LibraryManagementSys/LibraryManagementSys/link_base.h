#pragma once
#include"scene_base.h"
#include<iostream>

class Link {
 public:
  Link(std::string, Scene*);
  Link(char*, Scene*) throw(...);
  void switchScene(std::string);

 private:
  std::string symbol_str_;
  Scene* next_scene_;
};