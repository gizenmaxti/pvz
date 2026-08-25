#include <easyx.h>
#include "adventure_game.h"
#include"plant_pool.h"
#include "plant_registry.h"
#include"input.h"

void adventure_game_Scene::load() {
	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shop, "res\\images\\adventure_game\\wd.jpg", 650*0.9, 100*0.9);
	loadimage(&poolimg, "res\\images\\adventure_game\\poolimg.jpg",600*0.8,650*0.8);

	levelconfig = level_registry::instance().get_levelinfo(curlevel);
	pool = levelconfig.pool;
}
void adventure_game_Scene::poolrendering() {
	int col=0,row=0;
	/*auto &pooltypes =pool.getplanttype();
	for (auto it = pooltypes.begin(); it != pooltypes.end();) {
		Planttype i = *it;
		int x = 30 + (col * (plant_registry::instance().get_plant_info(i).w + 2));
		int y = 140 + (row * (plant_registry::instance().get_plant_info(i).h + 5));
		putimage(x, y, &plant_registry::instance().get_plant_info(i).cardimg);
		col++;
		if (input::instance().ishover(x, y, plant_registry::instance().get_plant_info(i).w, plant_registry::instance().get_plant_info(i).h) && input::instance().isclicked()) {
			product.push_back(i);
			it = pooltypes.erase(it);
		}
		if (col % 6 == 0) {
			col = 0;
			row++;
		}
	}*/
	for (auto i : pool.getplanttype()) {
		int x = 30 + (col* (plant_registry::instance().get_plant_info(i).w+2));
		int y = 140 + (row * (plant_registry::instance().get_plant_info(i).h+5));
		putimage(x, y, &plant_registry::instance().get_plant_info(i).cardimg);
		col++;
		if (input::instance().ishover(x, y, plant_registry::instance().get_plant_info(i).w, plant_registry::instance().get_plant_info(i).h) && input::instance().isclicked()) {
			product.push_back(i);
			
		}
		if (col % 6==0) {
			col = 0;
			row++;
		}
	}
}
void adventure_game_Scene::shoprendering() {
	int x = 100, y = 5,col=0;
	for (auto i : product) {
		col++;
		x = 30 + (col * (plant_registry::instance().get_plant_info(i).w + 2));
		putimage(x, y, &plant_registry::instance().get_plant_info(i).cardimg);
	}
}

void adventure_game_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(10, 0, &shop);
	putimage(0, 90, &poolimg);
	poolrendering();
	shoprendering();

	FlushBatchDraw();
	EndBatchDraw();
}