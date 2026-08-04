#include "adventure.h"
#include "game.h"

void adventure_Scene::load() {
	loadimage(&background, "res\\images\\menuselect\\background.png", WIN_WIDTH, WIN_HEIGHT);
	loadimage(&background2, "res\\images\\menuselect\\background2.png", WIN_WIDTH-20, WIN_HEIGHT-50);
	loadimage(&return_button, "res\\images\\menuselect\\return_button.png", 120 , 80);

	std::string levelpath = "res\\images\\menuselect\\level\\level (";
	for(int i=1;i<=COUNT_LEVEL;++i) {
		loadimage(&levels[i-1].img, (levelpath + std::to_string(i) + ").jpg").c_str(), 80, 100);
		levels[i - 1].id = i;
	}
}

void adventure_Scene::draw_level() {
	int y = 120,row=0;
	for(int i=0;i<COUNT_LEVEL;++i) {
		if (i % 8 == 0&&i)y += 140,row=0;
		putimage(50 + row * 100, y, &levels[i].img);
		row++;
	}
}

void adventure_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(10, 25, &background2);
	putimagePNG(15, 25, &return_button);
	draw_level();
	FlushBatchDraw();
	EndBatchDraw();
}
