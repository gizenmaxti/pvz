#pragma once

enum class Zombietype {
    zombie,     // 普通僵尸
    flag,       // 旗帜僵尸（首波信号）
    iron,       // 铁桶僵尸（高血量）
    loadblock,  // 路障僵尸（中等血量）
    rugby       // 橄榄球僵尸（快速、高血量）
};