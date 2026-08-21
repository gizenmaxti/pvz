#include <stdexcept>
#include "menu.h"
#include "adventure.h"
#include "SceneManager.h"
#include "adventure_game.h"
#include "input.h"
#define scenebegin adventure_game_Scene
//#define scenebegin MenuScene

void SceneManager::changeScene(Action action=Action::pop, std::unique_ptr<scene>cur =nullptr) {
	if (action != Action::pop && (cur == nullptr || cur.get() == nullptr)) {
		throw std::logic_error("此功能未开发");
	}
	switch (action) {
	case Action::push:
		cur->load();
		mainscene.push(std::move(cur));
		break;
	case Action::pop:
		mainscene.top()->unload();
		mainscene.pop();
		break;
	case Action::replace:
		mainscene.top()->unload();
		mainscene.pop();
		cur->load();
		mainscene.push(std::move(cur));
		break;
	default:
		break;
	}
}

void SceneManager::initmainscene() {
	mainscene = std::stack<std::unique_ptr<scene>>();
	//changeScene(Action::push, std::make_unique<MenuScene>());
	changeScene(Action::push, std::make_unique<scenebegin>());
}

void SceneManager::sceneLoop() {
	initmainscene();
	while (1) {
		try {
			input::instance().userclick();
			/*clicked = false;
			userclick();*/
			if (!mainscene.empty()) {
				mainscene.top()->update();
			}
		}
		catch (const std::exception& e) {
			MessageBoxA(nullptr, e.what(), "错误", MB_OK);
		}
		Sleep(16);
	}
}
