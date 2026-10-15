#pragma once
#include <easyx.h>
#include<memory>
#include<algorithm>
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
		lastbuy = std::chrono::steady_clock::now() - std::chrono::seconds(cooldown + 1);
	}

	// 冷却是否已经结束
	bool isbuy() const {
		return std::chrono::duration<float>(std::chrono::steady_clock::now() - lastbuy).count() > cooldown;
	}

	// 剩余冷却比例：1 = 刚买完（全遮罩），0 = 冷却完成（无遮罩）
	float cooldownRatio() const {
		if (cooldown <= 0) return 0.0f;
		const float elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - lastbuy).count();
		const float remain = 1.0f - elapsed / static_cast<float>(cooldown);
		return remain < 0.0f ? 0.0f : (remain > 1.0f ? 1.0f : remain);
	}

	void buy() {
		lastbuy = std::chrono::steady_clock::now();
	}
	Planttype t;
	std::chrono::steady_clock::time_point lastbuy;
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
	void win();
	void fail();
	void poolrendering();
	void shoprendering();
	void setlevel(level l) {
		curlevel = l;
	}
private:
	// 在卡槽中查找尚未冷却的指定植物；找不到返回 nullptr，天然规避悬空指针
	product* findAvailableProduct(Planttype t) {
		for (auto& p : shop) {
			if (p.t == t && p.isbuy()) return &p;
		}
		return nullptr;
	}

	grassland g;
	// 用 Planttype 值记录当前选中的卡，而不是指向 shop 元素的裸指针：
	Planttype selectplant = Planttype::sunflower;
	bool hasSelection = false;
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