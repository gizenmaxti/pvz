#pragma once
#include <easyx.h>
#include <windows.h>
#include <string>
#include <vector>
#include <chrono>
#include <functional>
#pragma comment(lib, "MSIMG32.lib")
void putimagePNG(int x, int y, IMAGE* img, int alpha = 255);

int countfiles(const std::string folderpath);

struct timer{
	std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
	void updatetime(float time, std::function <void()>f);
};
extern std::vector<timer>timers;