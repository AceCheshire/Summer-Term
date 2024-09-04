// * �ļ���app_const.h
// * ���ߣ�������
// * ���ܣ����������ඨ�������õĳ�������Щ���������������ռ�������������Щ������������Сд��
#include <windows.h>
#ifndef LMS_APP_CONST_H_
#define LMS_APP_CONST_H_
// ǰ����ɫ��ǰ����ɫ��ǰ����ɫ��ǰ����ɫ�ļӺ͡�
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
// Ĭ��ǰ��ɫΪǰ����ɫ
#define FOREGROUND_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
// �û���Ϣ���ڵ��ļ�����
#define kUserFolderPath(USER_NAME) L"\\res\\user\\" + (USER_NAME)
// �û��������ڵ��ļ���
#define kUserPasswordPath(USER_NAME) L"res/user/" + USER_NAME + L"/password.dat"
// �û�Ȩ�����ڵ��ļ���
#define kUserPermissionPath(USER_NAME) \
  L"res/user/" + USER_NAME + L"/permission.dat"
// �û���ʷ���ڵ��ļ���
#define kUserHistoryPath(USER_NAME) L"res/user/" + USER_NAME + L"/history.dat"
// ͼ����Ϣ���ڵ��ļ�����
#define kBookFolderPath(BOOK_NAME) L"\\res\\book\\" + BOOK_NAME
// ͼ���������ڵ��ļ���
#define kBookDetailPath(BOOK_NAME) L"res/book/" + BOOK_NAME + L"/detail.dat"
// ���ڼ������ض����������¡�ʾ��:
//    if (kKeyDown(VK_LBUTTON)) {
//      std::wcout << "Left button is pressed down!";
//    }
#define kKeyDown(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
namespace library_management_sys {
namespace book {  // Book ��ĳ���
enum Order {
  // �������ļ��У�Book::author_��ͼ�����ߣ����ڵ��к�
  kAuthorOffset = 1,
  // �������ļ��У�Book::type_��ͼ��������ڵ��к�
  kTypeOffset,
  // �������ļ��У�Book::state_��ͼ��״̬�����ڵ��к�
  kStateOffset,
  // �������ļ��У�Book::description_��ͼ�����������ڵ��к�
  kDescriptionOffset,
  // �������ļ��У�Book::history_��ͼ�������ʷ�����ڵ��к�
  kHistoryOffset
};
}  // namespace book

namespace mouse {  // Mouse ��ĳ���
// ���� Mouse::hoverAndClick()����ʾ�ڼ���������ʱ�ļ��ʱ������
constexpr DWORD kDetectInterval = 125;
// ���� Mouse::hoverAndClick()����ʾÿ�ּ����Ҫ����������������Ĵ�����
constexpr short kDetectGroupTimes = 2;
// ���� Mouse::hoverAndClick() ��ΪĬ�Ϸ���ֵ�����ش�ֵ˵���ڿ���̨ȫ������£�
// ���ͣ����λ��û�м�⵽���ַ��������
// ע�⣺ Link::symbol_str_�����ӱ�ʶ����ֵ���ܺʹ�ֵ������ͻ��������ͬ��ֵ����
constexpr wchar_t kDefaultReturn[] = L"__NULL__";

// ����һ�������ֵ������̨�Ƽ��������СΪ 12��Ĭ��ֵ�����������������Ԥ���
// ��Ļ��С�£��ȿ�����������СӦ��Ϊ 16px �ߣ�9.3px��
constexpr double kFontRatio = 16 / 9.3;
// ����̨������оࡣ1.2 ΪĬ��ֵ��
constexpr double kRowInterval = 1.2;
// Ԥ����Ļ��ȡ�
constexpr int kClassicWidth = 2560;
// Ԥ����Ļ�߶ȡ�
constexpr int kClassicHeight = 1440;
}  // namespace mouse

namespace reader {  // Reader ��ĳ���
// ���� readForPointPaint()����ʾҳ�浥Ԫ�ĺ������ڳ��������ļ��е���ʼλ�á�
constexpr int kXBase = 0;
// ���� readForPointPaint()����ʾҳ�浥Ԫ���������ڳ��������ļ��е���ʼλ�á�
constexpr int kYBase = 4;
// ���� readForPointPaint()����ʾҳ�浥Ԫ��ɫ��Ϣ�ڳ��������ļ��е���ʼλ�á�
constexpr int kColorBase = 8;
// ���� readForPointPaint()����ʾҳ�浥Ԫ���������ڳ��������ļ��е���ʼλ�á�
constexpr int kHighlightBase = 13;
// ���� readForPointPaint()����ʾҳ�浥Ԫ�ı���Ϣ�ڳ��������ļ��е���ʼλ�á�
constexpr int kStrBase = 15;
}  // namespace reader

namespace page {  // Page ��ĳ���
// �ȼ���ǰ����ɫ��0x0007�����ϱ�����ɫ��0x0000��
constexpr WORD GROUND_DEFAULT = 0x0007;
}  // namespace page

namespace scheduler {  // Scheduler ��ĳ���
// ��ʾ�����������ɲ���ת�ĳ�����
constexpr int kMaxJumpNum = 64;
// ��ʾ�����������ɵ�������
constexpr int kMaxLinkNum = 256;
}  // namespace scheduler

namespace statistic {  // Statistic ��ĳ���
// ���ڴ��ͳ������
constexpr wchar_t kStatisticDataSource[] = L"res/statistic.dat";
// 2024-08-01 00:00:00
constexpr int kTimeStampStart = 1722441600;
}

namespace scene {  // Scene ��ĳ���
// ����ÿ�����������
constexpr int kAdviceLength = 80;
// ��������������ַ�
constexpr wchar_t kSpecialChars[] = L"!@#$%^&*()_+-=;:,.\"\'?/[]{}\\|<>~";
// ��ǰ���Ե� Unicode �������
constexpr wint_t kAnsiStart = (wint_t)0x4E00;
// ��ǰ���Ե� Unicode �����յ�
constexpr wint_t kAnsiEnd = (wint_t)0x9FBF;
}  // namespace scene

namespace detail_page {  // DetailPage ��ĳ���
// ��ʾ�Ż������� checkLink() �з���������ָ�
// Ӧ���� search_page::PortalTask �� portal_page::CheckMode ������ͬ��
enum PortalTask { kUser = 1, kBook };
// ��ʾ���������� checkLink() �з���������ָ�
// Ӧ���� search_page::CheckMode ������ͬ��
enum SearchTask { kSearch = 1, kUp, kDown, kAdd, kDelete, kModify };
// ���鳡�������Ӷ�Ӧ������ָ�
enum CheckMode {
  // ͼ����û�����
  kNameLink = 1,
  // ͼ������
  kAuthorLink,
  // ͼ������
  kTypeLink,
  // ͼ������
  kDescriptionLink,
  // �û�Ȩ��
  kPermissionLink,
  // �û�����
  kPasswordLink,
  // ����Ա������û���ͼ��
  kAddLink,
  // ����Ա�޸��û���ͼ����Ϣ
  kModifyLink,
  // ����Աȡ����ǰ����
  kCancelLink,
  // ��ͨ�û�����ͼ��
  kBorrowLink,
  // ��ͨ�û��黹ͼ��
  kReturnLink,
  // ��ʷ��¼����һ��
  kNextLink,
  // ��ʷ��¼����һ��
  kLastLink
};
constexpr wchar_t kNameText[] = L"Name";      // ͼ����û�������ʾ��
constexpr wchar_t kAuthorText[] = L"Author";  // ͼ��������ʾ��
constexpr wchar_t kTypeText[] = L"Type";      // ͼ��������ʾ��
constexpr wchar_t kStateText[] = L"State";    // ͼ��������ʾ��
constexpr wchar_t kDescriptionText[] = L"Description";  // ͼ��������ʾ��
constexpr wchar_t kPasswordText[] = L"Password";        // �û�������ʾ��
constexpr wchar_t kPermissionText[] = L"Permission";    // �û�Ȩ����ʾ��
constexpr wchar_t kAddText[] = L"Add";  // ������û���ͼ����ʾ��
constexpr wchar_t kModifyText[] = L"Modify";  // �޸��û���ͼ����ʾ����Ϣ
constexpr wchar_t kCancelText[] = L"Cancel";  // ȡ����ǰ������ʾ����Ϣ
constexpr wchar_t kHistoryText[] = L"History";  // �û���ͼ����ʾ����Ϣ
constexpr wchar_t kReturnText[] = L"Return";    // �黹ͼ����ʾ����Ϣ
constexpr wchar_t kBorrowText[] = L"Borrow";    // ����ͼ����ʾ����Ϣ
constexpr wchar_t kNextText[] = L"+";    // �鿴��¼��һ����ʾ����Ϣ
constexpr wchar_t kLastText[] = L"-";    // �鿴��¼��һ����ʾ����Ϣ
// �������� DetailPage �����ı��������ļ�������Ա�����û���
constexpr wchar_t kPageDataSource1[] = L"res/detail_page_data_1.dat";
// �������� DetailPage �����ı��������ļ�������Ա�޸��û���
constexpr wchar_t kPageDataSource2[] = L"res/detail_page_data_2.dat";
// �������� DetailPage �����ı��������ļ�����ͨ�û��鿴�û���
constexpr wchar_t kPageDataSource3[] = L"res/detail_page_data_3.dat";
// �������� DetailPage �����ı��������ļ�������Ա����ͼ�飩
constexpr wchar_t kPageDataSource4[] = L"res/detail_page_data_4.dat";
// �������� DetailPage �����ı��������ļ�������Ա�޸�ͼ�飩
constexpr wchar_t kPageDataSource5[] = L"res/detail_page_data_5.dat";
// �������� DetailPage �����ı��������ļ�����ͨ�û��鿴ͼ�飩
constexpr wchar_t kPageDataSource6[] = L"res/detail_page_data_6.dat";
constexpr WORD kModifyColor = FOREGROUND_BLUE;  // ���� ��Modify�� ����ɫ
constexpr WORD kAddColor = FOREGROUND_GREEN;    // ���� ��Add�� ����ɫ
// ���� ��Return�� ����ɫ
constexpr WORD kReturnColor = FOREGROUND_GREEN | FOREGROUND_RED;
// ���� ��Borrow�� ����ɫ
constexpr WORD kBorrowColor = FOREGROUND_GREEN | FOREGROUND_RED;
// ���� ��Cancel�� ����ɫ
constexpr WORD kCancelColor = FOREGROUND_RED;
constexpr COORD kModifyPos = {15, 5};  // ���� ��Modify�� ������
constexpr COORD kAddPos = {15, 5};     // ���� ��Add�� ������
constexpr COORD kReturnPos = {25, 5};  // ���� ��Return�� ������
constexpr COORD kBorrowPos = {15, 5};  // ���� ��Borrow�� ������
constexpr COORD kCancelPos = {25, 5};  // ���� ��Cancel�� ������
// DetailPage ��ѡ��ѡ���ָ��ͼ��
constexpr wchar_t kPointerText[] = L"*";
// DetailPage ��ѡ��ѡ���ָ����ɫ
constexpr WORD kPointerColor = FOREGROUND_GREEN | FOREGROUND_RED;
constexpr wchar_t kAdminText[] =
    L"Administrator";  // ����ԱȨ�޵ı�ʾ����ʾΪ�û�Ȩ�ޡ�
constexpr wchar_t kGuestText[] = L"Guest";  // ��ͨȨ�޵ı�ʾ����ʾΪ�û�Ȩ�ޡ�
// DetailPage ��ѡ��ѡ���ָ������ʾ��֮���ƫ������
constexpr COORD kPointerOffset = {-4, 0};
// ÿ��ͼ����û�������ʷ�ĵ����������տո����Ϊһ�����ʣ�
constexpr int kHistoryLength = 3;
// ͬʱ��ʾ����ʷ��¼����
constexpr int kMaxHistoryNum = 10;
}  // namespace detail_page

namespace help_page {  // HelpPage ��ĳ���
// �������� HelpPage �����ı��������ļ�
constexpr wchar_t kPageDataSource[] = L"res/help_page_data.dat";
}  // namespace help_page

namespace home_page {  // HomePage ��ĳ���
// �������� HomePage �����ı��������ļ�
constexpr wchar_t kPageDataSource[] = L"res/home_page_data.dat";
// ��ҳ�����Ӷ�Ӧ������ָ��
enum CheckMode { kExit = 1 };
}  // namespace home_page

namespace login_page {  // LoginPage ��ĳ���
// �������� LoginPage �����ı��������ļ�
constexpr wchar_t kPageDataSource[] = L"res/login_page_data.dat";
constexpr wchar_t kNameText[] = L"ID / name:";  // ָ�� ID / ����λ�õ���ʾ��
constexpr wchar_t kPasswordText[] = L"Password:";  // ָ������λ�õ���ʾ��
constexpr wchar_t kErrorText[] = L"(wrong?)";  // ��������ʱ��ʾ���ı�
constexpr COORD kInputOffset = {11, 0};  // ���������ʾ�ʵ�ƫ������
}  // namespace login_page

namespace portal_page {  // PortalPage ��ĳ���
// �Ż����������Ӷ�Ӧ������ָ�
// Ӧ�� search_page::PortalTask �� detail_page::PortalTask ����һ�¡�
enum CheckMode { kUser = 1, kBook, kExit };
// �������� PortalPage �����ı��������ļ�
constexpr wchar_t kPageDataSource[] = L"res/portal_page_data.dat";
// ��ʾ���������û����ƺ�ͼ�����Ƶ�ƫ������
constexpr COORD kOutputOffset = {20, 0};
// ����ͼ��ԭ������
constexpr COORD kOrigin = {80, 30};
// ����ͼ�Ĵ�С
constexpr COORD kGraphSize = {80, 15};
}  // namespace portal_page

namespace search_page {  // SearchPage ��ĳ���
// ��ʾ�Ż������� checkLink() �з���������ָ�
// Ӧ���� portal_page::CheckMode �� detail_page::PortalTask ������ͬ��
enum PortalTask { kUser = 1, kBook };
// �������������Ӷ�Ӧ������ָ��
// Ӧ���� detail_page::SearchTask ������ͬ��
enum CheckMode { kSearch = 1, kUp, kDown, kAdd, kDelete, kModify };
// �������� SearchPage �����ı��������ļ�
constexpr wchar_t kPageDataSource[] = L"res/search_page_data.dat";
constexpr wchar_t kUserDataSource[] = L"res/user/user.dat";  // �û�������
constexpr wchar_t kBookDataSource[] = L"res/book/book.dat";  // ͼ��������
constexpr wchar_t kStartPointText[] = L">";  // �����������ʾ��
// ��ƥ����ʱ����ʾ���
constexpr wchar_t kNotMatchText[] = L"Sorry, there are no results found";
// ������������������ƫ������
constexpr COORD kInputOffset = {2, 0};
// ��һ���������������������ƫ������
constexpr COORD kSearchOffset = {5, 2};
// �����������֮���ƫ������
constexpr COORD kRowOffset = {0, 2};
constexpr wchar_t kPointerText[] = L"*";  // ѡ��ָ���ͼ��
constexpr WORD kPointerColor =
    FOREGROUND_GREEN | FOREGROUND_RED;  // ѡ��ָ�����ɫ
// ѡ��ָ�����������֮���ƫ������
constexpr COORD kPointerOffset = {-5, 0};
// ��ʾ����Ļ�ϵ������������
constexpr unsigned short kMaxSearchNum = 10;
}  // namespace search_page
}  // namespace library_management_sys
#endif  // LMS_APP_CONST_H_