#ifndef _SUPPORT_H_
#define _SUPPORT_H_

#include "entt/entt.hpp"
#include "math/Vector2.h"

enum class Kind {
    player,
    enemy
};

Vector2 isoToWorld(entt::registry &registry, float x, float y);
Vector2 worldToIso(entt::registry& registry, float x, float y);

#endif