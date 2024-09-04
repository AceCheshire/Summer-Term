// * 文件：search_page.cc
// * 作者：麦天乐
// * 介绍：定义 SearchPage 类。
#include "inc/inheritance/scene/search_page/search_page.h"

#include <windows.h>

#include <iostream>
#include <string>

#include "inc/app_const.h"
#include "inc/base/book_base.h"
#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
#include "inc/base/scene_base.h"
#include "inc/base/user_base.h"
namespace library_management_sys {
SearchPage::SearchPage(PageUnitEx& pageunit_list_head)
    : SharedScene(pageunit_list_head) {}

bool SearchPage::prepareScene() {
  layoutText();
  if (shared_task_ > 10)
    shared_task_ /= 10;  // 从详情页返回，去除搜索页选择
  searching_book_.clear();
  searching_user_.clear();
  return true;
}

void SearchPage::inputInfo() {
  // 输入框定位
  COORD tmp_for_input =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  tmp_for_input.X += search_page::kInputOffset.X;
  tmp_for_input.Y += search_page::kInputOffset.Y;
  // 清除上次输入的内容
  Page::returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_for_input);
  for (int i = 0; i < request_.length(); i++) std::wcout << " ";
  // 移动光标并显示，用户输入
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_for_input);
  Page::hideCursor(false);
  request_ = inputLine(true, true, true, true, false);
  Page::hideCursor(true);
}

bool SearchPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;  // 无需 checkLink()
  switch (check_mode) {
    case search_page::kSearch:
      for (int i = 0; i < search_page::kMaxSearchNum; i++) {  // 清空搜索结果
        result_[i].clear();
        similarity_value_[i] = 0;
      }
      iterator_ = search_size_ = 0;
      search();                // 存入搜索结果
      return searchDisplay();  // 显示搜索结果
    case search_page::kAdd:
      if (current_user_.checkPermission()) {
        shared_task_ =
            shared_task_ * 10 + search_page::kAdd;
        return true;
      } else {
        return false;
      }
    case search_page::kDelete:
      if (current_user_.checkPermission())
        del(result_[search_page::kMaxSearchNum - iterator_]);  // 删除文件
      return checkLink(search_page::kSearch);  // 刷新搜索结果
    case search_page::kUp:
      iterator_ = (iterator_ == 0) ? search_size_ : (iterator_ - 1);
      pointerDisplay();  // 向上迭代并显示
      return false;
    case search_page::kDown:
      iterator_ = (iterator_ == search_size_) ? 0 : (iterator_ + 1);
      pointerDisplay();  // 向下迭代并显示
      return false;
    case search_page::kModify:  // 为详情页面传递信息
      if (iterator_ == 0) return false;  // 检查选中
      if (shared_task_ == search_page::kUser)
        searching_user_.setName(
            result_[search_page::kMaxSearchNum - iterator_]);
      if (shared_task_ == search_page::kBook)
        searching_book_.setName(
            result_[search_page::kMaxSearchNum - iterator_]);
      shared_task_ =
          shared_task_ * 10 + search_page ::kModify;
      return true;
    default:
      return false;
  }  // switch (check_mode)
}

void SearchPage::del(const std::wstring& searching_object) {
  std::wstring file_name;
  std::wstring folder_name;
  switch (shared_task_) {  // 文件名定位
    case search_page::kUser:
      file_name = search_page::kUserDataSource;
      folder_name = kUserFolderPath(searching_object);
      break;
    case search_page::kBook:
      file_name = search_page::kBookDataSource;
      folder_name = kBookFolderPath(searching_object);
      break;
  }  // switch (shared_task_)
  if (Reader::deleteDirectory(folder_name))  // 删除文件夹和总览记录
    Reader::deleteFileLine(file_name, searching_object);
}

void SearchPage::search() {
  std::wstring file_name;
  switch (shared_task_) {  // 文件名定位
    case search_page::kUser:
      file_name = search_page::kUserDataSource;
      break;
    case search_page::kBook:
      file_name = search_page::kBookDataSource;
      break;
  }                      // switch (shared_task_)
  int row_iterator = 1;  // 在读取时迭代行号
  std::wstring finding;  // 暂存读取信息
  while (Reader::readFileLine(file_name, row_iterator, finding)) {  // 读取
    row_iterator++;
    double similarity =
        getSimilarity(request_, finding);               // 获取相似度
    if (similarity_value_[0] >= similarity) {  // 判断是否入围搜索结果
      continue;
    } else {  // 将新结果纳入列表
      similarity_value_[0] = similarity;
      result_[0] = finding;
      if (search_size_ < search_page::kMaxSearchNum)
        search_size_++;  // 计算搜索结果数
    }
    for (int iterator = 1; iterator < search_page::kMaxSearchNum;
         iterator++) {  // 将搜索结果排序（从小到大）
      if (similarity_value_[iterator] >= similarity) {
        break;
      } else {
        std::swap(similarity_value_[iterator],
                  similarity_value_[iterator - 1]);
        std::swap(result_[iterator], result_[iterator - 1]);
      }
    }
  }
}

short SearchPage::getSimilarity(const std::wstring& request,
                                 const std::wstring& finding) {
  // 该函数通过计算编辑距离计算相似度
  short lengthR = (short)request.length();
  short lengthF = (short)finding.length();
  // 防止溢出而设置的临时变量
  short temp_num_1 = lengthR + 1;
  short temp_num_2 = lengthF + 1;
  short* distance = (short*)malloc(sizeof(short) * (temp_num_1) * (temp_num_2));
  for (short i = 0; i <= lengthR; i++) *(distance + i * (lengthF + 1)) = i;
  for (short j = 0; j <= lengthF; j++) *(distance + j) = j;
  for (short i = 1; i <= lengthR; i++) {
    for (short j = 1; j <= lengthF; j++) {
      temp_num_1 = i - 1;
      temp_num_2 = j - 1;
      if (request[temp_num_1] == finding[temp_num_2])
        *(distance + i * (lengthF + 1) + j) =
            *(distance + (i - 1) * (lengthF + 1) + (j - 1)) + 1;
      else {
        *(distance + i * (lengthF + 1) + j) =
            min(*(distance + (i - 1) * (lengthF + 1) + (j - 1)) + 1,
                min(*(distance + (i - 1) * (lengthF + 1) + j) + 1,
                    *(distance + i * (lengthF + 1) + (j - 1))) +
                    1);
      }
    }
  }
  short ret = *(distance + (lengthR + 1) * (lengthF + 1) - 1);
  free(distance);
  return scene::kAdviceLength - ret;  // 编辑距离越大，相似度越低
}

bool SearchPage::searchDisplay() {
  // 清除旧搜索结果并恢复显示用户输入
  system("cls");
  prepareScene();
  COORD tmp_for_input =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  tmp_for_input.X += search_page::kInputOffset.X;
  tmp_for_input.Y += search_page::kInputOffset.Y;
  Page::pointPaint(tmp_for_input, page::GROUND_DEFAULT, request_);
  // 计算最后一条搜索结果的显示位置
  COORD searching_result_location =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  searching_result_location.X +=
      search_page::kSearchOffset.X + search_page::kRowOffset.X * search_size_;
  searching_result_location.Y +=
      search_page::kSearchOffset.Y + search_page::kRowOffset.Y * search_size_;
  if (search_size_ == 0) {  // 无搜索结果显示信息
    Page::pointPaint(searching_result_location, FOREGROUND_RED,
                     search_page::kNotMatchText);
    return false;
  }
  iterator_ = 1;
  pointerDisplay();  // 重置选择指针并显示
  for (int i = search_page::kMaxSearchNum - search_size_;
       i < search_page::kMaxSearchNum; i++) {  // 显示搜索出的名称
    searching_result_location.X -= search_page::kRowOffset.X;
    searching_result_location.Y -= search_page::kRowOffset.Y;
    Page::pointPaint(searching_result_location, page::GROUND_DEFAULT,
                     result_[i]);
  }
  return false;
}

void SearchPage::pointerDisplay() {
  // 计算选择指针初始位置
  COORD pointer_coord =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  pointer_coord.X +=
      search_page::kSearchOffset.X + search_page::kPointerOffset.X;
  pointer_coord.Y +=
      search_page::kSearchOffset.Y + search_page::kPointerOffset.Y;
  for (int i = 1; i <= search_page::kMaxSearchNum; i++) {  // 遍历指针轨迹
    if (i == iterator_) {  // 若是选择的搜索结果，显示指针图案
      Page::pointPaint(pointer_coord, search_page::kPointerColor,
                       search_page::kPointerText);
    } else {  // 若是未选择的搜索结果，显示空格
      Page::pointPaint(pointer_coord, page::GROUND_DEFAULT, L" ");
    }
    pointer_coord.X += search_page::kRowOffset.X;
    pointer_coord.Y += search_page::kRowOffset.Y;
  }
}
}  // namespace library_management_sys