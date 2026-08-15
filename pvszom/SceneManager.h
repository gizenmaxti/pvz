#pragma once
#include <stack>
#include<memory>
#include "scene.h"
enum class SceneType {
	MainMenu,
	Adventure,
	Survival,
	MiniGame,
	Store,
	Settings,
	Loading,
	GameOver
};

enum class Action {
	push,
	pop,
	replace,
	null
};

class SceneManager {
public:	

	void sceneLoop();
	void changeScene(Action action, const std::unique_ptr<scene>cur);
private:
	void initmainscene();

	std::stack<std::unique_ptr<scene>>mainscene;
	
	scene* currentScene = nullptr;
};