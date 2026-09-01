#include "game.h"
#include "menu.h"
#include "adventure.h"
#include "SceneManager.h"
void gameloop() {

	SceneManager::instance().sceneLoop();
}

