#include"level_registry.h"
#include"plant_registry.h"
#include"levelinfo.h"
#include"UIconfig.h"

levelinfo level_1() {
	levelinfo l;
	l.id = 1;
	//l.g = std::make_unique<grassland>(5,9);
	l.pool.add_plant(Planttype::peashooter);
	l.pool.add_plant(Planttype::sunflower);
	l.pool.add_plant(Planttype::nuts);
	l.pool.add_plant(Planttype::doubleshooter);
	loadimage(&l.img, "res\\images\\menuselect\\level\\level (1).jpg", l.w, l.h);
	loadimage(&l.hoverimg, "res\\images\\menuselect\\level\\level (1).jpg", l.ww, l.hh);
	return l;
}

levelinfo level_2() {
	levelinfo l;
	l.id = 2;
	l.pool.add_plant(Planttype::peashooter);
	l.pool.add_plant(Planttype::sunflower);
	l.pool.add_plant(Planttype::iceshooter);
	l.pool.add_plant(Planttype::doubleshooter);
	l.pool.add_plant(Planttype::potato);
	l.pool.add_plant(Planttype::machinegun);
	l.pool.add_plant(Planttype::nuts);
	l.pool.add_plant(Planttype::treestump);

	loadimage(&l.img, "res\\images\\menuselect\\level\\level (2).jpg", l.w, l.h);
	loadimage(&l.hoverimg, "res\\images\\menuselect\\level\\level (2).jpg", l.ww, l.hh);
	return l;
}

void level_registry::load() {
	level_registry::instance().putconfig(level::level_1, level_1());
	level_registry::instance().putconfig(level::level_2, level_2());
}

//void plant_registry::load() {
//	int w=63*0.9, h=88*0.9;
//	plant_registry::putconfig(Planttype::peashooter, plantinfo(100, 100, 5, "Peashooter", "res\\images\\cards\\peashooter.png", "res\\images\\plants\\peashooter", w, h,true,20));
//	plant_registry::putconfig(Planttype::sunflower, plantinfo(100, 50, 0, "Sunflower", "res\\images\\cards\\sunflower.png", "res\\images\\plants\\sunflower", w, h));
//	plant_registry::putconfig(Planttype::potato, plantinfo(100, 150, 5, "potato", "res\\images\\cards\\potato.png", "res\\images\\plants\\potato\\", w, h));
//	plant_registry::putconfig(Planttype::doubleshooter, plantinfo(100, 200, 5, "Doubleshooter", "res\\images\\cards\\doubleshooter.png", "res\\images\\plants\\doubleshooter", w, h,true,20));
//	plant_registry::putconfig(Planttype::iceshooter, plantinfo(100, 150, 5, "Iceshooter", "res\\images\\cards\\iceshooter.png", "res\\images\\plants\\iceshooter", w, h,true,15));
//	plant_registry::putconfig(Planttype::treestump, plantinfo(100, 175, 5, "Treestump", "res\\images\\cards\\treestump.png", "res\\images\\plants\\treestump", w, h));
//	plant_registry::putconfig(Planttype::machinegun, plantinfo(100, 150, 5, "Machinegun", "res\\images\\cards\\machinegun.png", "res\\images\\plants\\machinegun", w, h,true,25));
//	plant_registry::putconfig(Planttype::nuts, plantinfo(100, 100, 5, "Nuts", "res\\images\\cards\\nuts.png", "res\\images\\plants\\nuts", w, h));
//
//}

void plant_registry::load() {
	int w = 63 * 0.9, h = 88 * 0.9;
	plant_registry::putconfig(Planttype::peashooter, plantinfo(100, 100, 10, "Peashooter",
		"res\\images\\cards\\peashooter.png", "res\\images\\plants\\peashooter", w, h,
		true, 20, "res\\images\\plants\\bullet\\pea.png"));

	plant_registry::putconfig(Planttype::iceshooter, plantinfo(100, 150, 10, "Iceshooter",
		"res\\images\\cards\\iceshooter.png", "res\\images\\plants\\iceshooter", w, h,
		true, 15, "res\\images\\plants\\bullet\\ice.png"));

	plant_registry::putconfig(Planttype::doubleshooter, plantinfo(100, 200, 15, "Doubleshooter",
		"res\\images\\cards\\doubleshooter.png", "res\\images\\plants\\doubleshooter", w, h,
		true, 20, "res\\images\\plants\\bullet\\pea.png"));

	plant_registry::putconfig(Planttype::machinegun, plantinfo(100, 150, 25, "Machinegun",
		"res\\images\\cards\\machinegun.png", "res\\images\\plants\\machinegun", w, h,
		true, 25, "res\\images\\plants\\bullet\\firepea"));

	plant_registry::putconfig(Planttype::nuts, plantinfo(500, 50, 15, "Nuts", "res\\images\\cards\\nuts.png", "res\\images\\plants\\nuts", w, h));
	plant_registry::putconfig(Planttype::treestump, plantinfo(100, 175, 15, "Treestump", "res\\images\\cards\\treestump.png", "res\\images\\plants\\treestump", w, h));
	plant_registry::putconfig(Planttype::sunflower, plantinfo(100, 50, 5, "Sunflower", "res\\images\\cards\\sunflower.png", "res\\images\\plants\\sunflower", w, h));
	plant_registry::putconfig(Planttype::potato, plantinfo(100, 150, 15, "potato", "res\\images\\cards\\potato.png", "res\\images\\plants\\potato\\", w, h));
}
void UIconfig::load() {
	loadimage(&black, "res//images//UIconfig//black.png");
}