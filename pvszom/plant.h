#pragma once
#include"plant_registry.h"

class plant {
public:
	plant(Planttype rt) :t(rt), hp(plant_registry::instance().get_plant_info(t).inithp), value(plant_registry::instance().get_plant_info(t).value) {
	}
	Planttype gettype() {
		return t;
	}
	int gethp() {
		return hp;
	}
	int getvalue() {
		return value;
	}
	const IMAGE& getBulletImg(int frame = 0) {
		auto& imgs = plant_registry::instance().get_plant_info(t).bulletimgs;
		return imgs[frame % imgs.size()];
	}
	const IMAGE& dance() {
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		if (std::chrono::duration <float>(now - lastframe).count() > 0.1f) {
			curframe = (curframe + 1) % plant_registry::instance().get_plant_info(t).patimgs.size();
			lastframe = now;
		}
		return plant_registry::instance().get_plant_info(t).patimgs[curframe];
	}
	bool canAttack() {
		return plant_registry::instance().get_plant_info(t).canshoot;
	}
	int getDamage() {
		return plant_registry::instance().get_plant_info(t).damage;
	}
	void takeDamage(int dmg) { hp -= dmg; }

private:
	int curframe = 0;
	std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
	Planttype t;
	int hp, value;
};