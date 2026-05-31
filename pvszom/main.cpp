#include <iostream>
#include <string>
#include <vector>
#include<chrono>
#include<graphics.h>
#include "tool.h"
#include "zombie.h"
#include "plants.h"
#include <thread>

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define CARD_COUNT 8

IMAGE imgbg_3;
IMAGE imgwd;

int framecount = 0;
int mousex, mousey;
static int type = 0;
static int suncount = 50;

void userClick() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		int i = (msg.y - 100) / 100;
		int j = (msg.x - 160) / 80;
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 250 && msg.x < 250 + 8 * 70 && msg.y > 5 && msg.y < 5 + 88) {
				type = (msg.x - 250) / 70;
				plantcards[type].dancing(msg.x, msg.y, 180);
				plantcards[type].isslected = true;
			}
		}
		if (msg.message == WM_MOUSEMOVE) {
			mousex = msg.x;
			mousey = msg.y;
		}
		if (msg.message == WM_LBUTTONUP) {
			if (plantcards[type].isslected) {
				if (plantcards[type].isslected && msg.x > 160 && msg.x < 160 + 9 * 80 && msg.y>100 && msg.y < 100 + 5 * 100) {
					if (j >= 0 && j < 9 && i >= 0 && i < 5&&smap[i][j].hp <= 0) {
						smap[i][j].type = type;
						smap[i][j].hp = plantcards[type].hp;
						smap[i][j].x = j;
						smap[i][j].y = i;
						smap[i][j].ti = 0;
						smap[i][j].isAttacking = false;
						smap[i][j].distance = 9999;
					}
					if (j >= 0 && j < 9 && i >= 0 && i < 5 && smap[i][j].hp > 0) {
						if (smap[i][j].addsun == false) {
							suncount += 50;
							smap[i][j].addsun = true;
							smap[i][j].ti = 0;
						}
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
			plantcards[type].dancing(mousex-50, mousey-170, 150);
		}
		else
		plantcards[type].dancing(mousex-30, mousey-25, 150);
	}
}
void updatazombie() {
	for (auto it = allzombie.begin(); it != allzombie.end();) {
		zoms& z = *it;
		if (z.hp <= 0) {
			it=allzombie.erase(it);
		}
		else {
			int col = int(z.x-160) / 80;
			if (col >= 0 && col < 9&&smap[z.row][col].hp > 0) {
				z.isEating = true;
				if (framecount % 30 == 0) {
					smap[z.row][col].hp -= typezombie[z.type].attack;
				}
			}
			else z.isEating = false;
			if(z.row>=0&&z.row<5&&col > 0 && col < 9 && smap[z.row][col].hp > 0 && smap[z.row][col].type==0) {
				z.hp -= 1000;
				smap[z.row][col].isAttacking = true;
			}
			for (int i = 0; i < 9; ++i) {
				if (z.row >= 0 && z.row < 5 && col > 0 && col < 9 && (smap[z.row][i].type == 1 || smap[z.row][i].type == 5 || smap[z.row][i].type == 7) && smap[z.row][i].hp>0) {
					smap[z.row][i].isAttacking = true;
					if (smap[z.row][i].distance <= 0) {
						z.hp -= 1;
					}
					else {
						smap[z.row][i].distance = z.x;
					}
				}
			}
			z.move();
			++it;
		}
	}
}
void gameInit() {
	srand((unsigned int)time(NULL));
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	memset(smap, 0, sizeof(smap));
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
	putzombie(framecount);
	FlushBatchDraw();
	EndBatchDraw();
}
void gameloop() {
	// 目标帧率 60 FPS，每帧应耗时约 16.666... 毫秒
	const auto frameDuration = std::chrono::milliseconds(16);
	auto nextFrameTime = std::chrono::steady_clock::now();

	// 帧率统计变量（每秒打印一次）
	static int frameCount = 0;
	static auto lastStatTime = std::chrono::steady_clock::now();

	while (true) {
		// ----- 执行一帧的逻辑 -----
		framecount++;
		updateWindow();   // 绘制、更新植物、阳光等
		userClick();      // 处理鼠标输入

		// 等待至下一帧的预定时间点（实现精确 60 帧）
		nextFrameTime += frameDuration;
		std::this_thread::sleep_until(nextFrameTime);

		// ----- 帧率统计（每秒输出一次）-----
		frameCount++;
		auto now = std::chrono::steady_clock::now();
		double elapsed = std::chrono::duration<double>(now - lastStatTime).count();
		if (elapsed >= 1.0) {
			double fps = frameCount / elapsed;
			printf("FPS: %.1f, 僵尸数量: %d\n", fps, (int)allzombie.size());
			frameCount = 0;
			lastStatTime = now;
		}
	}
}

int main() {
	gameInit();
	Sleep(1000);
	gameloop();

	return 0;
}