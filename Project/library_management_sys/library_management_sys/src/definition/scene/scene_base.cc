// * �ļ���scene_base.cc
// * ���ߣ�������
// * ���ܣ����� Scene �ࡣ
#include "inc/base/scene_base.h"

#include <conio.h>

#include <iostream>
#include <string>
#include <tuple>

#include "inc/app_const.h" 
#include "inc/base/page_base.h"
namespace library_management_sys {
Scene::Scene(PageUnitEx& pageunit_list_head)
    : pageunit_list_head_(&pageunit_list_head) {}

SharedScene::SharedScene(PageUnitEx& pageunit_list_head)
    : Scene(pageunit_list_head) {}

// SharedPool �ĳ�ʼ��
User SharedPool::current_user_;
User SharedPool::searching_user_;
Book SharedPool::searching_book_;
int SharedPool::shared_task_ = 0;

void Scene::layoutText() {
  PageUnitEx* iterator = pageunit_list_head_;
  while (iterator != NULL) {  // ��������Ԫ��
    Page::pointPaint(iterator->pos_, iterator->color_, iterator->text_);
    iterator = iterator->getNext();
  }
}

std::wstring Scene::inputLine(bool space, bool num, bool en, bool sp, bool ansi,
                              const wchar_t& fill_char) {
  std::wstring tmp_string;
  wchar_t tmp_char;
  while ((tmp_char = _getwch()) != L'\r') {  // ����س�
    if (tmp_char == 224 || tmp_char == 0)
      std::ignore = _getwch();                             // ������ư���
    if (((en && L'A' <= tmp_char && tmp_char <= 'Z') ||    // Ӣ����ĸ��д
         (en && L'a' <= tmp_char && tmp_char <= L'z') ||   // Ӣ����ĸСд
         (space && tmp_char == L' ') ||                    // �ո�
         (num && L'0' <= tmp_char && tmp_char <= L'9') ||  // ����
         (sp && (std::wstring(scene::kSpecialChars).find(tmp_char)) !=
                    std::wstring::npos) ||          // �����ַ�
         (ansi && scene::kAnsiStart <= tmp_char &&  // ��ǰ���Ա����ַ�
          tmp_char <= scene::kAnsiEnd)) &&
        tmp_string.length() <= scene::kAdviceLength) {  // �������볤��
      std::wcout << ((fill_char == L'\0') ? tmp_char
                                          : fill_char);  // ��ʾ�����ַ�
      tmp_string.push_back(tmp_char);  // ����������ַ�
    } else if (tmp_char == L'\b' && tmp_string.length()) {  // �����˸�
      if (19968U <= tmp_string.back() && tmp_string.back() <= 40895U)
        std::wcout << L"\b \b";
      std::wcout << L"\b \b";  // ɾ����ʾ�ַ�����������ɾ������
      tmp_string.pop_back();   // ������ɾ���ַ�
    }
  }
  return tmp_string;
}
}  // namespace library_management_sys