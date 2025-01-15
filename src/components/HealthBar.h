#ifndef _HEALTHBAR_COMPONENT_H_
#define _HEALTHBAR_COMPONENT_H_

#include <string>
#include "entt/entt.hpp"

struct HealthBar {
    std::string back;
    std::string front;
    entt::entity unit;
    int offsetX;
    int offsetY;
    float progress;
};

#endif