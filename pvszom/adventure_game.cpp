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

	battle.init(&g, 10);
	suns.init();
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
	for (auto& i : shop) {
		col++;
		x = 30 + (col * (plant_registry::instance().get_plant_info(i.t).w + 7));
		putimage(x, y, &plant_registry::instance().get_plant_info(i.t).cardimg);
		if (!i.isbuy())putimagePNG(x, y, plant_registry::instance().get_plant_info(i.t).w, plant_registry::instance().get_plant_info(i.t).h, &UIconfig::instance().getblack(), 180);
		if (input::instance().isdragging() && input::instance().ishover(x, y, plant_registry::instance().get_plant_info(i.t).w, plant_registry::instance().get_plant_info(i.t).h) && !selectplant && i.isbuy()) {
			//selectplant = i.t;
			selectplant = &i;
		}
	}
	if (selectplant && input::instance().isleftdown()) {
		int offsetx = input::instance().getx() - 170, offsety = input::instance().gety() - 70, w = 80, h = 100;
		//根据鼠标的x,y调整硬编码数值进行种植植物位置的偏移调整，w为列距，h为行距。
		if (g.planting(offsety / h, offsetx / w, selectplant->t)) {
			selectplant->buy();
			//printf("%d  %d\n", (input::instance().gety() - 100 ), (input::instance().getx() - 160));
			//终端打印测试代码
		}
	}
	if (selectplant && input::instance().isdragging()) {
		putimagePNG(input::instance().getx() - 30, input::instance().gety() - 30, &plant_registry::instance().get_plant_info(selectplant->t).patimgs[0]);
	}
	else {
		selectplant = nullptr;
	}
}


void adventure_game_Scene::fight() {
	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, "黑体");
	std::string sunText = "阳光: " + std::to_string(suns.getSunCount());
	outtextxy(50, 40, sunText.c_str());
	auto now = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
	lastFrameTime = now;
	if (deltaTime > 0.1f) deltaTime = 0.1f; // clamp,避免调试断点导致的异常大跳变
	g.update();
	battle.update(deltaTime);
	suns.update(deltaTime);
	shoprendering();

	if (battle.getResult() == BattleResult::win) {
		curprocess = process::win;
	}
	else if (battle.getResult() == BattleResult::lose) {
		curprocess = process::fail;
	}
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
		settextcolor(RGB(255, 255, 0));
		settextstyle(40, 0, "黑体");
		outtextxy(350, 250, "胜利!");
		break;
	case process::fail:
		settextcolor(RGB(255, 0, 0));
		settextstyle(40, 0, "黑体");
		outtextxy(350, 250, "失败!");
		break;
	}
	FlushBatchDraw();
	EndBatchDraw();
}