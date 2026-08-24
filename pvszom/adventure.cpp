#include "adventure.h"
#include "game.h"
#include "level.h"
#include"input.h"
#include"SceneManager.h"
#include"adventure_game.h"

void adventure_Scene::load() {
	loadimage(&background, "res\\images\\menuselect\\background.png", WIN_WIDTH, WIN_HEIGHT);
	loadimage(&background2, "res\\images\\menuselect\\background2.png", WIN_WIDTH-20, WIN_HEIGHT-50);
	loadimage(&return_button, "res\\images\\menuselect\\return_button.png", 120 , 80);
	loadimage(&return_bbutton, "res\\images\\menuselect\\return_button.png", 140, 100);

	level_list = levels();
}
void adventure_Scene::returnbutton() {
	if (input::instance().ishover(15, 25, 120, 80)) {
		putimagePNG(5, 15, &return_button);
		if (input::instance().isclicked()) {
			SceneManager::instance().changeScene(Action::pop);
		}
	}else putimagePNG(15, 25, &return_button);

}

void adventure_Scene::draw_level() {
	int y = 120,row=0;
	for(int i=0;i<level_list.size();++i) {
		int x = 50 + row * 100;
		if (i % 8 == 0&&i)y += 140,row=0;
		row++;
		if (input::instance().ishover(x, y, level_list[i].w, level_list[i].w)) {
			putimage(x-10, y-10, &level_list[i].hoverimg);
			if(input::instance().isclicked())
			SceneManager::instance().changeScene(Action::push, std::make_unique<adventure_game_Scene>());
		}
		else {
			putimage(x, y, &level_list[i].img);
		}
	}
}

void adventure_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(10, 25, &background2);
	returnbutton();
	draw_level();
	FlushBatchDraw();
	EndBatchDraw();
}

