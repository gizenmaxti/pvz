#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<chrono>
#include<easyx.h>
#include "tool.h"
//#include "zombie.h"
//#include "plants.h"
#include"SceneManager.h"
class MenuScene;
class adventure_Scene;

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
extern void gameloop();
extern void userclick();

extern int msgx, msgy;
extern bool clicked;

extern SceneManager sceneManager;


