#include"plant_registry.h"
#include"tool.h"
#include"shop.h"
void plant_registry::load() {

	//plant_infos.emplace(Planttype::sunflower, plantinfo(100, 50, 5, "Sunflower", "res\\images\\plants\\sunflower_card.png", "res\\images\\cards\\sunflower.png", 63, 88));
	//register_plant(Planttype::peashooter, plantinfo(100, 100, 5, "Peashooter", "res\\images\\cards\\peashooter.png", "res\\images\\plants\\peashooter\\0.png", 63, 88));
	//register_plant(Planttype::sunflower, plantinfo(100, 50, 5, "Sunflower", "res\\images\\cards\\sunflower.png", "res\\images\\plants\\sunflower\\0.png",  63, 88));
	////register_plant(Planttype::cherry, plantinfo(100, 150, 5, "Cherry", "res\\images\\cards\\cherry.png", "res\\images\\plants\\cherry\\0.png", 63, 88));
	//register_plant(Planttype::doubleshooter, plantinfo(100, 200, 5, "Doubleshooter", "res\\images\\cards\\doubleshooter.png", "res\\images\\plants\\doubleshooter\\0.png", 63, 88));
	//register_plant(Planttype::iceshooter, plantinfo(100, 150, 5, "Iceshooter", "res\\images\\cards\\iceshooter.png", "res\\images\\plants\\iceshooter\\0.png", 63, 88));
	//register_plant(Planttype::treestump, plantinfo(100, 175, 5, "Treestump", "res\\images\\cards\\treestump.png", "res\\images\\plants\\treestump\\0.png", 63, 88));
	//register_plant(Planttype::machinegun, plantinfo(100, 150, 5, "Machinegun", "res\\images\\cards\\machinegun.png", "res\\images\\plants\\machinegun\\0.png", 63, 88));	
	//register_plant(Planttype::nuts, plantinfo(100, 100, 5, "Nuts", "res\\images\\cards\\nuts.png", "res\\images\\plants\\nuts\\0.png", 63, 88));
	plant_infos.emplace(Planttype::peashooter, plantinfo(100, 100, 5, "Peashooter", "res\\images\\cards\\peashooter.png", "res\\images\\plants\\peashooter\\0.png", 63, 88));
	plant_infos.emplace(Planttype::sunflower, plantinfo(100, 50, 5, "Sunflower", "res\\images\\cards\\sunflower.png", "res\\images\\plants\\sunflower\\0.png", 63, 88));
	plant_infos.emplace(Planttype::cherry, plantinfo(100, 150, 5, "Cherry", "res\\images\\cards\\cherry.png", "res\\images\\plants\\cherry\\0.png", 63, 88));
	plant_infos.emplace(Planttype::doubleshooter, plantinfo(100, 200, 5, "Doubleshooter", "res\\images\\cards\\doubleshooter.png", "res\\images\\plants\\doubleshooter\\0.png", 63, 88));
	plant_infos.emplace(Planttype::iceshooter, plantinfo(100, 150, 5, "Iceshooter", "res\\images\\cards\\iceshooter.png", "res\\images\\plants\\iceshooter\\0.png", 63, 88));
	plant_infos.emplace(Planttype::treestump, plantinfo(100, 175, 5, "Treestump", "res\\images\\cards\\treestump.png", "res\\images\\plants\\treestump\\0.png", 63, 88));
	plant_infos.emplace(Planttype::machinegun, plantinfo(100, 150, 5, "Machinegun", "res\\images\\cards\\machinegun.png", "res\\images\\plants\\machinegun\\0.png", 63, 88));
	plant_infos.emplace(Planttype::nuts, plantinfo(100, 100, 5, "Nuts", "res\\images\\cards\\nuts.png", "res\\images\\plants\\nuts\\0.png", 63, 88));
}
//void plant_registry::update() {
//	int x = 20, y = 100;
//	int i = 0;
//	for (const auto& type : plant_types) {
//		if (x <= msgx && msgx <= x + plant_infos.at(type).w && y <= msgy && msgy <= y + plant_infos.at(type).h && clicked&&!plant_infos.at(type).isSelected) {
//			shop::instance().add_plant(type);
//		}
//		if(!plant_infos.at(type).isSelected){
//			putimage(x + i * 80, y, &plant_infos.at(type).cardimg);
//			if (i % 4 == 3) {
//				y += 100;
//				i = 0;
//			}
//			else {
//				i++;
//			}
//		}
//	}
//}