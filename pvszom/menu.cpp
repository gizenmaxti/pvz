#include"menu.h"
#include"adventure.h"


void MenuScene::load() {
	loadimage(&menu_begin, "res\\images\\menu\\menu_begin.jpg", WIN_WIDTH, WIN_HEIGHT);
	
	buttons.clear();
	buttons.emplace_back(450, 60, 380, 150, "res\\images\\menu\\button1.png", "res\\images\\menu\\select_button1.png", []() {return std::make_unique<adventure_Scene>(); });
	buttons.emplace_back(450, 172, 360, 130, "res\\images\\menu\\button2.png", "res\\images\\menu\\select_button2.png", nullptr);
	buttons.emplace_back(455, 257, 325, 120, "res\\images\\menu\\button3.png", "res\\images\\menu\\select_button3.png", nullptr);
	buttons.emplace_back(460, 325, 300, 120, "res\\images\\menu\\button4.png", "res\\images\\menu\\select_button4.png", nullptr);
}

void MenuScene::draw_button() {
	for (int i = 0; i < buttons.size(); ++i) {
		buttons[i].hover(buttons[i].ishover(msgx, msgy));
	}
}


void MenuScene::update() {
	BeginBatchDraw();
	putimage(0, 0, &menu_begin);
	draw_button();
	FlushBatchDraw();
	EndBatchDraw();
}

