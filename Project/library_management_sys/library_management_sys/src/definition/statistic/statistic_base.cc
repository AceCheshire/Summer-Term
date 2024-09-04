// * �ļ���statistic_base.cc
// * ���ߣ�������
// * ���ܣ����� Statistic �ࡣ
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
                  std::chrono::seconds(1);  // �����ʱ���
  size_t day_stamp = (sec_stamp - statistic::kTimeStampStart) / 86400;  // ����
  // ������ļ�¼
  Reader::appendLine(statistic::kStatisticDataSource, book_name);
  Reader::appendLine(statistic::kStatisticDataSource, user_name);
  Reader::appendLine(statistic::kStatisticDataSource,
                     std::to_wstring(day_stamp));
}

std::wstring Statistic::getBestBook() {
  unsigned int row_iterator = 1;
  std::wstring row_data;  // �ݴ��ļ�������
  std::map<std::wstring, int> frequency;
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data)) {
    if (row_iterator % 3 == 1) frequency[row_data]++;  // ͳ������Ƶ��
    row_iterator++;                                    // �����к�
  }
  if (!frequency.empty()) {  // �������ֵ��
    return frequency.rbegin()->first;
  } else {
    return L"Unknown";
  }
}

std::wstring Statistic::getBestReader() {
  unsigned int row_iterator = 1;
  std::wstring row_data;  // �ݴ��ļ�������
  std::map<std::wstring, size_t> frequency;
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data)) {
    if (row_iterator % 3 == 2) frequency[row_data]++;  // ͳ���û���Ƶ��
    row_iterator++;                                    // �����к�
  }
  if (!frequency.empty()) {  // �������ֵ��
    return frequency.rbegin()->first;
  } else {
    return L"Unknown";
  }
}

size_t Statistic::getBorrowNum() {
  unsigned int row_iterator = 1;
  std::wstring row_data;  // �ݴ��ļ�������
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data))
    row_iterator++;
  return (row_iterator - 1) / 3;  // �����ļ������������� statistic ���ṹ����
}

size_t Statistic::getBorrowNum(unsigned short day) {
  unsigned int row_iterator = 1;
  size_t counter = 0;
  std::wstring row_data;  // �ݴ��ļ�������
  while (Reader::readFileLine(statistic::kStatisticDataSource, row_iterator,
                              row_data)) {
    if (row_iterator % 3 == 0)
      if (day == _wtoi(row_data.c_str())) counter++;  // ��ʱ����ϣ���������һ
    row_iterator++;
  }
  return counter;
}

void Statistic::graph(COORD origin, short height, short width,
                      short col_width) {
  size_t value[200] = {};
  size_t max_value = 0;
  for (int i = 0; i < 200; i++) {  // ������������ֵ
    value[i] = getBorrowNum(i);
    max_value = (value[i] > max_value) ? value[i] : max_value;
  }
  // ����ԭ��
  Page::pointPaint(origin, page::GROUND_DEFAULT, L"��");
  // ���ƺ������ͷ
  Page::pointPaint(origin.X, origin.Y - height, page::GROUND_DEFAULT, L"��");
  Page::pointPaint(origin.X + width, origin.Y, page::GROUND_DEFAULT, L"��");
  // ��ȫ����
  for (int i = 1; i < width; i++)
    Page::pointPaint(origin.X + i, origin.Y, page::GROUND_DEFAULT, L"��");
  // ��ȫ����
  for (int j = 1; j < height; j++)
    Page::pointPaint(origin.X, origin.Y - j, page::GROUND_DEFAULT, L"��");
  // ��������
  if (!max_value) return;  // ��δ��⵽���ļ�¼ʱ������������
  for (int i = 1; i < width; i++) {
    int col_height = value[(i - 1) / col_width] * height / max_value;
    if (col_height > 0)
      Page::pointPaint(origin.X + i, origin.Y, page::GROUND_DEFAULT, L"�l");
    for (int j = 1; j < col_height; j++)
      Page::pointPaint(origin.X + i, origin.Y - j, page::GROUND_DEFAULT, L"�U");
  }
}
}  // namespace library_management_sys