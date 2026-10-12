#pragma once
#include <easyx.h>
#include<memory>
#include "scene.h"
#include "level_registry.h"
#include "plant_pool.h"
#include"Button.h"
//#include"grassland.h"
#include"battle_manager.h"
#include"sun_manager.h"
enum process {
	ready,
	fight,
	win,
	fail
};

struct product {
	product(Planttype rt) :t(rt) {
		cooldown = plant_registry::instance().get_plant_info(t).cooldown;
	}
	bool isbuy() {
		return std::chrono::duration<float>(std::chrono::steady_clock::now() - lastbuy).count() > cooldown;
	}

	void buy() {
		lastbuy = std::chrono::steady_clock::now();
	}
	Planttype t;
	std::chrono::steady_clock::time_point lastbuy = std::chrono::steady_clock::now();
	int cooldown;
};
//struct uires {
//	IMAGE background, shopimg, poolimg;
//
//};

class adventure_game_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
	void ready();
	void fight();
	void win();
	void fail();
	void poolrendering();
	void shoprendering();
	void setlevel(level l) {
		curlevel = l;
	}
private:
	grassland g;
	product* selectplant = nullptr;
	process curprocess = process::ready;
	//process curprocess = process::fail;
	const levelinfo* levelconfig = nullptr;
	plant_pool pool;
	std::vector<product>shop;
	level curlevel;
	IMAGE background, shopimg, poolimg,winimg,failimg,pauseimg;

	std::unique_ptr<Basicbutton>start, again, next, menu, returnadventure;
	battle_manager battle;
	sun_manager suns;
	std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
};