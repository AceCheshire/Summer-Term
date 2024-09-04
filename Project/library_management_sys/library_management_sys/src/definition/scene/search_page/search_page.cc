// * �ļ���search_page.cc
// * ���ߣ�������
// * ���ܣ����� SearchPage �ࡣ
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
    shared_task_ /= 10;  // ������ҳ���أ�ȥ������ҳѡ��
  searching_book_.clear();
  searching_user_.clear();
  return true;
}

void SearchPage::inputInfo() {
  // �����λ
  COORD tmp_for_input =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  tmp_for_input.X += search_page::kInputOffset.X;
  tmp_for_input.Y += search_page::kInputOffset.Y;
  // ����ϴ����������
  Page::returnDefault();
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_for_input);
  for (int i = 0; i < request_.length(); i++) std::wcout << " ";
  // �ƶ���겢��ʾ���û�����
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                           tmp_for_input);
  Page::hideCursor(false);
  request_ = inputLine(true, true, true, true, false);
  Page::hideCursor(true);
}

bool SearchPage::checkLink(unsigned short check_mode) {
  if (check_mode == 0) return true;  // ���� checkLink()
  switch (check_mode) {
    case search_page::kSearch:
      for (int i = 0; i < search_page::kMaxSearchNum; i++) {  // ����������
        result_[i].clear();
        similarity_value_[i] = 0;
      }
      iterator_ = search_size_ = 0;
      search();                // �����������
      return searchDisplay();  // ��ʾ�������
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
        del(result_[search_page::kMaxSearchNum - iterator_]);  // ɾ���ļ�
      return checkLink(search_page::kSearch);  // ˢ���������
    case search_page::kUp:
      iterator_ = (iterator_ == 0) ? search_size_ : (iterator_ - 1);
      pointerDisplay();  // ���ϵ�������ʾ
      return false;
    case search_page::kDown:
      iterator_ = (iterator_ == search_size_) ? 0 : (iterator_ + 1);
      pointerDisplay();  // ���µ�������ʾ
      return false;
    case search_page::kModify:  // Ϊ����ҳ�洫����Ϣ
      if (iterator_ == 0) return false;  // ���ѡ��
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
  switch (shared_task_) {  // �ļ�����λ
    case search_page::kUser:
      file_name = search_page::kUserDataSource;
      folder_name = kUserFolderPath(searching_object);
      break;
    case search_page::kBook:
      file_name = search_page::kBookDataSource;
      folder_name = kBookFolderPath(searching_object);
      break;
  }  // switch (shared_task_)
  if (Reader::deleteDirectory(folder_name))  // ɾ���ļ��к�������¼
    Reader::deleteFileLine(file_name, searching_object);
}

void SearchPage::search() {
  std::wstring file_name;
  switch (shared_task_) {  // �ļ�����λ
    case search_page::kUser:
      file_name = search_page::kUserDataSource;
      break;
    case search_page::kBook:
      file_name = search_page::kBookDataSource;
      break;
  }                      // switch (shared_task_)
  int row_iterator = 1;  // �ڶ�ȡʱ�����к�
  std::wstring finding;  // �ݴ��ȡ��Ϣ
  while (Reader::readFileLine(file_name, row_iterator, finding)) {  // ��ȡ
    row_iterator++;
    double similarity =
        getSimilarity(request_, finding);               // ��ȡ���ƶ�
    if (similarity_value_[0] >= similarity) {  // �ж��Ƿ���Χ�������
      continue;
    } else {  // ���½�������б�
      similarity_value_[0] = similarity;
      result_[0] = finding;
      if (search_size_ < search_page::kMaxSearchNum)
        search_size_++;  // �������������
    }
    for (int iterator = 1; iterator < search_page::kMaxSearchNum;
         iterator++) {  // ������������򣨴�С����
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
  // �ú���ͨ������༭����������ƶ�
  short lengthR = (short)request.length();
  short lengthF = (short)finding.length();
  // ��ֹ��������õ���ʱ����
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
  return scene::kAdviceLength - ret;  // �༭����Խ�����ƶ�Խ��
}

bool SearchPage::searchDisplay() {
  // ���������������ָ���ʾ�û�����
  system("cls");
  prepareScene();
  COORD tmp_for_input =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  tmp_for_input.X += search_page::kInputOffset.X;
  tmp_for_input.Y += search_page::kInputOffset.Y;
  Page::pointPaint(tmp_for_input, page::GROUND_DEFAULT, request_);
  // �������һ�������������ʾλ��
  COORD searching_result_location =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  searching_result_location.X +=
      search_page::kSearchOffset.X + search_page::kRowOffset.X * search_size_;
  searching_result_location.Y +=
      search_page::kSearchOffset.Y + search_page::kRowOffset.Y * search_size_;
  if (search_size_ == 0) {  // �����������ʾ��Ϣ
    Page::pointPaint(searching_result_location, FOREGROUND_RED,
                     search_page::kNotMatchText);
    return false;
  }
  iterator_ = 1;
  pointerDisplay();  // ����ѡ��ָ�벢��ʾ
  for (int i = search_page::kMaxSearchNum - search_size_;
       i < search_page::kMaxSearchNum; i++) {  // ��ʾ������������
    searching_result_location.X -= search_page::kRowOffset.X;
    searching_result_location.Y -= search_page::kRowOffset.Y;
    Page::pointPaint(searching_result_location, page::GROUND_DEFAULT,
                     result_[i]);
  }
  return false;
}

void SearchPage::pointerDisplay() {
  // ����ѡ��ָ���ʼλ��
  COORD pointer_coord =
      (*pageunit_list_head_)[search_page::kStartPointText].pos_;
  pointer_coord.X +=
      search_page::kSearchOffset.X + search_page::kPointerOffset.X;
  pointer_coord.Y +=
      search_page::kSearchOffset.Y + search_page::kPointerOffset.Y;
  for (int i = 1; i <= search_page::kMaxSearchNum; i++) {  // ����ָ��켣
    if (i == iterator_) {  // ����ѡ��������������ʾָ��ͼ��
      Page::pointPaint(pointer_coord, search_page::kPointerColor,
                       search_page::kPointerText);
    } else {  // ����δѡ��������������ʾ�ո�
      Page::pointPaint(pointer_coord, page::GROUND_DEFAULT, L" ");
    }
    pointer_coord.X += search_page::kRowOffset.X;
    pointer_coord.Y += search_page::kRowOffset.Y;
  }
}
}  // namespace library_management_sys