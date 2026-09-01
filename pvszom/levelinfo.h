#pragma once
#include<easyx.h>
#include<memory>
#include"plant_pool.h"
#include"grassland.h"
enum class level {
	level_1,
	level_2
};

struct levelinfo {
	int id;
	IMAGE img, hoverimg;
	int w = 120, h = 120, ww = 140, hh = 140;
	plant_pool pool;
};