#pragma once
#include<iostream>
#include"SceneBase.h"

class Link {
public:
	Link(std::string, Scene*);
	Link(char*, Scene*) throw(...);
	void SwitchScene(std::string);
private:
	std::string symbolStr;
	Scene* nextScene;
};