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
	// 统一在加载处显式取整：EasyX 的 loadimage 需要 int，直接从 double 隐式转换会触发 C4244
	auto px = [](double v) { return static_cast<int>(v); };

	loadimage(&background, "res\\images\\adventure_game\\bg_3.png");
	loadimage(&shopimg, "res\\images\\adventure_game\\wd.jpg", px(650 * 0.9), px(100 * 0.9));
	loadimage(&poolimg, "res\\images\\adventure_game\\poolimg.jpg", px(600 * 0.8), px(650 * 0.8));
	loadimage(&winimg, "res\\images\\adventure_game\\win.jpg", px(1279 * 0.4), px(1727 * 0.4));
	loadimage(&failimg, "res\\images\\adventure_game\\fail.jpg", px(1279 * 0.4), px(1727 * 0.4));
	loadimage(&pauseimg, "res\\images\\adventure_game\\pause.jpg");

	returnadventure = std::make_unique<Basicbutton>(0, 0, px(620 * 0.58), px(182 * 0.58), "res\\images\\adventure_game\\returnadventure.png");
	next = std::make_unique<Basicbutton>(0, 0, px(626 * 0.58), px(183 * 0.58), "res\\images\\adventure_game\\next.png");
	again= std::make_unique<Basicbutton>(0, 0, px(584 * 0.58), px(164 * 0.58), "res\\images\\adventure_game\\again.png");
	menu = std::make_unique<Basicbutton>(0, 0, px(592 * 0.58), px(184 * 0.58), "res\\images\\adventure_game\\menu.png");
	start = std::make_unique<Basicbutton>(0, 0, px(362 * 0.5), px(80 * 0.5), "res\\images\\adventure_game\\game_start.png");
	
	levelconfig = &level_registry::instance().get_levelinfo(curlevel);
	pool = levelconfig->pool;

	battle.init(&g, levelconfig->totalzonbie);
	suns.init();
	// 向日葵产出的阳光交给 sun_manager 统一管理
	battle.setSunSpawner([this]() { suns.spawnDrop(); });
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

	int y = 5, col = 0;

	for (size_t i = 0; i < shop.size(); ++i) {
		col++;
		const auto& t = shop[i].t;
		const auto& info = plant_registry::instance().get_plant_info(t);
		int w = info.w, h = info.h;
		// 位置必须与 shoprendering() 的绘制位置完全一致，否则点击判定与画面错位
		int x = 30 + (col * (w + 7));
		putimage(x, y, &info.cardimg);
	}

	// 收集要移除的植物类型，循环外统一处理：避免在遍历 shop 时 erase 导致悬空
	std::vector<Planttype> toRemove;
	for (size_t i = 0; i < shop.size(); ++i) {
		col = static_cast<int>(i) + 1;
		const auto& t = shop[i].t;
		const auto& info = plant_registry::instance().get_plant_info(t);
		int w = info.w, h = info.h;
		int x = 30 + (col * (w + 7));
		if (input::instance().ishover(x, y, w, h) && input::instance().isclicked()) {
			// ready 阶段只是选卡，未扣费，所以取消选择不需要退款；把卡放回植物池即可
			toRemove.push_back(t);
		}
	}

	for (auto t : toRemove) {
		// C++17 下没有 std::erase_if（那是 C++20），用 erase-remove 惯用法
		shop.erase(std::remove_if(shop.begin(), shop.end(),
			[t](const product& p) { return p.t == t; }), shop.end());
		for (auto& i : pool.getplanttype()) {
			if (i.t == t) i.optional = true;
		}
	}
	if (!toRemove.empty()) {
		// shop 已被改动，之前选中的卡可能已不存在，必须清空选择
		hasSelection = false;
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
	int y = 5, col = 0;
	for (auto& i : shop) {
		col++;
		const auto& info = plant_registry::instance().get_plant_info(i.t);
		int x = 30 + (col * (info.w + 7));
		putimage(x, y, &info.cardimg);
		bool affordable = suns.getSunCount() >= info.value;
		if (!i.isbuy() || !affordable) {
			putimagePNG(x, y, info.w, info.h, &UIconfig::instance().getblack(), 180);
		}
		if (input::instance().isdragging() && input::instance().ishover(x, y, info.w, info.h)
			&& !hasSelection && i.isbuy() && affordable) {
			selectplant = i.t;
			hasSelection = true;
		}
	}

	if (hasSelection) {
		// 每帧按值重新查找，而不是持有裸指针：shop 若在本帧被改动也不会悬空
		product* sel = findAvailableProduct(selectplant);
		if (!sel) {
			hasSelection = false;   // 卡已被移除或正在冷却
		}
		else if (input::instance().isleftdown()) {
			const int offsetx = input::instance().getx() - 170;
			const int offsety = input::instance().gety() - 70;
			const int w = 80, h = 100;   // 列距、行距
			const auto& info = plant_registry::instance().get_plant_info(selectplant);
			if (g.planting(offsety / h, offsetx / w, selectplant, suns.getSunCount())) {
				suns.trySpend(info.value);   // 校验已通过，此处必然成功
				sel->buy();
				hasSelection = false;
			}
		}
	}

	if (hasSelection && input::instance().isdragging()) {
		putimagePNG(input::instance().getx() - 30, input::instance().gety() - 30,
			&plant_registry::instance().get_plant_info(selectplant).patimgs[0]);
	}
	// 注意：松手那一帧 isdragging() 已为 false、isleftdown() 为 true，
	// 所以这里不能因为 !isdragging() 就清空选择，否则永远种不下去。
	// 选择会在成功种植、卡被移除、或 start 进入战斗时清理。
}


void adventure_game_Scene::fight() {
	
	auto now = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
	lastFrameTime = now;
	if (deltaTime > 0.1f) deltaTime = 0.1f; // clamp,避免调试断点导致的异常大跳变
	g.update(deltaTime);        // 只推进植物动画与死亡清理
	battle.update(deltaTime);   // 内部负责植物行为、绘制、子弹与僵尸
	suns.update(deltaTime);     // 阳光最后画，保证在最上层
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