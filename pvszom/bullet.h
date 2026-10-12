#pragma once
#include <easyx.h>

struct bullet {
    bullet(float x, float y, int row, int damage, const IMAGE* img, bool ice = false)
        : x(x), y(y), row(row), damage(damage), img(img), ice(ice) {
    }
    float x, y;
    int row;
    int damage;
    const IMAGE* img;
    bool ice = false;      // 寒冰子弹：命中后给僵尸附加减速
    bool active = true;
};