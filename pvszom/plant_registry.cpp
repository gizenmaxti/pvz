#include"plant_registry.h"
void plant_registry::load() {
	plant_infos.emplace(Planttype::peashooter, plantinfo(100, 100, 5, "Peashooter", "res\\images\\plants\\peashooter_card.png", "res\\images\\cards\\peashooter.png", 63, 88));
	plant_infos.emplace(Planttype::sunflower, plantinfo(100, 50, 5, "Sunflower", "res\\images\\plants\\sunflower_card.png", "res\\images\\cards\\sunflower.png", 63, 88));
}