#include "sun_manager.h"
#include "input.h"
#include "tool.h"
#include <cstdlib>
#include <easyx.h>

void sun_manager::spawnDrop(float x, float y) {
    sun_drop d;
    if (x < 0.0f) {
        // 天空掉落：随机横向位置，落到场地内随机高度
        d.x = 170.0f + static_cast<float>(rand() % 650);
        d.y = 0.0f;
        d.targetY = 150.0f + static_cast<float>(rand() % 350);
    }
    else {
        // 向日葵产出：从植物位置落下一点点
        d.x = x;
        d.y = y;
        d.targetY = y + 40.0f;
    }
    drops.push_back(d);
}

void sun_manager::update(float deltaTime) {
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0;
        spawnDrop();   // 天空自然掉落
    }

    for (auto it = drops.begin(); it != drops.end();) {
        if (!it->active) { it = drops.erase(it); continue; }

        if (it->y < it->targetY) {
            it->y += 40.0f * deltaTime; // 下落速度：像素/秒
        }

        auto& imgs = sun_registry::instance().getImgs();
        if (imgs.empty()) { ++it; continue; }   // 素材缺失时不做取模运算，避免除零崩溃

        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration<float>(now - it->lastframe).count() > 0.15f) {
            it->curframe = (it->curframe + 1) % static_cast<int>(imgs.size());
            it->lastframe = now;
        }
        putimagePNG(static_cast<int>(it->x), static_cast<int>(it->y), &imgs[it->curframe]);

        if (input::instance().isclicked()
            && input::instance().ishover(static_cast<int>(it->x), static_cast<int>(it->y), 100, 100)) {
            sunCount += 50;
            it->active = false;
        }
        ++it;
    }
}