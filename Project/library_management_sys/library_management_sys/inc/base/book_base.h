// * 文件：book_base.h
// * 作者：麦天乐
// * 介绍：声明 Book 类。
#include <string>
#ifndef LMS_BASE_BOOK_BASE_H_
#define LMS_BASE_BOOK_BASE_H_
namespace library_management_sys {
// 集成图书信息并提供公有访问接口。
// 示例:
//    Book test_book;
class Book {
 public:
  // 更改成员 name_，并调用一次 updateInfo()。
  void setName(const std::wstring& book_name);
  // 根据 name_ 的值更新 Book 实例中的成员。
  void updateInfo();
  void setAuthor(const std::wstring& author) { author_ = author; }
  void setType(const std::wstring& type) { type_ = type; }
  void setDescription(const std::wstring& description) {
    description_ = description;
  }
  void setState(const std::wstring& state) { state_ = state; }
  // 在成员 history_ 的末尾加上新历史记录。
  // 第一个参数是行为标记，第二个参数是用户名称。
  void appendHistory(const std::wstring& declaration, const std::wstring& name);
  // 清空 Book 实例成员的值。
  void clear();
  // 保存图书信息到文件中，参数为旧图书名称，成功返回真。
  bool saveBook(const std::wstring& old_name) const;
  // 新增图书文件夹，成功返回真。
  bool addBook() const;
  std::wstring getName() const { return name_; }
  std::wstring getDescription() const { return description_; }
  std::wstring getAuthor() const { return author_; }
  std::wstring getType() const { return type_; }
  std::wstring getState() const { return state_; }
  std::wstring getHistory() const { return history_; }

 protected:
  // 记录图书名称
  std::wstring name_;
  // 记录图书作者
  std::wstring author_ = L"Unknown";
  // 记录图书类别，譬如“教育”。
  std::wstring type_ = L"Unknown";
  // 记录图书简要介绍
  std::wstring description_;
  // 记录图书状态（借出或空闲）
  std::wstring state_;
  // 记录图书历史
  std::wstring history_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_BOOK_BASE_H_