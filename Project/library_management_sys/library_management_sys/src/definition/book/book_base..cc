// * License: Apache 2.0
// * File: book_base.cc
// * Author: Mai Tianle
// * Date: 2024-08-15
// * Description: Define class Book.
#include <string>

#include "inc/base/book_base.h"
#include "inc/base/reader_base.h"
namespace library_management_sys {
void Book::setName(const std::wstring& book_name) {
  name_ = book_name;
  updateInfo();  // Call it considering info fluctuation
}

void Book::updateInfo() {
  Reader tmp_reader;  // temp Reader for interface
  // Update author_
  tmp_reader.readFileLine(kBookDataPath(name_), book::kAuthorOffset, author_);
  // Update type_
  tmp_reader.readFileLine(kBookDataPath(name_), book::kTypeOffset, type_);
  // Update tag_
  tmp_reader.readFileLine(kBookDataPath(name_), book::kTagOffset, tag_);
  // Update state_
  tmp_reader.readFileLine(kBookDataPath(name_), book::kStateOffset, state_);
  // Update description_
  tmp_reader.readFileLine(kBookDataPath(name_), book::kDescriptionOffset, description_);
}

void Book::clear() {
  while (name_.length()) name_.pop_back();
  while (author_.length()) author_.pop_back();
  while (type_.length()) type_.pop_back();
  while (tag_.length()) tag_.pop_back();
  while (state_.length()) state_.pop_back();
  while (description_.length()) description_.pop_back();
}
}  // namespace library_management_sys