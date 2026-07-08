#include"menu.h"
#include"adventure.h"
int selected = -1;
void MenuScene::load() {
	loadimage(&menu_begin, "res\\images\\menu\\menu_begin.jpg", WIN_WIDTH, WIN_HEIGHT);
	
	buttons[0].x = 450;
	buttons[0].y=60;
	buttons[0].width = 380;
	buttons[0].height = 150;

	buttons[1].x = 450;
	buttons[1].y = 172;
	buttons[1].width = 360;
	buttons[1].height = 130;

	buttons[2].x = 455;
	buttons[2].y = 257;
	buttons[2].width = 325;
	buttons[2].height = 120;

	buttons[3].x = 460;
	buttons[3].y = 325;
	buttons[3].width = 300;
	buttons[3].height = 120;

	for (int i = 0; i < button_count; ++i) {
		std::string img_path = "res\\images\\menu\\button" + std::to_string(i + 1) + ".png";
		std::string select_img_path = "res\\images\\menu\\select_button" + std::to_string(i + 1) + ".png";
		loadimage(&buttons[i].img, img_path.c_str(), buttons[i].width, buttons[i].height);
		loadimage(&buttons[i].select_img, select_img_path.c_str(), buttons[i].width, buttons[i].height);
	}
}

bool MenuScene::select_button(int x, int y, button b) {
	if (x > b.x && x<b.x + b.width && y>b.y+40 && y < b.y + b.height-20) {
		return true;
	}
	else {
		return false;
	}
}

void MenuScene::draw_button() {
	for (int i = 0; i < button_count; ++i) {
		if (select_button(msgx, msgy, buttons[i])) {
			putimagePNG(buttons[i].x, buttons[i].y, &buttons[i].select_img);
			if (clicked) {
				putimagePNG(buttons[i].x, buttons[i].y, &buttons[i].img);
				selected = i;
			}
		}
		else {
			putimagePNG(buttons[i].x, buttons[i].y, &buttons[i].img);
		}
	}
}

void MenuScene::update() {
	BeginBatchDraw();
	putimage(0, 0, &menu_begin);
	draw_button();
	FlushBatchDraw();
	EndBatchDraw();
}

