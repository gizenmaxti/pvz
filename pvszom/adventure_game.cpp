#include <easyx.h>
#include "adventure_game.h"
#include"plant_pool.h"
#include "plant_registry.h"
#include"input.h"
#include"UIconfig.h"
#include"tool.h"
#include"grassland.h"

void adventure_game_Scene::load() {
	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shopimg, "res\\images\\adventure_game\\wd.jpg", 650 * 0.9, 100 * 0.9);
	loadimage(&poolimg, "res\\images\\adventure_game\\poolimg.jpg", 600 * 0.8, 650 * 0.8);
	start = std::make_unique<Basicbutton>(0, 0, 362 * 0.5, 80 * 0.5, "res\\images\\adventure_game\\game_start.png");
	levelconfig = level_registry::instance().get_levelinfo(curlevel);

	pool = levelconfig.pool;
}
void adventure_game_Scene::poolrendering() {
	putimage(0, 90, &poolimg);
	int col = 0, row = 0;

	for (auto& i : pool.getplanttype()) {
		int x = 30 + (col * (plant_registry::instance().get_plant_info(i.t).w + 2)),
			y = 140 + (row * (plant_registry::instance().get_plant_info(i.t).h + 5)),
			w = plant_registry::instance().get_plant_info(i.t).w,
			h = plant_registry::instance().get_plant_info(i.t).h;
		putimage(x, y, &plant_registry::instance().get_plant_info(i.t).cardimg);
		if (!i.optional)
			putimagePNG(x, y, w, h, &UIconfig::instance().getblack(), 180);
		col++;
		if (input::instance().ishover(x, y, w, h) && input::instance().isclicked() && shop.size() < 8 && i.optional) {
			shop.push_back(i.t);
			i.optional = false;
		}
		if (col % 7 == 0) {
			col = 0;
			row++;
		}
	}
}
void adventure_game_Scene::ready() {
	poolrendering();
	putimage(10, 0, &shopimg);
	if (input::instance().ishover(150, 555, start->getw(), start->geth())) {
		putimage(150, 555, &start->getimg());
		if (input::instance().isclicked()) {
			curprocess = process::fight;
		}
	}

	int x, y = 5, col = 0;

	for (auto it = shop.begin(); it != shop.end();) {
		col++;
		int w = plant_registry::instance().get_plant_info(it->t).w,
			h = plant_registry::instance().get_plant_info(it->t).h;
		x = 30 + (col * (w + 7));
		putimage(x, y, &plant_registry::instance().get_plant_info(it->t).cardimg);
		if (input::instance().ishover(x, y, w, h) && input::instance().isclicked()) {
			Planttype removedType = it->t;
			it = shop.erase(it);
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
	int x, y = 5, col = 0;
	for (auto i : shop) {
		col++;
		x = 30 + (col * (plant_registry::instance().get_plant_info(i.t).w + 7));
		putimage(x, y, &plant_registry::instance().get_plant_info(i.t).cardimg);
		if (input::instance().isdragging() && input::instance().ishover(x, y, plant_registry::instance().get_plant_info(i.t).w, plant_registry::instance().get_plant_info(i.t).h) && !selectplant) {
			selectplant = i.t;
		}
	}
	if (selectplant && input::instance().isleftdown()) {
		g.planting((input::instance().gety() - 100) / 100, (input::instance().getx() - 160) / 80, *selectplant);

	}
	if (selectplant && input::instance().isdragging()) {
		putimagePNG(input::instance().getx() - 30, input::instance().gety() - 30, &plant_registry::instance().get_plant_info(*selectplant).plantimg);
	}
	else {
		selectplant = std::nullopt;
	}
}


void adventure_game_Scene::fight() {
	shoprendering();
	g.update();
}


void adventure_game_Scene::update() {

	BeginBatchDraw();
	putimage(0, 0, &background);

	switch (curprocess) {
	case process::ready:
		ready(); break;
	case process::fight:
		fight(); break;
	case process::win:
		break;
	case process::fail:
		break;
	}
	FlushBatchDraw();
	EndBatchDraw();
}