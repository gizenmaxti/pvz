#include <easyx.h>
#include "adventure_game.h"
#include "Card.h"
#include"plant_pool.h"
#include "plant_registry.h"

void adventure_game_Scene::load() {
	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shop, "res\\images\\adventure_game\\wd.jpg", 650, 100);
	loadimage(&poolimg, "res\\images\\adventure_game\\poolimg.jpg",600*0.8,650*0.8);
}
void adventure_game_Scene::poolrendering() {
	int x = 0, y = 0;
	for (auto i : pool.getplanttype()) {
		putimage(x, y, &plant_registry::instance().get_plant_info(i).cardimg);
	}
}

void adventure_game_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(160, 0, &shop);
	putimage(100, 100, &poolimg);
	poolrendering();

	FlushBatchDraw();
	EndBatchDraw();
}