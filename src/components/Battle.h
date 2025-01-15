#ifndef _BATTLE_COMPONENT_H_
#define _BATTLE_COMPONENT_H_

#include "entt/entt.hpp"
#include "utils/support.h"

struct Battle {
    float attackDistance;
    float cooldown;
    float timer;
    Kind kind;
    entt::entity target = entt::null;
};

#endif