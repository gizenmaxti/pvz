#include "sun_manager.h"
#include "input.h"
#include "tool.h"
#include <cstdlib>
#include <easyx.h>

void sun_manager::update(float deltaTime) {
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0;
        sun_drop d;
        d.x = 170 + rand() % 650;
        d.y = 0;
        d.targetY = 150 + rand() % 350;
        drops.push_back(d);
    }

    for (auto it = drops.begin(); it != drops.end();) {
        if (!it->active) { it = drops.erase(it); continue; }

        if (it->y < it->targetY) {
            it->y += 40.0f * deltaTime; // 下落速度：像素/秒
        }

        auto& imgs = sun_registry::instance().getImgs();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration<float>(now - it->lastframe).count() > 0.15f) {
            it->curframe = (it->curframe + 1) % imgs.size();
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