#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<chrono>
#include<easyx.h>
#include "tool.h"
#include "zombie.h"
#include "plants.h"
#define WIN_WIDTH 900
#define WIN_HEIGHT 600
extern void gameloop();

extern int msgx, msgy;
extern bool clicked;
