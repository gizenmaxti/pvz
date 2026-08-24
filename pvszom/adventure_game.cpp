#include <easyx.h>
#include "adventure_game.h"
#include "Card.h"
#include"plant_pool.h"
#include "plant_registry.h"
std::vector<Card> cards;
plant_pool pool;

void cardload() {
	
	plant_registry::instance().load();
}
void poolload() {
	pool.add_plant(plant_card(Planttype::peashooter));
	pool.add_plant(plant_card(Planttype::peashooter));
	pool.add_plant(plant_card(Planttype::peashooter));
	pool.add_plant(plant_card(Planttype::peashooter));
	pool.add_plant(plant_card(Planttype::peashooter));
	
}


void adventure_game_Scene::load() {
	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shop, "res\\images\\adventure_game\\wd.jpg", 650, 100);
	cardload();
	poolload();
}

void adventure_game_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(160, 0, &shop);
	pool.update();
	FlushBatchDraw();
	EndBatchDraw();
}