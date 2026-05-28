//#include<easyx.h>
//#include"Game.h"
//
//#define WIN_WIDTH 900
//#define WIN_HEIGHT 600
//
//IMAGE imgbg_3,imgwd;
//int framecount = 0;
//
//void gameinit() {
//	initgraph(WIN_WIDTH, WIN_HEIGHT);
//	loadimage(&imgbg_3, "res/images/bg_3.png");
//	loadimage(&imgwd, "res/images/wd.jpg", 650, 100);
//}
//
//void updateWindow() {
//	BeginBatchDraw();
//	putimage(0, 0, &imgbg_3);//背景
//	putimage(160, 0, &imgwd);//卡片窗口
//	EndBatchDraw();
//}
//
//void gameloop() {
//	while (1) {
//		framecount++;
//		updateWindow();
//		//userClick();
//		Sleep(16);
//	}
//}