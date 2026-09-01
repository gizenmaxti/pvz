#pragma once
#include <easyx.h>
#include <chrono>
#include <vector>
#include "tool.h"

class sun_registry {
public:
    static sun_registry& instance() {
        static sun_registry inst;
        return inst;
    }
    void load() {
        int count = countfiles("res\\images\\plants\\sun");
        imgs.resize(count);
        for (int i = 0; i < count; ++i)
            loadimage(&imgs[i], ("res\\images\\plants\\sun\\" + std::to_string(i) + ".png").c_str(), 50, 50);
    }
    const std::vector<IMAGE>& getImgs() const { return imgs; }
private:
    std::vector<IMAGE> imgs;
};

struct sun_drop {
    float x, y;
    float targetY;
    int curframe = 0;
    std::chrono::steady_clock::time_point lastframe = std::chrono::steady_clock::now();
    bool active = true;
};