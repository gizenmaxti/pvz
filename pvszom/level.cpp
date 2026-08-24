#include"level.h"

level level_1() {
	level l;
	l.id = 1;
	l.pool.add_plant(plant_card(Planttype::peashooter));
	l.pool.add_plant(plant_card(Planttype::sunflower));
	loadimage(&l.img, "res\\images\\menuselect\\level\\level (1).jpg", l.w, l.h);
	loadimage(&l.hoverimg, "res\\images\\menuselect\\level\\level (1).jpg", l.hw, l.hh);
	//l.nextscene = nullptr;
	return l;
}

level level_2() {
	level l;
	l.id = 2;
	l.pool.add_plant(plant_card(Planttype::peashooter));
	l.pool.add_plant(plant_card(Planttype::sunflower));
	l.pool.add_plant(plant_card(Planttype::cherry));
	loadimage(&l.img, "res\\images\\menuselect\\level\\level (2).jpg", l.w, l.h);
	loadimage(&l.hoverimg, "res\\images\\menuselect\\level\\level (2).jpg", l.hw, l.hh);
	//l.nextscene = nullptr;
	return l;
}

std::vector<level>levels() {
	std::vector<level>lvls;
	lvls.push_back(std::move(level_1()));
	lvls.push_back(std::move(level_2()));
	return lvls;
}