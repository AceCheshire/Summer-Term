// * �ļ���book_base.h
// * ���ߣ�������
// * ���ܣ����� Book �ࡣ
#include <string>
#ifndef LMS_BASE_BOOK_BASE_H_
#define LMS_BASE_BOOK_BASE_H_
namespace library_management_sys {
// ����ͼ����Ϣ���ṩ���з��ʽӿڡ�
// ʾ��:
//    Book test_book;
class Book {
 public:
  // ���ĳ�Ա name_��������һ�� updateInfo()��
  void setName(const std::wstring& book_name);
  // ���� name_ ��ֵ���� Book ʵ���еĳ�Ա��
  void updateInfo();
  void setAuthor(const std::wstring& author) { author_ = author; }
  void setType(const std::wstring& type) { type_ = type; }
  void setDescription(const std::wstring& description) {
    description_ = description;
  }
  void setState(const std::wstring& state) { state_ = state; }
  // �ڳ�Ա history_ ��ĩβ��������ʷ��¼��
  // ��һ����������Ϊ��ǣ��ڶ����������û����ơ�
  void appendHistory(const std::wstring& declaration, const std::wstring& name);
  // ��� Book ʵ����Ա��ֵ��
  void clear();
  // ����ͼ����Ϣ���ļ��У�����Ϊ��ͼ�����ƣ��ɹ������档
  bool saveBook(const std::wstring& old_name) const;
  // ����ͼ���ļ��У��ɹ������档
  bool addBook() const;
  std::wstring getName() const { return name_; }
  std::wstring getDescription() const { return description_; }
  std::wstring getAuthor() const { return author_; }
  std::wstring getType() const { return type_; }
  std::wstring getState() const { return state_; }
  std::wstring getHistory() const { return history_; }

 protected:
  // ��¼ͼ������
  std::wstring name_;
  // ��¼ͼ������
  std::wstring author_ = L"Unknown";
  // ��¼ͼ�����Ʃ�硰��������
  std::wstring type_ = L"Unknown";
  // ��¼ͼ���Ҫ����
  std::wstring description_;
  // ��¼ͼ��״̬���������У�
  std::wstring state_;
  // ��¼ͼ����ʷ
  std::wstring history_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_BOOK_BASE_H_