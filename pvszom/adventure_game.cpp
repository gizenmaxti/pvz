#include <easyx.h>
#include "adventure_game.h"
#include"plant_pool.h"
#include "plant_registry.h"
#include"input.h"
#include"UIconfig.h"
#include"tool.h"


void adventure_game_Scene::load() {
	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shopimg, "res\\images\\adventure_game\\wd.jpg", 650*0.9, 100*0.9);
	loadimage(&poolimg, "res\\images\\adventure_game\\poolimg.jpg",600*0.8,650*0.8);

	levelconfig = level_registry::instance().get_levelinfo(curlevel);
	pool = levelconfig.pool;
}
void adventure_game_Scene::poolrendering() {
	putimage(0, 90, &poolimg);
	int col=0,row=0;
	
	for (auto &i : pool.getplanttype()) {
		int x = 30 + (col * (plant_registry::instance().get_plant_info(i.t).w + 2)),
			y = 140 + (row * (plant_registry::instance().get_plant_info(i.t).h + 5)),
			w = plant_registry::instance().get_plant_info(i.t).w,
			h = plant_registry::instance().get_plant_info(i.t).h;
		putimage(x, y, &plant_registry::instance().get_plant_info(i.t).cardimg);
		if(!i.optional)
			putimagePNG(x, y, w, h, &UIconfig::instance().getblack(),180);
		col++;
		if (input::instance().ishover(x, y, w, h) && input::instance().isclicked()&&shop.size()<8&&i.optional) {
			shop.push_back(i.t);
			i.optional = false;
		}
		if (col % 7==0) {
			col = 0;
			row++;
		}
	}
}
void adventure_game_Scene::ready() {
	poolrendering();
	putimage(10, 0, &shopimg);
	int x, y = 5, col = 0;
	
	for (auto it = shop.begin(); it != shop.end();) {
		col++;
		int w = plant_registry::instance().get_plant_info(*it).w,
			h = plant_registry::instance().get_plant_info(*it).h;
		x =30 +(col * (w + 7));
		putimage(x, y, &plant_registry::instance().get_plant_info(*it).cardimg);
		if (input::instance().ishover(x, y, w, h) && input::instance().isclicked()) {
			Planttype removedType = *it;
			it=shop.erase(it);
			for (auto& i : pool.getplanttype()) {
				if (i.t == removedType) {
					i.optional = true;
				}
			}
		}
		else ++it;
	}
}

void adventure_game_Scene::shoprendering() {
	putimage(10, 0, &shopimg);
	int x, y = 5,col=0;
	for (auto i : shop) {
		col++;
		x = 30+ (col * (plant_registry::instance().get_plant_info(i).w + 7));
		putimage(x, y, &plant_registry::instance().get_plant_info(i).cardimg);
	}
}


void adventure_game_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	/*poolrendering();
	shoprendering();*/
	ready();
	FlushBatchDraw();
	EndBatchDraw();
}