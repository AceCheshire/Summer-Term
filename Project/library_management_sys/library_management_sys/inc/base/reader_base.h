// * �ļ���reader_base.h
// * ���ߣ�������
// * ���ܣ����� Reader �ࡣ
#include <string>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_READER_BASE_H_
#define LMS_BASE_READER_BASE_H_
namespace library_management_sys {
// ��̬�࣬��д�����ļ���������ظ�ֵ��
class Reader {
 public:
  // ����Ϊ PageUnitEx ʵ����ȡ�ļ���Ϣ������ļ����ܱ������򿪣����ؼ١�
  // ��ȡ֮�� pageunit_list_head �� PageUnit ��Ա����Ϊ��ʼ״̬������
  // ����Ϊ���·����
  // ʾ����
  //    if (Reader::readForPointPaint(test_pageunit_ex, L"test.txt")) {
  //      PageUnitEx* test_pageunit_pointer;
  //      while ((test_pageunit_pointer = test_pageunit_ex.getNext()) != NULL)
  //        Page::pointPaint(test_pageunit_pointer->getPageUnit());
  //    }
  static bool readForPointPaint(PageUnitEx& pageunit_list_head,
                                const std::wstring& file_name);
  // �������ļ�������ɹ���ѯ�����ƺ���Ӧ�����룬�����档
  // ʾ��:
  //    std::wcin >> test_name;
  //    std::wcin >> test_password;
  //    if (Reader::readForLogin(test_name, test_password)) {
  //      std::wcout << "Password is correct!" << std::endl;
  //    }
  // ��ȼ��ڣ�
  //    std::wstring password_path = L"res/user/" + name + L"/password.txt";
  //    Reader::readFileLine(password_path, 1, correct_password);
  //    if (correct_password == password) return true;
  // �Ƽ�ʹ�� readForLogin() ����Ϊ���ڷ��������ƥ�䣬���ܸ�Ϊ��ȫ��
  static bool readForLogin(const std::wstring& name,
                           const std::wstring& password);
  // �÷������ڶ�ȡ�ļ��ض��в�������ַ����С������������ܹ�����
  // ���в����طǿտ��ַ����������档��������Ϊ���·����
  // ʾ��:
  //    if (Reader::readFileLine(L"test.txt", 100, test_destination) {
  //      std::wcout << test_destination << std::endl;
  //    }
  static bool readFileLine(const std::wstring& file_name,
                           unsigned int row_number, std::wstring& destination);
  // ����ɾ�������ļ������ض��У�����ʱ�����档����Ϊ�ļ�����Ҫɾ�����е����ݡ�
  // ��������Ϊ���·����
  // ʾ����
  //    Reader::deleteFileLine(L"test.txt", L"test");
  static bool deleteFileLine(const std::wstring& file_name,
                             const std::wstring& request_line);
  // ���ڽ��ض��ļ����ض��и�Ϊ�µ����ݡ���������Ϊ���·����
  // ʾ����
  // Reader::changeFileLine(L"test.txt", 1, L"test");
  static bool changeFileLine(const std::wstring& file_name,
                             unsigned int row_number,
                             const std::wstring& request_line);
  // ����ɾ���ļ�Ŀ¼��������Ŀ¼������Ŀ¼�������ṩ����ڿ�ִ���ļ���·����
  // �ɹ��򷵻��档
  // ʾ��:
  //    Reader::deleteDirectory(L"\\test_folder");
  static bool deleteDirectory(const std::wstring& directory_path);
  // �������ļ�ĩβ������У���ӵ���һ�������ɲ����������������·����
  // ʾ����
  //    Reader::appendLine(L"res/book.dat", L"Journey To The West");
  static bool appendLine(const std::wstring& file_name,
                         const std::wstring& new_line);
  // ���ڴ���Ŀ¼�����ṩ����ڿ�ִ���ļ���·�����ɹ��򷵻��档
  // ʾ����
  //    Reader::createDirectory(L"\\test_folder");
  static bool createDirectory(const std::wstring& directory_path);
  // ���ڴ����հ��ļ������ṩ����ڿ�ִ���ļ���·�����ɹ��򷵻��档
  // ʾ����
  //    Reader::createFile(L"test_text.txt");
  static bool createFile(const std::wstring& file_name);
  // �����ƶ��ļ���Ŀ¼�����ṩ����ڿ�ִ���ļ���·�����ɹ��򷵻��档
  // ʾ����
  //    Reader::moveFile(L"\\test_new_pos", L"\\test_old_pos");
  static bool moveFile(const std::wstring& new_name,
                       const std::wstring& old_name);

 private:
  Reader();
};
}  // namespace library_management_sys
#endif  // LMS_BASE_READER_BASE_H_