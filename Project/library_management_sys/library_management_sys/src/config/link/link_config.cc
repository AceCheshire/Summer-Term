#include"error_base.h"
#include"link_base.h"
#include<iostream>
#include<windows.h>
using namespace std;

Link::Link(std::string symbol_str, Scene& next_scene)
    : symbol_str_(symbol_str), next_scene_serial_(&next_scene) {}

Link::Link(char* symbol_str, Scene& next_scene) throw(...) {
  try {
    next_scene_serial_ = &next_scene;
    if (symbol_str != NULL)
      symbol_str_ = symbol_str;
    else
      throw kHeapPointerError;
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: function Link | err_num " << err_num << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
  }
}

bool Link::switchScene(std::string request_str) {
  if (request_str == symbol_str_) {
    system("cls");
    next_scene_serial_->prepareScene();
    return true;
  }
  return false;
}