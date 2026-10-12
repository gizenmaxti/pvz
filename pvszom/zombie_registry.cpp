#include "zombie_registry.h"

void zombie_registry::load() {
    int w = 144, h = static_cast<int>(166 * 0.8);
    zombie_registry::instance().putconfig(Zombietype::zombie,
        zombieinfo(200, 15.0f, 20, "res\\images\\zombies\\zombie\\walk", "res\\images\\zombies\\zombie\\eat", w, h));

    zombie_registry::instance().putconfig(Zombietype::flag,
        zombieinfo(200, 15.0f, 20, "res\\images\\zombies\\flag\\walk", "res\\images\\zombies\\flag\\eat", w, h));

    zombie_registry::instance().putconfig(Zombietype::iron,
        zombieinfo(500, 10.0f, 25, "res\\images\\zombies\\iron\\walk", "res\\images\\zombies\\iron\\eat", w, h));

    zombie_registry::instance().putconfig(Zombietype::loadblock,
        zombieinfo(350, 12.0f, 20, "res\\images\\zombies\\loadblock\\walk", "res\\images\\zombies\\loadblock\\eat", w, h));

    zombie_registry::instance().putconfig(Zombietype::rugby,
        zombieinfo(400, 25.0f, 30, "res\\images\\zombies\\rugby\\walk", "res\\images\\zombies\\rugby\\eat", w, h));
}