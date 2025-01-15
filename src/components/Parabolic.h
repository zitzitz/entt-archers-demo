#ifndef _PARABOLIC_COMPONENT_H_
#define _PARABOLIC_COMPONENT_H_

#include "entt/entt.hpp"

struct Parabolic
{
    float startPositionX;
    float startPositionY;
    float targetPositionX;
    float targetPositionY;
    float heightMin;
    float heightMax;
    float speed;
    float timer;
    float height;
};



#endif