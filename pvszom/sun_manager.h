#pragma once
#include <vector>
#include "sun.h"

class sun_manager {
public:
    void init() { drops.clear(); spawnTimer = 0; sunCount = 50; } // 初始阳光50，可按关卡调整
    void update(float deltaTime);
    int &getSunCount() { return sunCount; }
    bool trySpend(int cost) {
        if (sunCount >= cost) { sunCount -= cost; return true; }
        return false;
    }

private:
    std::vector<sun_drop> drops;
    float spawnTimer = 0;
    float spawnInterval = 8.0f;
    int sunCount = 50;
};