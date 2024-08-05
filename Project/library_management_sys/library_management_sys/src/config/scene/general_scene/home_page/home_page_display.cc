#include"error_base.h"
#include"home_page_sp.h"
#include<iostream>
#include<windows.h>
using namespace std;

HomePage::HomePage(Mouse* attached_mouse, Scene* prev_scene,
                   PageUnitEx* pageunit_list_head)
    : GeneralScene(attached_mouse, prev_scene, pageunit_list_head) {}

bool HomePage::prepareScene() {
  try {
    while (true) {
      layoutText();
      waitInput(true, true);
    }
  } catch (BasicError err_num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    cout << endl;
    cerr << "ERR: class HomePage | function prepareScene | err_num " << err_num
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
    return false;
  }
  return true;
}
