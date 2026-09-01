#include <iostream>
#include <string>
#include <vector>
#include<chrono>
#include<easyx.h>
#include"SceneManager.h"

void gameInit() {
	srand((unsigned int)time(NULL));
	initgraph(WIN_WIDTH, WIN_HEIGHT);
}
int main() {
	gameInit();
	SceneManager::instance().sceneLoop();
	return 0;
}