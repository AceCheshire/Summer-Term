// * �ļ���statistic_base.h
// * ���ߣ�������
// * ���ܣ����� Statistic �ࡣ
#include <windows.h>

#include <string>
#ifndef LMS_BASE_STATISTIC_BASE_H_
#define LMS_BASE_STATISTIC_BASE_H_
namespace library_management_sys {
// ��̬�࣬������һЩͼ�����ͳ�Ƶĳ�������
class Statistic {
 public:
  // ��ͼ����ļ�¼���浽ͳ���ļ��У�������ʱ�����
  // ����Ϊ���ĵ�ͼ�����ƺͽ��ĵ��û����ơ�
  static void saveBorrowRecord(const std::wstring& book_name,
                               const std::wstring& user_name);
  // ͳ��ͼ�鱻�û����ĵĴ�����ѡ�����ܻ�ӭ��ͼ��������Ϊ����ֵ��
  static std::wstring getBestBook();
  // ͳ���û�����ͼ��Ĵ�����ѡ����������û�������Ϊ����ֵ��
  static std::wstring getBestReader();
  // ͳ�Ʋ����ؽ�������
  static size_t getBorrowNum();
  // ͳ�Ʋ�����ĳһ��Ľ�������������Ϊ����ڱ�׼ʱ������������
  static size_t getBorrowNum(unsigned short day);
  // ���ƽ�������ͼ��ʱ����ԭ��Ϊ��׼ʱ����㡣
  // �����ֱ�Ϊ����ͼԭ�����ꡢ����ͼ�߶ȡ�����ͼ��Ⱥ����ο�ȡ�
  static void graph(COORD origin, short height, short width, short col_width);
 private:
  Statistic();
};
}  // namespace library_management_sys
#endif  // LMS_BASE_STATISTIC_BASE_H_