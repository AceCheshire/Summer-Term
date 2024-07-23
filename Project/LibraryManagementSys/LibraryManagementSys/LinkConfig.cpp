#include"LinkConst.h"
#include<iostream>
#include<windows.h>
using namespace std;

Link::Link(std::string ssymbolStr, Scene* nnextScene) :symbolStr(ssymbolStr), nextScene(nnextScene) {
}

Link::Link(char* ssymbolStr, Scene* nnextScene) throw(...){
	int errnum_heap_pointer = HEAP_POINTER_ERROR;
	try {
		nextScene = nnextScene;
		if (ssymbolStr != NULL)symbolStr = ssymbolStr;
		else throw errnum_heap_pointer;
	}
	catch (int errnum) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		cout << endl;
		cerr << "ERR: function Link | errnum " << errnum << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}
}

void Link::SwitchScene(std::string requestStr) {
	if (requestStr == symbolStr) {
		system("cls");
		nextScene->PrepareScene();
	}
}