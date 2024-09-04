// * 文件：app_const.h
// * 作者：麦天乐
// * 介绍：声明将在类定义中引用的常量。这些常量所处的命名空间名，是引用这些常量的类名的小写。
#include <windows.h>
#ifndef LMS_APP_CONST_H_
#define LMS_APP_CONST_H_
// 前景白色是前景红色、前景绿色和前景蓝色的加和。
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
// 默认前景色为前景白色
#define FOREGROUND_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
// 用户信息所在的文件夹名
#define kUserFolderPath(USER_NAME) L"\\res\\user\\" + (USER_NAME)
// 用户密码所在的文件名
#define kUserPasswordPath(USER_NAME) L"res/user/" + USER_NAME + L"/password.dat"
// 用户权限所在的文件名
#define kUserPermissionPath(USER_NAME) \
  L"res/user/" + USER_NAME + L"/permission.dat"
// 用户历史所在的文件名
#define kUserHistoryPath(USER_NAME) L"res/user/" + USER_NAME + L"/history.dat"
// 图书信息所在的文件夹名
#define kBookFolderPath(BOOK_NAME) L"\\res\\book\\" + BOOK_NAME
// 图书详情所在的文件名
#define kBookDetailPath(BOOK_NAME) L"res/book/" + BOOK_NAME + L"/detail.dat"
// 用于监测键盘特定按键被按下。示例:
//    if (kKeyDown(VK_LBUTTON)) {
//      std::wcout << "Left button is pressed down!";
//    }
#define kKeyDown(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
namespace library_management_sys {
namespace book {  // Book 类的常量
enum Order {
  // 在详情文件中，Book::author_（图书作者）所在的行号
  kAuthorOffset = 1,
  // 在详情文件中，Book::type_（图书类别）所在的行号
  kTypeOffset,
  // 在详情文件中，Book::state_（图书状态）所在的行号
  kStateOffset,
  // 在详情文件中，Book::description_（图书描述）所在的行号
  kDescriptionOffset,
  // 在详情文件中，Book::history_（图书借阅历史）所在的行号
  kHistoryOffset
};
}  // namespace book

namespace mouse {  // Mouse 类的常量
// 用于 Mouse::hoverAndClick()，表示在监测鼠标输入时的监测时间间隔。
constexpr DWORD kDetectInterval = 125;
// 用于 Mouse::hoverAndClick()，表示每轮检测需要对鼠标输入连续监测的次数。
constexpr short kDetectGroupTimes = 2;
// 用于 Mouse::hoverAndClick() 作为默认返回值。返回此值说明在控制台全屏情况下，
// 鼠标停留的位置没有监测到宽字符串输出。
// 注意： Link::symbol_str_（链接标识）的值不能和此值发生冲突（即有相同的值）。
constexpr wchar_t kDefaultReturn[] = L"__NULL__";

// 这是一个经验比值。控制台推荐的字体大小为 12（默认值）。满足此条件后，在预设的
// 屏幕大小下，等宽字体的字体大小应该为 16px 高，9.3px宽。
constexpr double kFontRatio = 16 / 9.3;
// 控制台字体的行距。1.2 为默认值。
constexpr double kRowInterval = 1.2;
// 预设屏幕宽度。
constexpr int kClassicWidth = 2560;
// 预设屏幕高度。
constexpr int kClassicHeight = 1440;
}  // namespace mouse

namespace reader {  // Reader 类的常量
// 用于 readForPointPaint()，表示页面单元的横坐标在场景数据文件行的起始位置。
constexpr int kXBase = 0;
// 用于 readForPointPaint()，表示页面单元的纵坐标在场景数据文件行的起始位置。
constexpr int kYBase = 4;
// 用于 readForPointPaint()，表示页面单元颜色信息在场景数据文件行的起始位置。
constexpr int kColorBase = 8;
// 用于 readForPointPaint()，表示页面单元高亮设置在场景数据文件行的起始位置。
constexpr int kHighlightBase = 13;
// 用于 readForPointPaint()，表示页面单元文本信息在场景数据文件行的起始位置。
constexpr int kStrBase = 15;
}  // namespace reader

namespace page {  // Page 类的常量
// 等价于前景白色（0x0007）加上背景黑色（0x0000）
constexpr WORD GROUND_DEFAULT = 0x0007;
}  // namespace page

namespace scheduler {  // Scheduler 类的常量
// 表示调度器可容纳并跳转的场景数
constexpr int kMaxJumpNum = 64;
// 表示调度器可容纳的链接数
constexpr int kMaxLinkNum = 256;
}  // namespace scheduler

namespace statistic {  // Statistic 类的常量
// 用于存放统计数据
constexpr wchar_t kStatisticDataSource[] = L"res/statistic.dat";
// 2024-08-01 00:00:00
constexpr int kTimeStampStart = 1722441600;
}

namespace scene {  // Scene 类的常量
// 限制每行输入的字数
constexpr int kAdviceLength = 80;
// 限制输入的特殊字符
constexpr wchar_t kSpecialChars[] = L"!@#$%^&*()_+-=;:,.\"\'?/[]{}\\|<>~";
// 当前语言的 Unicode 编码起点
constexpr wint_t kAnsiStart = (wint_t)0x4E00;
// 当前语言的 Unicode 编码终点
constexpr wint_t kAnsiEnd = (wint_t)0x9FBF;
}  // namespace scene

namespace detail_page {  // DetailPage 类的常量
// 表示门户场景在 checkLink() 中发出的任务指令。
// 应该与 search_page::PortalTask 和 portal_page::CheckMode 保持相同。
enum PortalTask { kUser = 1, kBook };
// 表示搜索场景在 checkLink() 中发出的任务指令。
// 应该与 search_page::CheckMode 保持相同。
enum SearchTask { kSearch = 1, kUp, kDown, kAdd, kDelete, kModify };
// 详情场景内链接对应的任务指令。
enum CheckMode {
  // 图书或用户名称
  kNameLink = 1,
  // 图书作者
  kAuthorLink,
  // 图书类型
  kTypeLink,
  // 图书描述
  kDescriptionLink,
  // 用户权限
  kPermissionLink,
  // 用户密码
  kPasswordLink,
  // 管理员添加新用户或图书
  kAddLink,
  // 管理员修改用户或图书信息
  kModifyLink,
  // 管理员取消当前操作
  kCancelLink,
  // 普通用户借阅图书
  kBorrowLink,
  // 普通用户归还图书
  kReturnLink,
  // 历史记录翻下一条
  kNextLink,
  // 历史记录翻上一条
  kLastLink
};
constexpr wchar_t kNameText[] = L"Name";      // 图书或用户名称提示词
constexpr wchar_t kAuthorText[] = L"Author";  // 图书作者提示词
constexpr wchar_t kTypeText[] = L"Type";      // 图书类型提示词
constexpr wchar_t kStateText[] = L"State";    // 图书类型提示词
constexpr wchar_t kDescriptionText[] = L"Description";  // 图书描述提示词
constexpr wchar_t kPasswordText[] = L"Password";        // 用户密码提示词
constexpr wchar_t kPermissionText[] = L"Permission";    // 用户权限提示词
constexpr wchar_t kAddText[] = L"Add";  // 添加新用户或图书提示词
constexpr wchar_t kModifyText[] = L"Modify";  // 修改用户或图书提示词信息
constexpr wchar_t kCancelText[] = L"Cancel";  // 取消当前操作提示词信息
constexpr wchar_t kHistoryText[] = L"History";  // 用户或图书提示词信息
constexpr wchar_t kReturnText[] = L"Return";    // 归还图书提示词信息
constexpr wchar_t kBorrowText[] = L"Borrow";    // 借阅图书提示词信息
constexpr wchar_t kNextText[] = L"+";    // 查看记录下一条提示词信息
constexpr wchar_t kLastText[] = L"-";    // 查看记录上一条提示词信息
// 用于载入 DetailPage 场景文本的数据文件（管理员新增用户）
constexpr wchar_t kPageDataSource1[] = L"res/detail_page_data_1.dat";
// 用于载入 DetailPage 场景文本的数据文件（管理员修改用户）
constexpr wchar_t kPageDataSource2[] = L"res/detail_page_data_2.dat";
// 用于载入 DetailPage 场景文本的数据文件（普通用户查看用户）
constexpr wchar_t kPageDataSource3[] = L"res/detail_page_data_3.dat";
// 用于载入 DetailPage 场景文本的数据文件（管理员新增图书）
constexpr wchar_t kPageDataSource4[] = L"res/detail_page_data_4.dat";
// 用于载入 DetailPage 场景文本的数据文件（管理员修改图书）
constexpr wchar_t kPageDataSource5[] = L"res/detail_page_data_5.dat";
// 用于载入 DetailPage 场景文本的数据文件（普通用户查看图书）
constexpr wchar_t kPageDataSource6[] = L"res/detail_page_data_6.dat";
constexpr WORD kModifyColor = FOREGROUND_BLUE;  // 链接 “Modify” 的颜色
constexpr WORD kAddColor = FOREGROUND_GREEN;    // 链接 “Add” 的颜色
// 链接 “Return” 的颜色
constexpr WORD kReturnColor = FOREGROUND_GREEN | FOREGROUND_RED;
// 链接 “Borrow” 的颜色
constexpr WORD kBorrowColor = FOREGROUND_GREEN | FOREGROUND_RED;
// 链接 “Cancel” 的颜色
constexpr WORD kCancelColor = FOREGROUND_RED;
constexpr COORD kModifyPos = {15, 5};  // 链接 “Modify” 的坐标
constexpr COORD kAddPos = {15, 5};     // 链接 “Add” 的坐标
constexpr COORD kReturnPos = {25, 5};  // 链接 “Return” 的坐标
constexpr COORD kBorrowPos = {15, 5};  // 链接 “Borrow” 的坐标
constexpr COORD kCancelPos = {25, 5};  // 链接 “Cancel” 的坐标
// DetailPage 中选中选项的指针图案
constexpr wchar_t kPointerText[] = L"*";
// DetailPage 中选中选项的指针颜色
constexpr WORD kPointerColor = FOREGROUND_GREEN | FOREGROUND_RED;
constexpr wchar_t kAdminText[] =
    L"Administrator";  // 管理员权限的标示，显示为用户权限。
constexpr wchar_t kGuestText[] = L"Guest";  // 普通权限的标示，显示为用户权限。
// DetailPage 中选中选项的指针与提示词之间的偏移坐标
constexpr COORD kPointerOffset = {-4, 0};
// 每条图书或用户借阅历史的单词数（按照空格隔开为一个单词）
constexpr int kHistoryLength = 3;
// 同时显示的历史记录条数
constexpr int kMaxHistoryNum = 10;
}  // namespace detail_page

namespace help_page {  // HelpPage 类的常量
// 用于载入 HelpPage 场景文本的数据文件
constexpr wchar_t kPageDataSource[] = L"res/help_page_data.dat";
}  // namespace help_page

namespace home_page {  // HomePage 类的常量
// 用于载入 HomePage 场景文本的数据文件
constexpr wchar_t kPageDataSource[] = L"res/home_page_data.dat";
// 主页内链接对应的任务指令
enum CheckMode { kExit = 1 };
}  // namespace home_page

namespace login_page {  // LoginPage 类的常量
// 用于载入 LoginPage 场景文本的数据文件
constexpr wchar_t kPageDataSource[] = L"res/login_page_data.dat";
constexpr wchar_t kNameText[] = L"ID / name:";  // 指出 ID / 名称位置的提示词
constexpr wchar_t kPasswordText[] = L"Password:";  // 指出密码位置的提示词
constexpr wchar_t kErrorText[] = L"(wrong?)";  // 输入有误时显示的文本
constexpr COORD kInputOffset = {11, 0};  // 输入框与提示词的偏移坐标
}  // namespace login_page

namespace portal_page {  // PortalPage 类的常量
// 门户场景内链接对应的任务指令。
// 应与 search_page::PortalTask 和 detail_page::PortalTask 保持一致。
enum CheckMode { kUser = 1, kBook, kExit };
// 用于载入 PortalPage 场景文本的数据文件
constexpr wchar_t kPageDataSource[] = L"res/portal_page_data.dat";
// 显示借阅量、用户名称和图书名称的偏移坐标
constexpr COORD kOutputOffset = {20, 0};
// 条形图的原点坐标
constexpr COORD kOrigin = {80, 30};
// 条形图的大小
constexpr COORD kGraphSize = {80, 15};
}  // namespace portal_page

namespace search_page {  // SearchPage 类的常量
// 表示门户场景在 checkLink() 中发出的任务指令。
// 应该与 portal_page::CheckMode 和 detail_page::PortalTask 保持相同。
enum PortalTask { kUser = 1, kBook };
// 搜索场景内链接对应的任务指令
// 应该与 detail_page::SearchTask 保持相同。
enum CheckMode { kSearch = 1, kUp, kDown, kAdd, kDelete, kModify };
// 用于载入 SearchPage 场景文本的数据文件
constexpr wchar_t kPageDataSource[] = L"res/search_page_data.dat";
constexpr wchar_t kUserDataSource[] = L"res/user/user.dat";  // 用户名概览
constexpr wchar_t kBookDataSource[] = L"res/book/book.dat";  // 图书名概览
constexpr wchar_t kStartPointText[] = L">";  // 搜索框起点提示词
// 无匹配结果时的提示语句
constexpr wchar_t kNotMatchText[] = L"Sorry, there are no results found";
// 搜索框与搜索框起点的偏移坐标
constexpr COORD kInputOffset = {2, 0};
// 第一条搜索结果与搜索框起点的偏移坐标
constexpr COORD kSearchOffset = {5, 2};
// 搜索结果各行之间的偏移坐标
constexpr COORD kRowOffset = {0, 2};
constexpr wchar_t kPointerText[] = L"*";  // 选择指针的图案
constexpr WORD kPointerColor =
    FOREGROUND_GREEN | FOREGROUND_RED;  // 选择指针的颜色
// 选择指针与搜索结果之间的偏移坐标
constexpr COORD kPointerOffset = {-5, 0};
// 显示在屏幕上的搜索结果数量
constexpr unsigned short kMaxSearchNum = 10;
}  // namespace search_page
}  // namespace library_management_sys
#endif  // LMS_APP_CONST_H_