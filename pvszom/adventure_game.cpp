#include <easyx.h>
#include "adventure_game.h"
#include "Card.h"
std::vector<Card> cards;
void cardload() {
	cards.clear();
	for(int i=0,x=250;i<8;++i,x+=70) {
		cards.emplace_back(50, x, 5, "res\\images\\cards\\(" + std::to_string(i) + ").png", 63, 88);
	}
	cards[0].value = 25;
	cards[1].value = 200;
	cards[2].value = 50;
	cards[3].value = 50;
	cards[4].value = 50;
	cards[5].value = 175;
	cards[6].value = 150;
	cards[7].value = 100;
}
void cardupdate() {
	for (int i = 0; i < 8; ++i) {
		putimage(cards[i].x, cards[i].y, &cards[i].img);
	}
}


void adventure_game_Scene::load() {
	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shop, "res\\images\\adventure_game\\wd.jpg", 650, 100);
	cardload();
}

void adventure_game_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(160, 0, &shop);
	cardupdate();
	FlushBatchDraw();
	EndBatchDraw();
}