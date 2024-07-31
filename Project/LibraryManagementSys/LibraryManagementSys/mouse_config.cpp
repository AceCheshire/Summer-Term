#include"mouse_base.h"
#include"page_base.h"
#include<iostream>
#include<windows.h>

Mouse::Mouse() {
	handle_mouse_output_ = GetStdHandle(STD_OUTPUT_HANDLE);
	hwnd_mouse_foreground_ = GetForegroundWindow();
	point_mouse_pos_.x = point_mouse_pos_.y = 0;
	coord_mouse_pos_.X = coord_mouse_pos_.Y = 0;
	GetCurrentConsoleFont(handle_mouse_output_, FALSE, &console_font_);
	MoveWindow(hwnd_mouse_foreground_, 0, 0, kClassicWidth, kClassicHeight, TRUE);
}

std::string Mouse::hoverAndClick(PageUnitEx* source_text) {
	short x;
	short y;
	int counter = kMouseDetectGroupTimes;
	while (counter--) {
		GetCursorPos(&point_mouse_pos_);
		ScreenToClient(hwnd_mouse_foreground_, &point_mouse_pos_);
		x = (short)(point_mouse_pos_.x / console_font_.dwFontSize.Y * kFontRatio);
		y = (short)(point_mouse_pos_.y / console_font_.dwFontSize.Y / kRowInterval);
		coord_mouse_pos_ = { x,y };
		read_str_ = readCursorChars(source_text);
		if (KEY_DOWN(VK_LBUTTON) && !read_str_.empty())return read_str_;
		Sleep(kMouseDetectInterval);
	}
	return kDefaultReturn;
}

char Mouse::readChar(COORD coord_pos) {
	TCHAR cursor_hover_on_char[1];
	DWORD dword_char;
	if (ReadConsoleOutputCharacterW(handle_mouse_output_, cursor_hover_on_char, 1, coord_pos, &dword_char))
		return (char)cursor_hover_on_char[0];
	else return ' ';
}

std::string Mouse::readCursorChars(PageUnitEx* source_text) {
	COORD floating_left_pos = coord_mouse_pos_;
	COORD floating_right_pos = coord_mouse_pos_;
	floating_right_pos.X++;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	std::string read_string;
	char read_char;
	GetConsoleScreenBufferInfo(handle_mouse_output_, &csbi);
	while (((read_char = readChar(floating_right_pos)) != ' ') && (read_char != '\t') &&
		(read_char != '\n') && (read_char != '\0') &&
		(floating_right_pos.X <= csbi.srWindow.Right - csbi.srWindow.Left-1)) {
		char read_chars[2] = { read_char };
		SetConsoleTextAttribute(handle_mouse_output_, BACKGROUND_INTENSITY);
		SetConsoleCursorPosition(handle_mouse_output_, floating_right_pos);
		printf("%c", read_char);
		SetConsoleTextAttribute(handle_mouse_output_, GROUND_DEFAULT);
		read_string.append(read_chars);
		floating_right_pos.X++;
	}
	while (((read_char = readChar(floating_left_pos)) != ' ') && (read_char != '\t') &&
		(read_char != '\n') && (read_char != '\0') && (floating_left_pos.X >= 0)) {
		char read_chars[2] = { read_char };
		SetConsoleTextAttribute(handle_mouse_output_, BACKGROUND_INTENSITY);
		SetConsoleCursorPosition(handle_mouse_output_, floating_left_pos);
		printf("%c", read_char);
		SetConsoleTextAttribute(handle_mouse_output_, GROUND_DEFAULT);
		read_string.insert(0, read_chars);
		floating_left_pos.X--;
	}
	if (read_string != read_str_)popLastStr(source_text);
	return read_string;
}

void Mouse::popLastStr(PageUnitEx* source_text) {
	Page tmp_page;
	PageUnitEx* tmp_pointer = NULL;
	if (!read_str_.empty())tmp_pointer = source_text->findByText(read_str_);
	if (tmp_pointer != NULL) tmp_page.pointPaint(tmp_pointer->getPageUnit());
}