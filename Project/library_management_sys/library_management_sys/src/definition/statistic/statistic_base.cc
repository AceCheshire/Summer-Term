// * 文件：statistic_base.cc
// * 作者：麦天乐
// * 介绍：定义 Statistic 类。
#include "inc/base/statistic_base.h" 

#include <chrono>
#include <map>
#include <string>

#include "inc/base/page_base.h"
#include "inc/base/reader_base.h"
namespace library_management_sys {
void Statistic::saveBorrowRecord(const std::wstring& book_name,
                                 const std::wstring& user_name) {
  size_t sec_stamp = std::chrono::system_clock::now().time_since_epoch() /
                  std::chrono::seconds(1);  // 获得秒时间戳
  size_t day_stamp = (sec_stamp - statistic::kTimeStampStart) / 86400;  // 换算
  // 存入借阅记录
  Reader::appendLine(statistic::kStatisticDataSource, book_name);
  Reader::appendLine(statistic::kStatisticDataSource, user_name);
  Reader::appendLine(statistic::kStatisticDataSource,
                     std::to_wstring(day_stamp));
}

std::wstring Statistic::getBestBook() {
  unsigned int row_iterator = 1;
  std::wstring row_data;  // 暂存文件行数据
  std::map<std::wstring, int> frequency;
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data)) {
    if (row_iterator % 3 == 1) frequency[row_data]++;  // 统计书名频率
    row_iterator++;                                    // 计算行号
  }
  if (!frequency.empty()) {  // 返回最大值键
    return frequency.rbegin()->first;
  } else {
    return L"Unknown";
  }
}

std::wstring Statistic::getBestReader() {
  unsigned int row_iterator = 1;
  std::wstring row_data;  // 暂存文件行数据
  std::map<std::wstring, size_t> frequency;
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data)) {
    if (row_iterator % 3 == 2) frequency[row_data]++;  // 统计用户名频率
    row_iterator++;                                    // 计算行号
  }
  if (!frequency.empty()) {  // 返回最大值键
    return frequency.rbegin()->first;
  } else {
    return L"Unknown";
  }
}

size_t Statistic::getBorrowNum() {
  unsigned int row_iterator = 1;
  std::wstring row_data;  // 暂存文件行数据
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data))
    row_iterator++;
  return (row_iterator - 1) / 3;  // 返回文件行数除三（由 statistic ）结构决定
}

size_t Statistic::getBorrowNum(unsigned short day) {
  unsigned int row_iterator = 1;
  size_t counter = 0;
  std::wstring row_data;  // 暂存文件行数据
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data)) {
    if (row_iterator % 3 == 0)
      if (day == _wtoi(row_data.c_str())) counter++;  // 若时间符合，计数器加一
    row_iterator++;
  }
  return counter;
}

void Statistic::graph(COORD origin, short height, short width,
                      short col_width) {
  size_t value[200] = {};
  size_t max_value = 0;
  for (int i = 0; i < 200; i++) {  // 获得数据与最大值
    value[i] = getBorrowNum(i);
    max_value = (value[i] > max_value) ? value[i] : max_value;
  }
  // 绘制原点
  Page::pointPaint(origin, page::GROUND_DEFAULT, L"└");
  // 绘制横纵轴箭头
  Page::pointPaint(origin.X, origin.Y - height, page::GROUND_DEFAULT, L"┬");
  Page::pointPaint(origin.X + width, origin.Y, page::GROUND_DEFAULT, L"┤");
  // 补全横轴
  for (int i = 1; i < width; i++)
    Page::pointPaint(origin.X + i, origin.Y, page::GROUND_DEFAULT, L"─");
  // 补全纵轴
  for (int j = 1; j < height; j++)
    Page::pointPaint(origin.X, origin.Y - j, page::GROUND_DEFAULT, L"│");
  // 绘制条形
  if (!max_value) return;  // 当未检测到借阅记录时，不绘制条形
  for (int i = 1; i < width; i++) {
    int col_height = value[(i - 1) / col_width] * height / max_value;
    if (col_height > 0)
      Page::pointPaint(origin.X + i, origin.Y, page::GROUND_DEFAULT, L"╨");
    for (int j = 1; j < col_height; j++)
      Page::pointPaint(origin.X + i, origin.Y - j, page::GROUND_DEFAULT, L"║");
  }
}
}  // namespace library_management_sys