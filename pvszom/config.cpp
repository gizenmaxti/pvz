#include"level_registry.h"
#include"plant_registry.h"
#include"levelinfo.h"
#include"plantinfo.h"

levelinfo level_1() {
	levelinfo l;
	l.id = 1;
	l.pool.add_plant(plant_card(Planttype::peashooter));
	l.pool.add_plant(plant_card(Planttype::sunflower));
	loadimage(&l.img, "res\\images\\menuselect\\level\\level (1).jpg", l.w, l.h);
	loadimage(&l.hoverimg, "res\\images\\menuselect\\level\\level (1).jpg", l.ww, l.hh);
	return l;
}

levelinfo level_2() {
	levelinfo l;
	l.id = 2;
	l.pool.add_plant(plant_card(Planttype::peashooter));
	l.pool.add_plant(plant_card(Planttype::sunflower));
	l.pool.add_plant(plant_card(Planttype::cherry));
	loadimage(&l.img, "res\\images\\menuselect\\level\\level (2).jpg", l.w, l.h);
	loadimage(&l.hoverimg, "res\\images\\menuselect\\level\\level (2).jpg", l.ww, l.hh);
	return l;
}

void level_registry::load() {
	level_registry::instance().putconfig(level::level_1, level_1());
	level_registry::instance().putconfig(level::level_2, level_2());
}

void plant_registry::load() {
	int w=63, h=88;
	plant_registry::putconfig(Planttype::peashooter, plantinfo(100, 100, 5, "Peashooter", "res\\images\\cards\\peashooter.png", "res\\images\\plants\\peashooter\\0.png", w, h));
	plant_registry::putconfig(Planttype::sunflower, plantinfo(100, 50, 5, "Sunflower", "res\\images\\cards\\sunflower.png", "res\\images\\plants\\sunflower\\0.png", w, h));
	plant_registry::putconfig(Planttype::cherry, plantinfo(100, 150, 5, "Cherry", "res\\images\\cards\\cherry.png", "res\\images\\plants\\cherry\\0.png", w, h));
	plant_registry::putconfig(Planttype::doubleshooter, plantinfo(100, 200, 5, "Doubleshooter", "res\\images\\cards\\doubleshooter.png", "res\\images\\plants\\doubleshooter\\0.png", w, h));
	plant_registry::putconfig(Planttype::iceshooter, plantinfo(100, 150, 5, "Iceshooter", "res\\images\\cards\\iceshooter.png", "res\\images\\plants\\iceshooter\\0.png", w, h));
	plant_registry::putconfig(Planttype::treestump, plantinfo(100, 175, 5, "Treestump", "res\\images\\cards\\treestump.png", "res\\images\\plants\\treestump\\0.png", w, h));
	plant_registry::putconfig(Planttype::machinegun, plantinfo(100, 150, 5, "Machinegun", "res\\images\\cards\\machinegun.png", "res\\images\\plants\\machinegun\\0.png", w,h));
	plant_registry::putconfig(Planttype::nuts, plantinfo(100, 100, 5, "Nuts", "res\\images\\cards\\nuts.png", "res\\images\\plants\\nuts\\0.png", w, h));
}