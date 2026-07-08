#include "game.h"
#include "menu.h"

int msgx, msgy;
bool clicked;
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

void gameloop() {
	MenuScene menu;
	menu.load();
	while (1) {
		clicked = false;
		userclick();
		menu.update();
		Sleep(16);
	}
}
