// * 文件：statistic_base.h
// * 作者：麦天乐
// * 介绍：声明 Statistic 类。
#include <windows.h>

#include <string>
#ifndef LMS_BASE_STATISTIC_BASE_H_
#define LMS_BASE_STATISTIC_BASE_H_
namespace library_management_sys {
// 静态类，集成了一些图书管理统计的常见方法
class Statistic {
 public:
  // 将图书借阅记录保存到统计文件中，并附上时间戳。
  // 参数为借阅的图书名称和借阅的用户名称。
  static void saveBorrowRecord(const std::wstring& book_name,
                               const std::wstring& user_name);
  // 统计图书被用户借阅的次数，选择最受欢迎的图书名称作为返回值。
  static std::wstring getBestBook();
  // 统计用户借阅图书的次数，选择借阅最多的用户名称作为返回值。
  static std::wstring getBestReader();
  // 统计并返回借阅总数
  static size_t getBorrowNum();
  // 统计并返回某一天的借阅总数，参数为相对于标准时间起点的天数。
  static size_t getBorrowNum(unsigned short day);
  // 绘制借阅条形图，时间轴原点为标准时间起点。
  // 参数分别为条形图原点坐标、条形图高度、条形图宽度和条形宽度。
  static void graph(COORD origin, short height, short width, short col_width);
 private:
  Statistic();
};
}  // namespace library_management_sys
#endif  // LMS_BASE_STATISTIC_BASE_H_