#ifndef _BULLET_COMPONENT_H_
#define _BULLET_COMPONENT_H_

#include "entt/entt.hpp"

struct Bullet {
    float damage;
    entt::entity target = entt::null;
};

#endif