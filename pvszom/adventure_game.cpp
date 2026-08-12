#include <easyx.h>
#include "adventure_game.h"
void adventure_game_Scene::update() {
	BeginBatchDraw();
	putimage(0, 0, &background);
	putimage(160, 0, &shop);
	FlushBatchDraw();
	EndBatchDraw();
}