#include "adventure.h"
#include "level_registry.h"
#include"levelinfo.h"
#include"input.h"
#include"SceneManager.h"
#include"adventure_game.h"

void adventure_Scene::load() {
	loadimage(&background, "res\\images\\menuselect\\background.jpg", WIN_WIDTH, WIN_HEIGHT);
	loadimage(&background2, "res\\images\\menuselect\\background2.png", WIN_WIDTH - 20, WIN_HEIGHT - 50);
	// 显式取整，避免 double→int 隐式截断（C4244）
	const int rw = static_cast<int>(288 * 0.5), rh = static_cast<int>(64 * 0.5);
	const int bw = static_cast<int>(288 * 0.6), bh = static_cast<int>(64 * 0.6);
	loadimage(&return_button, "res\\images\\menuselect\\return_button.jpg", rw, rh);
	loadimage(&return_bbutton, "res\\images\\menuselect\\return_button.jpg", bw, bh);

}
void adventure_Scene::returnbutton() {
	int x = 15, y = 570;
	if (input::instance().ishover(x, y, static_cast<int>(288 * 0.5), static_cast<int>(64 * 0.5))) {
		putimagePNG(x - 10, y - 10, &return_bbutton);
		if (input::instance().isclicked()) {
			SceneManager::instance().changeScene(Action::pop);
		}
	}
	else putimagePNG(x, y, &return_button);
}

void adventure_Scene::draw_level() {
	// 原实现把 int i = 0; 放在循环体内，i % 8 == 0 && i 恒为假，
	// 换行逻辑永不触发，所有关卡都会叠在同一行。改用真实下标驱动换行。
	const int perRow = 4;      // 每行显示 4 个关卡
	const int stepX = 170, stepY = 140;
	int y = 120;
	int index = 0;
	for (auto k : level_registry::instance().getlevels()) {
		const int col = index % perRow;
		const int rowi = index / perRow;
		const int x = 45 + col * stepX;
		const int yy = y + rowi * stepY;
		const auto& info = level_registry::instance().get_levelinfo(k);
		if (input::instance().ishover(x, yy, info.w, info.h)) {
			putimage(x - 10, yy - 10, &info.hoverimg);
			if (input::instance().isclicked()) {
				auto gamescene = std::make_unique<adventure_game_Scene>();
				gamescene->setlevel(k);
				SceneManager::instance().changeScene(Action::push, std::move(gamescene));
			}
		}
		else {
			putimage(x, yy, &info.img);
		}
		++index;
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

