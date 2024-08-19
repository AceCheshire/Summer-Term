// * License: Apache 2.0
// * File: book_base.h
// * Author: Mai Tianle
// * Date: 2024-08-15
// * Description: Declare class Book.
#include <string>
#ifndef LMS_BASE_BOOK_BASE_H_
#define LMS_BASE_BOOK_BASE_H_
// Path that records book's data.
#define kBookDataPath(BOOK_NAME) L"res/book/" + BOOK_NAME + L"/detail.dat"
namespace library_management_sys {
namespace book {
enum Order {
  // It means the order of author_ in detail.dat.
  kAuthorOffset = 1,

  // It means the order of type_ in detail.dat.
  kTypeOffset,

  // It means the order of tag_ in detail.dat.
  kTagOffset,

  // It means the order of state_ in detail.dat.
  kStateOffset,

  // It means the order of description_ in detail.dat.
  kDescriptionOffset
};
}  // namespace book

// Coordinates information about book and provides public
// interfaces to access it.
// Example:
//    Book test_book;
class Book {
 public:
  // Changes name_ and call updateInfo().
  void setName(const std::wstring& book_name);

  // Updates data in Book instance by name_.
  // Used after setName().
  void updateInfo();

  // Clears the members.
  void clear();

  std::wstring getName() const { return name_; }
  std::wstring getDescription() const { return description_; }
  std::wstring getTag() const { return tag_; }
  std::wstring getAuthor() const { return author_; }
  std::wstring getType() const { return type_; }
  std::wstring getState() const { return state_; }

  void setAuthor(const std::wstring& author) { author_ = author; }
  void setType(const std::wstring& type) { type_ = type; }
  void setDescription(const std::wstring& description) {
    description_ = description;
  }
  void setState(const std::wstring& state) { state_ = state; }
  void setTag(const std::wstring& tag) { tag_ = tag; }

 protected:
  // Records book name.
  std::wstring name_;

  // Records author name of the book.
  std::wstring author_;

  // Records type of book, like "Education".
  std::wstring type_;

  // Records book brief introduction.
  std::wstring description_;

  // Records book state (borrowed or not).
  std::wstring state_;

  // Tags that describe a book.
  std::wstring tag_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_BOOK_BASE_H_