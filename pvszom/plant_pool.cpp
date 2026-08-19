#include"plant_pool.h"

void plant_pool::update() {
	int x = 20, y = 100;
	int i = 0;
	for (auto& card : plantpool) {
		card.x = x + i * 80;
		card.y = y;
		if (card.x <= msgx && msgx <= card.x + plant_registry::instance().get_plant_info(card.type).w && card.y <= msgy && msgy <= card.y + plant_registry::instance().get_plant_info(card.type).h && clicked && card.isSelected==true) {

		}
		if (card.isSelected==false) {
			putimage(0, 0, &plant_registry::instance().get_plant_info(card.type).cardimg);
		}
	}
}