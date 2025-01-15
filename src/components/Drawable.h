#ifndef _DRAWBLE_COMPONENT_H_
#define _DRAWBLE_COMPONENT_H_

#include <string>
#include "entt/entt.hpp"

struct Drawable
{
    std::string tile;
    int width;
    int height;
};

struct Anchor
{
    float x = 0.5;
    float y = 0.5;
};

#endif