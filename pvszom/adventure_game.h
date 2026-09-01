#pragma once
#include <easyx.h>
#include<memory>
#include "scene.h"
#include "level_registry.h"
#include "plant_pool.h"
#include"Button.h"
#include"grassland.h"
#include"battle_manager.h"
#include"sun_manager.h"
enum process {
	ready,
	fight,
	win,
	fail
};


struct product {
	product(Planttype rt):t(rt) {
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

class adventure_game_Scene : public scene {
public:
	void load() override;
	void update() override;
	void unload() override {
	}
	void ready();
	void fight();
	void poolrendering();
	void shoprendering();
	void setlevel(level l) {
		curlevel = l;
	}
private:
	grassland g;
	product* selectplant=nullptr;
	process curprocess=process::ready;
	levelinfo levelconfig;
	plant_pool pool;
	std::vector<product>shop;
	level curlevel;
	IMAGE background,shopimg,poolimg;
	std::unique_ptr<Basicbutton>start;
	battle_manager battle;
	sun_manager suns;
	std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
};