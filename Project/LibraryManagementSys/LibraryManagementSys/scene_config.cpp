#include"error_base.h"
#include"scene_base.h"
#include<iostream>

Scene::Scene(Mouse* attached_mouse,Scene* prev_scene,PageUnitEx* pageunit_list_head) 
	:attached_mouse_(attached_mouse),prev_scene_(prev_scene),pageunit_list_head_(pageunit_list_head){
}