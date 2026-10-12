#include<easyx.h>
#include"grassland.h"
#include"plant_registry.h"
#include"tool.h"

bool grassland::planting(int row, int col, Planttype t, int suncount) {
	if (row < 0 || row >= this->row || col < 0 || col >= this->col) return false;
	if (land[row][col]) return false;                       // 该格已有植物
	if (suncount < plant_registry::instance().get_plant_info(t).value) return false;

	auto p = plant_registry::create(t);
	if (!p) return false;                                   // 未注册工厂的类型
	land[row][col] = std::move(p);
	return true;
}

void grassland::remove(int row, int col) {
	if (row < 0 || row >= this->row || col < 0 || col >= this->col) return;
	land[row][col].reset();
}

// 植物动画推进与死亡清理
void grassland::update(float deltaTime) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			auto& cell = land[i][j];
			if (!cell) continue;

			if (cell->gethp() <= 0) {   // 血量归零则移除
				cell.reset();
				continue;
			}
			cell->updateAnimation(deltaTime);
		}
	}
}

// 统一在这里绘制，保证层级：先画所有植物，再由 battle_manager 绘制僵尸与子弹
void grassland::draw() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (land[i][j])
				putimagePNG(170 + j * 80, 90 + i * 100, &land[i][j]->dance());
		}
	}
}

plant* grassland::getPlant(int row, int col) {
	if (row < 0 || row >= this->row || col < 0 || col >= this->col) return nullptr;
	return land[row][col].get();
}

void grassland::damagePlant(int row, int col, int dmg) {
	if (row < 0 || row >= this->row || col < 0 || col >= this->col) return;
	if (land[row][col]) land[row][col]->takeDamage(dmg);
}
