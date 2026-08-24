#include<easyx.h>
#include"plant_pool.h"
enum class level {
	level_1,
	level_2
};
struct levelinfo {
	int id;
	IMAGE img, hoverimg;
	int w, h, ww, hh;
	plant_pool pool;
};