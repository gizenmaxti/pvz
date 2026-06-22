#pragma once
#include <easyx.h>
#include <windows.h>
#include <string>
#pragma comment(lib, "MSIMG32.lib")
void putimagePNG(int x, int y, IMAGE* img, int alpha = 255);

int countfiles(const std::string folderpath);
