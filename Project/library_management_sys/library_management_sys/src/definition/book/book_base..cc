// * �ļ���book_base.cc
// * ���ߣ�������
// * ���ܣ����� Book �ࡣ
#include "inc/base/book_base.h"

#include <fstream>
#include <string>

#include "inc/app_const.h"
#include "inc/base/reader_base.h"
namespace library_management_sys {
void Book::setName(const std::wstring& book_name) {
  name_ = book_name;
  updateInfo();  // ���ǵ���Ϣ����������������
}

void Book::updateInfo() {
  Reader::readFileLine(kBookDetailPath(name_), book::kAuthorOffset, author_);
  Reader::readFileLine(kBookDetailPath(name_), book::kTypeOffset, type_);
  Reader::readFileLine(kBookDetailPath(name_), book::kStateOffset, state_);
  Reader::readFileLine(kBookDetailPath(name_), book::kDescriptionOffset,
                       description_);
  Reader::readFileLine(kBookDetailPath(name_), book::kHistoryOffset, history_);
}

void Book::appendHistory(const std::wstring& declaration,
                         const std::wstring& name) {
  time_t second;
  time(&second);
  tm time;
  localtime_s(&time, &second);
  history_ += L" " + declaration;  // ��Ϊ���
  history_ += L" " + name;         // �û�����
  history_ += L" " + std::to_wstring(time.tm_year + 1900) + L"/" +
              std::to_wstring(time.tm_mon + 1) + L"/" +
              std::to_wstring(time.tm_mday) + L"-" +
              std::to_wstring(time.tm_hour) + L":" +
              std::to_wstring(time.tm_min) + L":" +
              std::to_wstring(time.tm_sec);  // ʱ���
}

void Book::clear() {
  name_.clear();
  author_.clear();
  type_.clear();
  state_.clear();
  description_.clear();
  history_.clear();
}

bool Book::saveBook(const std::wstring& old_name = L"") const {
  if (!old_name.length()||!name_.length()) {  // ��麯������
    return false;
  } else {
    if (name_ != old_name) {  // �޸�ͼ������
      // ���ͼ�������Ƿ�淶
      std::wifstream file(kBookDetailPath(old_name));
      if (file.is_open()) {
        file.close();
      } else {
        return false;
      }
      file.open(kBookDetailPath(name_));
      if (file.is_open()) return false;
      // �����Ϲ淶������ͼ����Ϣ�ļ�������
      Reader::deleteDirectory(kBookFolderPath(old_name));
      Reader::deleteFileLine(search_page::kBookDataSource, old_name);
      this->addBook();
    }
    // ����ͼ�������ļ�����Ϣ
    bool ret = true;
    ret = ret && Reader::changeFileLine(kBookDetailPath(name_),
                                        book::kAuthorOffset, author_);
    ret = ret && Reader::changeFileLine(kBookDetailPath(name_),
                                        book::kTypeOffset, type_);
    ret = ret && Reader::changeFileLine(kBookDetailPath(name_),
                                        book::kStateOffset, state_);
    ret = ret && Reader::changeFileLine(kBookDetailPath(name_),
                                        book::kDescriptionOffset, description_);
    ret = ret && Reader::changeFileLine(kBookDetailPath(name_),
                                        book::kHistoryOffset, history_);
    return ret;
  }
}

bool Book::addBook() const {
  // ���ͼ�������Ƿ�淶
  if (!name_.length()) return false;
  std::wifstream input_file(kBookDetailPath(name_));
  if (input_file.is_open()) {
    input_file.close();
    return false;
  }
  Reader::createDirectory(kBookFolderPath(name_));
  Reader::createFile(kBookDetailPath(name_));
  input_file.open(kBookDetailPath(name_));
  if (input_file.is_open()) {  // ����ļ��Ƿ�ɹ�����
    input_file.close();
  } else {
    return false;
  }
  // ����˳����Ϣ�����ļ�
  int counter = 1;
  bool ret = true;  // ��¼��������ֵ
  while (counter <= 100) {
    if (counter == book::kAuthorOffset)
      ret = ret && Reader::appendLine(kBookDetailPath(name_), author_);
    if (counter == book::kTypeOffset)
      ret = ret && Reader::appendLine(kBookDetailPath(name_), type_);
    if (counter == book::kStateOffset)
      ret = ret && Reader::appendLine(kBookDetailPath(name_), state_);
    if (counter == book::kHistoryOffset)
      ret = ret && Reader::appendLine(kBookDetailPath(name_), history_);
    if (counter == book::kDescriptionOffset)
      ret = ret && Reader::appendLine(kBookDetailPath(name_), description_);
    counter++;
  }
  if (ret)
    Reader::appendLine(search_page::kBookDataSource, name_);  // ��ӵ�����
  return ret;
}
}  // namespace library_management_sys