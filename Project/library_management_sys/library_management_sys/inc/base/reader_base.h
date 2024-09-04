// * 文件：reader_base.h
// * 作者：麦天乐
// * 介绍：声明 Reader 类。
#include <string>

#include "inc/base/page_base.h"
#ifndef LMS_BASE_READER_BASE_H_
#define LMS_BASE_READER_BASE_H_
namespace library_management_sys {
// 静态类，读写数据文件并进行相关赋值。
class Reader {
 public:
  // 用于为 PageUnitEx 实例获取文件信息。如果文件不能被正常打开，返回假。
  // 读取之后 pageunit_list_head 的 PageUnit 成员保持为初始状态。参数
  // 可以为相对路径。
  // 示例：
  //    if (Reader::readForPointPaint(test_pageunit_ex, L"test.txt")) {
  //      PageUnitEx* test_pageunit_pointer;
  //      while ((test_pageunit_pointer = test_pageunit_ex.getNext()) != NULL)
  //        Page::pointPaint(test_pageunit_pointer->getPageUnit());
  //    }
  static bool readForPointPaint(PageUnitEx& pageunit_list_head,
                                const std::wstring& file_name);
  // 在数据文件中如果成功查询到名称和相应的密码，返回真。
  // 示例:
  //    std::wcin >> test_name;
  //    std::wcin >> test_password;
  //    if (Reader::readForLogin(test_name, test_password)) {
  //      std::wcout << "Password is correct!" << std::endl;
  //    }
  // 这等价于：
  //    std::wstring password_path = L"res/user/" + name + L"/password.txt";
  //    Reader::readFileLine(password_path, 1, correct_password);
  //    if (correct_password == password) return true;
  // 推荐使用 readForLogin() ，因为其在方法内完成匹配，可能更为安全。
  static bool readForLogin(const std::wstring& name,
                           const std::wstring& password);
  // 该方法用于读取文件特定行并存入宽字符串中。如果这个方法能够正常
  // 进行并返回非空宽字符串，返回真。参数可以为相对路径。
  // 示例:
  //    if (Reader::readFileLine(L"test.txt", 100, test_destination) {
  //      std::wcout << test_destination << std::endl;
  //    }
  static bool readFileLine(const std::wstring& file_name,
                           unsigned int row_number, std::wstring& destination);
  // 用于删除给定文件名的特定行，正常时返回真。参数为文件名与要删除的行的内容。
  // 参数可以为相对路径。
  // 示例：
  //    Reader::deleteFileLine(L"test.txt", L"test");
  static bool deleteFileLine(const std::wstring& file_name,
                             const std::wstring& request_line);
  // 用于将特定文件的特定行改为新的内容。参数可以为相对路径。
  // 示例：
  // Reader::changeFileLine(L"test.txt", 1, L"test");
  static bool changeFileLine(const std::wstring& file_name,
                             unsigned int row_number,
                             const std::wstring& request_line);
  // 用于删除文件目录。不允许目录中有子目录，且需提供相对于可执行文件的路径。
  // 成功则返回真。
  // 示例:
  //    Reader::deleteDirectory(L"\\test_folder");
  static bool deleteDirectory(const std::wstring& directory_path);
  // 用于在文件末尾添加新行，添加的新一行内容由参数给定。允许相对路径。
  // 示例：
  //    Reader::appendLine(L"res/book.dat", L"Journey To The West");
  static bool appendLine(const std::wstring& file_name,
                         const std::wstring& new_line);
  // 用于创建目录。需提供相对于可执行文件的路径。成功则返回真。
  // 示例：
  //    Reader::createDirectory(L"\\test_folder");
  static bool createDirectory(const std::wstring& directory_path);
  // 用于创建空白文件。需提供相对于可执行文件的路径。成功则返回真。
  // 示例：
  //    Reader::createFile(L"test_text.txt");
  static bool createFile(const std::wstring& file_name);
  // 用于移动文件和目录。需提供相对于可执行文件的路径。成功则返回真。
  // 示例：
  //    Reader::moveFile(L"\\test_new_pos", L"\\test_old_pos");
  static bool moveFile(const std::wstring& new_name,
                       const std::wstring& old_name);

 private:
  Reader();
};
}  // namespace library_management_sys
#endif  // LMS_BASE_READER_BASE_H_