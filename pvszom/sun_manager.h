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

    // 天上掉落的阳光与向日葵产出的阳光共用这套掉落逻辑。
    // x/y 传入负值表示随机位置（用于天空掉落）。
    void spawnDrop(float x = -1.0f, float y = -1.0f);

    // 向日葵产出时调用：从该格位置落下一颗可点击收集的阳光
    void spawnFromPlant(int row, int col) {
        spawnDrop(170.0f + static_cast<float>(col) * 80.0f,
                  90.0f + static_cast<float>(row) * 100.0f);
    }

private:
    std::vector<sun_drop> drops;
    float spawnTimer = 0;
    float spawnInterval = 8.0f;
    int sunCount = 50;
};
