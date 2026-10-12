#include<easyx.h>
#include"grassland.h"
#include"plant_registry.h"
#include"tool.h"
#include"adventure_game.h"

bool grassland::planting(int row, int col, Planttype t, int suncount) {
	// 边界与占位校验统一走 row/col 成员，避免硬编码 5/9 与成员不一致
	if (row < 0 || row >= this->row || col < 0 || col >= this->col) return false;
	if (land[row][col].has_value()) return false;
	if (suncount < plant_registry::instance().get_plant_info(t).value) return false;

	land[row][col].emplace(t);
	return true;
}
void grassland::remove(int row, int col) {
	land[row][col] = std::nullopt;
}
void grassland::update() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (land[i][j].has_value() && land[i][j].value().gethp() <= 0)land[i][j] = std::nullopt;
			if (land[i][j].has_value())
				putimagePNG(170 + j * 80, 90 + i * 100, &land[i][j].value().dance());
		}
	}
}


plant* grassland::getPlant(int row, int col) {
	if (row < 0 || row >= this->row || col < 0 || col >= this->col) return nullptr;
	if (!land[row][col].has_value()) return nullptr;
	return &land[row][col].value();
}

void grassland::damagePlant(int row, int col, int dmg) {
	if (row < 0 || row >= this->row || col < 0 || col >= this->col) return;
	if (land[row][col].has_value()) {
		land[row][col]->takeDamage(dmg);
	}
}