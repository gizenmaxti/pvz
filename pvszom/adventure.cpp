#include "adventure.h"
void adventure_Scene::load() {
	loadimage(&background, "res\\images\\menu\\select_level.jpg", WIN_WIDTH, WIN_HEIGHT);
	
}
void adventure_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	FlushBatchDraw();
	EndBatchDraw();
}