#pragma once
#include <easyx.h>

struct bullet {
    bullet(float x, float y, int row, int damage, const IMAGE* img)
        : x(x), y(y), row(row), damage(damage), img(img) {
    }
    float x, y;
    int row;
    int damage;
    const IMAGE* img;
    bool active = true;
};