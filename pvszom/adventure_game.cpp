#include <easyx.h>
#include "adventure_game.h"
#include"plant_pool.h"
#include "plant_registry.h"
#include"input.h"
#include"UIconfig.h"
#include"tool.h"
#include"grassland.h"
#include"SceneManager.h"
#include"Button.h"

void adventure_game_Scene::load() {
	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shopimg, "res\\images\\adventure_game\\wd.jpg", 650 * 0.9, 100 * 0.9);
	loadimage(&poolimg, "res\\images\\adventure_game\\poolimg.jpg", 600 * 0.8, 650 * 0.8);
	loadimage(&winimg, "res\\images\\adventure_game\\win.jpg",1279*0.4,1727*0.4);
	loadimage(&failimg, "res\\images\\adventure_game\\fail.jpg", 1279 * 0.4, 1727 * 0.4);
	loadimage(&pauseimg, "res\\images\\adventure_game\\pause.jpg");

	returnadventure = std::make_unique<Basicbutton>(0, 0, 620*0.58, 182*0.58, "res\\images\\adventure_game\\returnadventure.png");
	next = std::make_unique<Basicbutton>(0, 0, 626*0.58, 183*0.58, "res\\images\\adventure_game\\next.png");
	again= std::make_unique<Basicbutton>(0, 0, 584*0.58,164*0.58, "res\\images\\adventure_game\\again.png");
	menu = std::make_unique<Basicbutton>(0, 0, 592*0.58, 184*0.58, "res\\images\\adventure_game\\menu.png");
	start = std::make_unique<Basicbutton>(0, 0, 362 * 0.5, 80 * 0.5, "res\\images\\adventure_game\\game_start.png");
	
	levelconfig = &level_registry::instance().get_levelinfo(curlevel);
	pool = levelconfig->pool;

	battle.init(&g, levelconfig->totalzonbie);
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


void drawSunCount(int sunCount, int x, int y) {
	setbkmode(TRANSPARENT);               
	settextcolor(RGB(0, 0, 0));     
	settextstyle(15, 0, "黑体");           

	std::string sunText = "阳光: " + std::to_string(sunCount);
	outtextxy(x, y, sunText.c_str());
}

void adventure_game_Scene::shoprendering() {
	putimage(10, 0, &shopimg);
	int x, y = 5, col = 0;
	for (auto& i : shop) {
		col++;
		x = 30 + (col * (plant_registry::instance().get_plant_info(i.t).w + 7));
		putimage(x, y, &plant_registry::instance().get_plant_info(i.t).cardimg);
		if (!i.isbuy() || !(suns.getSunCount() >= plant_registry::instance().get_plant_info(i.t).value))putimagePNG(x, y, plant_registry::instance().get_plant_info(i.t).w, plant_registry::instance().get_plant_info(i.t).h, &UIconfig::instance().getblack(), 180);
		if (input::instance().isdragging() && input::instance().ishover(x, y, plant_registry::instance().get_plant_info(i.t).w, plant_registry::instance().get_plant_info(i.t).h) && !selectplant && i.isbuy()&& suns.getSunCount() >= plant_registry::instance().get_plant_info(i.t).value) {
			//selectplant = i.t;
			selectplant = &i;
		}
	}
	if (selectplant && input::instance().isleftdown()) {
		int offsetx = input::instance().getx() - 170, offsety = input::instance().gety() - 70, w = 80, h = 100;
		//根据鼠标的x,y调整硬编码数值进行种植植物位置的偏移调整，w为列距，h为行距。
		if (g.planting(offsety / h, offsetx / w, selectplant->t, suns.getSunCount())) {
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
	
	auto now = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
	lastFrameTime = now;
	if (deltaTime > 0.1f) deltaTime = 0.1f; // clamp,避免调试断点导致的异常大跳变
	g.update();
	battle.update(deltaTime);
	suns.update(deltaTime);
	shoprendering();
	drawSunCount(suns.getSunCount(), 10, 70);
	if (battle.getResult() == BattleResult::win) {
		curprocess = process::win;
	}
	else if (battle.getResult() == BattleResult::lose) {
		curprocess = process::fail;
	}
}
void adventure_game_Scene::win() {
	int tempx = input::instance().getx(),tempy= input::instance().gety();
	bool tempclick = input::instance().isclicked();
	putimage(300,0,&winimg);
	//SceneManager::instance().changeScene(Action::pop);
	if (tempx >= 380 && tempx <= 380 + menu->getw() && tempy >= 240 && tempy <= 240 + menu->geth()) {
		putimage(380, 240, &menu->getimg());
		if (tempclick) {
			SceneManager::instance().changeScene(Action::pop);
			SceneManager::instance().changeScene(Action::pop);
		}
	}else
	if (tempx >= 380 && tempx <= 380 + returnadventure->getw() && tempy >= 500 && tempy <= 500 + returnadventure->geth()) {
		putimage(380, 500, &returnadventure->getimg());
		if (tempclick) {
			SceneManager::instance().changeScene(Action::pop);
		}
	}else
	if (tempx >= 380 && tempx <= 380 + next->getw() && tempy >= 380 && tempy <= 380 + next->geth()) {
		putimage(380, 380, &next->getimg());
		if (tempclick) {
			auto gamescene = std::make_unique<adventure_game_Scene>();
			int ne = static_cast<int>(curlevel) + 1;
			level k = static_cast<level>(ne) == level::count ? level::level_1 : static_cast<level>(ne);
			gamescene->setlevel(k);
			SceneManager::instance().changeScene(Action::pop);
			SceneManager::instance().changeScene(Action::push, std::move(gamescene));
			tempclick = false;
		}
	}
}
void adventure_game_Scene::fail() {
	int tempx = input::instance().getx(), tempy = input::instance().gety();
	bool tempclick = input::instance().isclicked();
	
	putimage(300, 0, &failimg);
	if (tempx >= 390 && tempx <= 390 + menu->getw() && tempy >= 220 && tempy <= 220 + menu->geth()) {
		putimage(390, 220, &menu->getimg());
		if (tempclick) {
			SceneManager::instance().changeScene(Action::pop);
			SceneManager::instance().changeScene(Action::pop);
		}
	}
	else
		if (tempx >= 390 && tempx <= 390 + returnadventure->getw() && tempy >= 480 && tempy <= 480 + returnadventure->geth()) {
			putimage(390, 480, &returnadventure->getimg());
			if (tempclick) {
				SceneManager::instance().changeScene(Action::pop);
			}
		}
		else
			if (tempx >= 390 && tempx <= 390 + next->getw() && tempy >= 360 && tempy <= 360 + next->geth()) {
				putimage(390, 360, &again->getimg());
				if (tempclick) {
					auto gamescene = std::make_unique<adventure_game_Scene>();
					gamescene->setlevel(curlevel);
					SceneManager::instance().changeScene(Action::pop);
					SceneManager::instance().changeScene(Action::push, std::move(gamescene));
					tempclick = false;
				}
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
		win();
		break;
	case process::fail:
		fail();
		break;
	}
	FlushBatchDraw();
	EndBatchDraw();
}