#include <iostream>
#include <string>
#include <vector>
#include<chrono>
#include<graphics.h>
#include "tool.h"
IMAGE imgbg_3, imgwd;
void gameInit() {
	initgraph(1000, 1800);
	loadimage(&imgbg_3, "res/images/bg_3.png");
	loadimage(&imgwd, "res/images/wd.jpg", 650, 100);
	//loadplantcard();
}
void updateWindow() {
	BeginBatchDraw();
	putimage(0, 0, &imgbg_3);//背景
	putimage(160, 0, &imgwd);//卡片窗口
	//drowcard();
	//zombiecreat(framecount);
	//putimagePNG(0, 0, plantcard[1], 180);
	//updatezombie();

	EndBatchDraw();
}
int main() {
	while (1) {
		updateWindow();
		//userClick();
		Sleep(16);
	}
	return 0;
}