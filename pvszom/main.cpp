#include <iostream>
#include <string>
#include <vector>
#include<chrono>
#include<easyx.h>
#include "tool.h"
#include "zombie.h"
#include "plants.h"
#include "game.h"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define CARD_COUNT 8
#define INITSUN 50

IMAGE imgbg_3;
IMAGE imgwd;

int framecount = 0;
int mousex, mousey;
static int type = 0;
int suncount = INITSUN;
int sunframe = 0;
float suny = 0;
bool suncatch = true;
float drop_the_sunx = rand() % WIN_WIDTH + 160;
float drop_the_suny = rand() % WIN_HEIGHT + 100;
bool gameover = false;
bool win = false;

void drowsun() {
	setbkmode(TRANSPARENT);
	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, "Arial");
	std::string suntext = "阳光: " + std::to_string(suncount);
	outtextxy(165,71,suntext.c_str());
}
//void drop_the_sun() {
//	sunframe = (sunframe + 1) % plantcards[2].bullet.size();
//	if (suncatch) {
//		putimagePNG(drop_the_sunx, suny, &plantcards[2].bullet[sunframe], 255);
//	}
//	if(framecount%1000==0) {
//		drop_the_sunx = rand() % (WIN_WIDTH) + 160;
//		drop_the_suny = rand() % (WIN_HEIGHT) + 100;
//		suncatch = true;
//	}
//	if(suny< drop_the_suny)suny++;
//}


bool isbuttondown = false;
void userClick() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		int i = (msg.y - 100) / 100;
		int j = (msg.x - 160) / 80;
		if (msg.message == WM_LBUTTONDOWN) {
			isbuttondown = true;
			if (msg.x > 250 && msg.x < 250 + 8 * 70 && msg.y > 5 && msg.y < 5 + 88) {
				type = (msg.x - 250) / 70;
				if (suncount >= plantcards[type].value) {
					if(type ==3)plantcards[type].dancing(msg.x-150, msg.y-70, 180);
					plantcards[type].dancing(msg.x, msg.y, 180);
					plantcards[type].isslected = true;
				}
			}
		}
		if (msg.message == WM_MOUSEMOVE) {
			mousex = msg.x;
			mousey = msg.y;
		}
		if (msg.message == WM_LBUTTONUP) {
			isbuttondown = false;
			if (plantcards[type].isslected) {
				if (plantcards[type].isslected && msg.x > 160 && msg.x < 160 + 9 * 80 && msg.y>100 && msg.y < 100 + 5 * 100) {
					if (j >= 0 && j < 9 && i >= 0 && i < 5&&smap[i][j].hp <= 0) {
						smap[i][j].type = type;
						smap[i][j].hp = plantcards[type].hp;
						smap[i][j].x = j;
						smap[i][j].y = i;
						smap[i][j].ti = 0;
						smap[i][j].isAttacking = false;
						suncount -= plantcards[type].value;
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
			for (int i = 0; i < 9; ++i) {
				if (smap[z.row][i].hp > 0) {
					smap[z.row][i].isAttacking = false;
				}
			}
			it=allzombie.erase(it);

		}
		else {
			int col = int(z.x - 160) / 80;
			if (col >= 0 && col < 9 && smap[z.row][col].hp > 0) {
				z.isEating = true;
				if (framecount % 30 == 0) {
					smap[z.row][col].hp -= typezombie[z.type].attack;
				}
			}
			else z.isEating = false;

			if (smap[z.row][col].hp > 0 && smap[z.row][col].type == 0) {
				smap[z.row][col].isAttacking = true;
				z.hp -= 1000;
			}

			if (z.x < 930) {
				for (int i = 0; i < 9; ++i) {
					if (smap[z.row][i].hp > 0 && smap[z.row][i].type == 1 || smap[z.row][i].type == 5 || smap[z.row][i].type == 7) {
						smap[z.row][i].isAttacking = true;
					}
				}
			}
			
			for (auto& b : bullets) {
				if (b.active) {
					if(b.type==1||b.type==5||b.type==7) {
						if ((b.y - 90) / 100 == z.row && b.x>= smap[z.row][int((b.x - 160) / 80)].x&&smap[z.row][int((b.x - 160) / 80)].hp>=0&&smap[z.row][int((b.x-160)/80)].type == 6) {
							b.damage = 20;
							b.img = plantcards[6].bullet[0];
						}
						if (b.x > z.x - 30 && b.x < z.x + 80 && b.y > z.zy && b.y < z.zy + 100) {
							z.hp -= b.damage;
							b.active = false;
						}
					}
					/*if ((b.type==999||b.type==2)&& isbuttondown&& mousey + 20 >= b.y + 50 && mousey - 20 <= b.y + 50 && mousex + 20 >= b.x + 40 && mousex - 20 <= b.x + 40) {
						b.active = false;
						suncount += b.damage;
					}*/
				}
				
				if (b.x > 900)b.active = false;
			}
			
			z.move();
			++it;
			/*if(z.x < 140||allzombie.size() == 0&&n==0) {
				gameover = true;
				if (z.x < 140)win = false;
				else win = true;
			}*/
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
	putimage(0, 0,&imgbg_3);//背景
	putimage(160, 0, &imgwd);//卡片窗口
	drawcard();
	updataglass();
	drowsun();
	updatebllet();
	drop_the_sun();
	updatazombie();
	updatamouse();
	putzombie();
	//putzombie(framecount);
	FlushBatchDraw();
	EndBatchDraw();
}



//void gameloop() {
//	while (!gameover) {
//		framecount++;
//		updateWindow();
//		userClick();
//		Sleep(16);
//	}
//}

int main() {
	gameInit();
	Sleep(1000);
	gameloop();

	return 0;
}