#include"level_registry.h"
#include"plant_registry.h"
#include"plants.h"
#include"levelinfo.h"
#include"UIconfig.h"

levelinfo level_1() {
	levelinfo l;
	l.id = 1;
	l.pool.add_plant(Planttype::peashooter);
	l.pool.add_plant(Planttype::sunflower);
	l.pool.add_plant(Planttype::nuts);
	l.pool.add_plant(Planttype::doubleshooter);
	l.totalzonbie = 1;
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
	l.totalzonbie = 10;
	loadimage(&l.img, "res\\images\\menuselect\\level\\level (2).jpg", l.w, l.h);
	loadimage(&l.hoverimg, "res\\images\\menuselect\\level\\level (2).jpg", l.ww, l.hh);
	return l;
}

void level_registry::load() {
	level_registry::instance().putconfig(level::level_1, level_1());
	level_registry::instance().putconfig(level::level_2, level_2());
}


void plant_registry::load() {
	int w = static_cast<int>(63 * 0.9), h = static_cast<int>(88 * 0.9);
	plant_registry::putconfig(Planttype::peashooter, plantinfo(100, 100, 10, "Peashooter",
		"res\\images\\cards\\peashooter.png", "res\\images\\plants\\peashooter", w, h,
		true, 20, "res\\images\\plants\\bullet\\pea.png", 1.5f));

	plant_registry::putconfig(Planttype::iceshooter, plantinfo(100, 150, 10, "Iceshooter",
		"res\\images\\cards\\iceshooter.png", "res\\images\\plants\\iceshooter", w, h,
		true, 15, "res\\images\\plants\\bullet\\ice.png", 1.5f));

	plant_registry::putconfig(Planttype::doubleshooter, plantinfo(100, 200, 15, "Doubleshooter",
		"res\\images\\cards\\doubleshooter.png", "res\\images\\plants\\doubleshooter", w, h,
		true, 20, "res\\images\\plants\\bullet\\pea.png", 1.5f));

	plant_registry::putconfig(Planttype::machinegun, plantinfo(100, 150, 25, "Machinegun",
		"res\\images\\cards\\machinegun.png", "res\\images\\plants\\machinegun", w, h,
		true, 25, "res\\images\\plants\\bullet\\pea.png", 0.35f));

	plant_registry::putconfig(Planttype::nuts, plantinfo(500, 50, 15, "Nuts", "res\\images\\cards\\nuts.png", "res\\images\\plants\\nuts", w, h));
	plant_registry::putconfig(Planttype::treestump, plantinfo(100, 175, 15, "Treestump", "res\\images\\cards\\treestump.png", "res\\images\\plants\\treestump", w, h));
	plant_registry::putconfig(Planttype::sunflower, plantinfo(100, 50, 5, "Sunflower", "res\\images\\cards\\sunflower.png", "res\\images\\plants\\sunflower", w, h));
	plant_registry::putconfig(Planttype::potato, plantinfo(100, 150, 15, "potato", "res\\images\\cards\\potato.png", "res\\images\\plants\\potato\\", w, h));

	// 注册每种植物对应的子类构造函数。新增植物只要在这里加一行 + 加配置即可，
	// 不需要修改 grassland 或 battle_manager 的任何逻辑。
	// 工厂里统一调用 init()，把注册表中的数值灌进对象（构造时注册表可能还没加载）。
	auto reg = [](Planttype t, std::function<std::unique_ptr<plant>()> make) {
		plant_registry::setCreator(t, [t, make]() {
			auto p = make();
			if (p) p->init();
			return p;
		});
		(void)t;
	};
	reg(Planttype::peashooter,    []() { return std::make_unique<PeashooterPlant>(Planttype::peashooter); });
	reg(Planttype::iceshooter,    []() { return std::make_unique<IceShooterPlant>(Planttype::iceshooter); });
	reg(Planttype::doubleshooter, []() { return std::make_unique<DoubleShooterPlant>(Planttype::doubleshooter); });
	reg(Planttype::machinegun,    []() { return std::make_unique<MachineGunPlant>(Planttype::machinegun); });
	reg(Planttype::sunflower,     []() { return std::make_unique<SunflowerPlant>(Planttype::sunflower); });
	reg(Planttype::nuts,          []() { return std::make_unique<NutsPlant>(Planttype::nuts); });
	reg(Planttype::treestump,     []() { return std::make_unique<TreeStumpPlant>(Planttype::treestump); });
	reg(Planttype::potato,        []() { return std::make_unique<PotatoPlant>(Planttype::potato); });
}

std::unique_ptr<plant> plant_registry::create(Planttype t) {
	auto it = creators().find(t);
	if (it == creators().end()) return nullptr;
	return it->second();
}
void UIconfig::load() {
	loadimage(&black, "res//images//UIconfig//black.png");
}