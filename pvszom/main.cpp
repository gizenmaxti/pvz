#include <iostream>
#include <string>
#include <vector>
#include<chrono>
#include<graphics.h>
#include "tool.h"
#include "zombie.h"
#include "plants.h"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define CARD_COUNT 8

IMAGE imgbg_3;
IMAGE imgwd;

int framecount = 0;
int x, y;
static int type = 0;
void userClick() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 250 && msg.x < 250 + 8 * 70 && msg.y > 5 && msg.y < 5 + 88) {
				type = (msg.x - 250) / 70;
				plantcards[type].dancing(msg.x, msg.y, 180);
				plantcards[type].isslected = true;
			}
		}
		if (msg.message == WM_MOUSEMOVE) {
			x = msg.x;
			y = msg.y;
		}
		if (msg.message == WM_LBUTTONUP) {
			if (plantcards[type].isslected) {
				if (plantcards[type].isslected && msg.x > 160 && msg.x < 160 + 9 * 80 && msg.y>100 && msg.y < 100 + 5 * 100) {
					int i = (msg.y - 100) / 100;
					int j = (msg.x - 160) / 80;
					if (smap[i][j].hp <= 0) {
						smap[i][j].pla = &plantcards[type];
						smap[i][j].hp = plantcards[type].hp;
						smap[i][j].x = j;
						smap[i][j].y = i;
					}
				}
				plantcards[type].isslected = false;
			}
		}

	}
}

void updatamouse() {
	if(plantcards[type].isslected&&type>=0&&type<=8) {
		if (type == 3) {
			plantcards[type].dancing(x-50, y-170, 150);
		}
		else
		plantcards[type].dancing(x-30, y-25, 150);
	}
}
void updatazombie() {
	for (auto& z : allzombie) {
		int y = int(z.x) / 100;
		if(y>=0&&y<=8&& smap[z.row][y].hp > 0 ) {
			z.isEating = true;
			if (framecount % 30 == 0) {
				smap[z.row][y].hp -= z.z->attack;
			}
		}
		else z.isEating = false;
		z.move();
	}
}
void gameInit() {
	srand((unsigned int)time(NULL));
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	loadimage(&imgbg_3, "res\\images\\bg_3.png");
	loadimage(&imgwd, "res\\images\\wd.jpg", 650, 100);
	loadplantcard();
	loadzombie();
}
void updateWindow() {
	BeginBatchDraw();
	putimage(0, 0, &imgbg_3);//背景
	putimage(160, 0, &imgwd);//卡片窗口
	drawcard();
	updataglass();
	updatamouse();
	updatazombie();
	/*zombiecreat(framecount);
	updatezombie();*/
	putzombie(framecount);
	FlushBatchDraw();
	EndBatchDraw();
}
void gameloop() {
	while (1) {
		framecount++;
		updateWindow();
		userClick();
		Sleep(16);
	}
}

int main() {
	gameInit();
	Sleep(1000);
	gameloop();

	return 0;
}