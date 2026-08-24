#pragma once
#include"scene.h"
#include"plant_pool.h"
struct level{
	int id;
	IMAGE img,hoverimg;
	plant_pool pool;
	int w=80, h=100;
	int hw = 100, hh = 120;
};
std::vector<level>levels();

