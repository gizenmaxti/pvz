#pragma once
#include<easyx.h>
#include"plant_pool.h"
enum class level {
	level_1,
	level_2
};

struct levelinfo {
	int id;
	IMAGE img, hoverimg;
	int w=80, h=100, ww=100, hh=120;
	plant_pool pool;
};