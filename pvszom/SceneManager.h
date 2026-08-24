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
	static SceneManager& instance() {
		static SceneManager instance;
		return instance;
	}
	void sceneLoop();
	void changeScene(Action action, const std::unique_ptr<scene>cur=nullptr);
private:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	void initmainscene();

	std::stack<std::unique_ptr<scene>>mainscene;

	scene* currentScene = nullptr;
};