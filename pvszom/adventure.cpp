#include "adventure.h"
#include "game.h"
#include "level_registry.h"
#include"levelinfo.h"
#include"input.h"
#include"SceneManager.h"
#include"adventure_game.h"

void adventure_Scene::load() {
	loadimage(&background, "res\\images\\menuselect\\background.jpg", WIN_WIDTH, WIN_HEIGHT);
	loadimage(&background2, "res\\images\\menuselect\\background2.png", WIN_WIDTH-20, WIN_HEIGHT-50);
	loadimage(&return_button, "res\\images\\menuselect\\return_button.jpg",288*0.5,64*0.5);
	loadimage(&return_bbutton, "res\\images\\menuselect\\return_button.jpg",288 * 0.6, 64*0.6);

	//level_registry::instance().load();
}
void adventure_Scene::returnbutton() {
	int x = 15, y = 570;
	if (input::instance().ishover(x, y, 288*0.5, 64*0.5)) {
		putimagePNG(x-10, y-10, &return_bbutton);
		if (input::instance().isclicked()) {
			SceneManager::instance().changeScene(Action::pop);
		}
	}else putimagePNG(x, y, &return_button);

}

void adventure_Scene::draw_level() {
	int y = 120, row = 0;
	for (auto k: level_registry::instance().getlevels()) {
		int i = 0;
		int x = 45 + row * 170;
		if (i % 8 == 0 && i)y += 140, row = 0;
		row++;
		if (input::instance().ishover(x, y, level_registry::instance().get_levelinfo(k).w, level_registry::instance().get_levelinfo(k).h)) {
			putimage(x - 10, y - 10, &level_registry::instance().get_levelinfo(k).hoverimg);
			if (input::instance().isclicked()) {
				auto gamescene = std::make_unique<adventure_game_Scene>();
				gamescene->setlevel(k);
				SceneManager::instance().changeScene(Action::push, std::move(gamescene));
			}
		}
		else {
			putimage(x, y, &level_registry::instance().get_levelinfo(k).img);
		}
	}
}

void adventure_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	//putimage(10, 25, &background2);
	returnbutton();
	draw_level();
	FlushBatchDraw();
	EndBatchDraw();
}

