#include "game.h"
#include "menu.h"
#include "adventure.h"
#include "SceneManager.h"


int msgx, msgy;
bool clicked;

SceneManager sceneManager;

void userclick() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		msgx = msg.x;
		msgy = msg.y;
		if(msg.message == WM_LBUTTONDOWN) {
			clicked = true;
		}
		
	}
}

void adventure_loop() {
	adventure_Scene adventure;
	adventure.load();
	while (1) {
		adventure.update();
	}
}

void gameloop() {

	sceneManager.sceneLoop();
}

