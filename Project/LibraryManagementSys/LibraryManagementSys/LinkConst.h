#pragma once
#include<iostream>
#include"SceneConst.h"
#define HEAP_POINTER_ERROR 3

class Link {
public:
	Link(std::string, Scene*);
	Link(char*, Scene*) throw(...);
	void SwitchScene(std::string);
private:
	std::string symbolStr;
	Scene* nextScene;
};