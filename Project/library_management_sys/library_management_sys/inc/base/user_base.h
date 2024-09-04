// * �ļ���user_base.h
// * ���ߣ�������
// * ���ܣ����� User �ࡣ
#include <string>
#ifndef LMS_BASE_USER_BASE_H_
#define LMS_BASE_USER_BASE_H_
namespace library_management_sys {
// �����û���Ϣ���ṩ���з��ʽӿڡ�
// ʾ����
//    User test_user;
class User {
 public:
  // ���ĳ�Ա name_��������һ�� updateInfo()��
  void setName(const std::wstring& user_name);
  // ���� name_ ��ֵ���� User ʵ���еĳ�Ա��
  void updateInfo();
  void setPermission(bool user_permission) { permission_ = user_permission; }
  // �ڳ�Ա history_ ��ĩβ��������ʷ��¼��
  // ��һ����������Ϊ��ǣ��ڶ����������û����ơ�
  void appendHistory(const std::wstring& declaration, const std::wstring& name);
  // ��� User ʵ���ĳ�Ա��
  void clear();
  // �����û���Ϣ���ļ��У�����Ϊ���û����ƺ�ϣ���޸ĵ����루���޸Ĳ�����ɹ������档
  bool saveUser(const std::wstring& old_name,
                const std::wstring& password_request = L"") const;
  // �����û��ļ��У�����Ϊϣ���޸ĵ����룬�ɹ������档
  bool addUser(const std::wstring& password_request) const;
  std::wstring getName() const { return name_; }
  bool checkPermission() const { return permission_; }
  std::wstring getHistory() const { return history_; }

 protected:
  // ��¼�û�����
  std::wstring name_;
  // ��¼�û��Ƿ�ӵ�и�����Ϣ��Ȩ�ޡ�
  // ����Ϊ���������д��Ϣ������Ϊ������ϢΪֻ����
  bool permission_ = false;
  // ��¼�û���ʷ
  std::wstring history_;
};
}  // namespace library_management_sys
#endif  // LMS_BASE_USER_BASE_H_