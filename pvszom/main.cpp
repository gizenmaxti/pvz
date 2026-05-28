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

std::vector<zombie>zombies;
IMAGE imgbg_3;
IMAGE imgwd;

int framecount = 0;

void pushzombie(int hp, int type, int attack, float speed, int x, int y, int time) {
	static int spwarn = 0, nextspwar = 0;
	if (spwarn >= nextspwar) {
		zombies.push_back(initzombie(hp, type, attack, speed, x, y));
		spwarn = 0;
		nextspwar = rand() % time + 400;
	}
	spwarn++;
}

void zombiecreat(int framecount) {
	static int spwarn = 0, nextspwar = 0;
	int row = rand() % 5;
	int type = rand() % 4;
	if (framecount == 60)zombies.push_back(initzombie(100, 4, 20, 0.15, 800, 100 * row));
	if (framecount > 400) {
		pushzombie(100, 0, 20, 0.15, 800, 100 * row, 700);
	}
	if (framecount > 900) {
		pushzombie(200, 2, 20, 0.15, 800, 100 * row, 2000);
	}
	if (framecount > 2000) {
		pushzombie(500, 1, 20, 0.15, 800, 100 * row, 3000);
	}
	if (framecount > 5000) {
		pushzombie(1000, 3, 20, 0.5, 800, 100 * row, 4000);
	}
}
void updatezombie() {
	for (auto& z : zombies) {
		z.move();
	}
}
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
					if (smap[i][j].pla.hp <= 0) {
						smap[i][j].pla = plantcards[type];
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
void gameInit() {
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	loadimage(&imgbg_3, "res\\images\\bg_3.png");
	loadimage(&imgwd, "res\\images\\wd.jpg", 650, 100);
	loadplantcard();
}
void updateWindow() {
	BeginBatchDraw();
	putimage(0, 0, &imgbg_3);//背景
	putimage(160, 0, &imgwd);//卡片窗口
	drawcard();
	updataglass();
	updatamouse();
	zombiecreat(framecount);
	updatezombie();
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