#pragma once
#include<iostream>
#include<windows.h>
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
constexpr WORD GROUND_DEFAULT = 7U;

struct PageUnit {
  COORD pos;
  WORD color;
  std::string text;
};

class PageUnitEx {
 public:
  void append(PageUnit&);
  PageUnitEx* findByText(std::string);
  PageUnit& getPageUnit() { return this_unit_; }
  PageUnitEx* getNext() { return next_unit_; }
  void deleteAll();

 private:
  PageUnit this_unit_;
  PageUnitEx* next_unit_;
};

class Page {
 public:
  Page();
  void hideCursor(bool);
  void returnDefault() throw();
  bool pointPaint(PageUnit) throw();
  bool pointPaint(COORD, WORD) throw();
  bool pointPaint(COORD, WORD, std::string) throw();
  bool pointPaint(short, short, WORD) throw();
  bool pointPaint(short, short, WORD, std::string) throw();

 protected:
  HANDLE handle_page_output_;
};