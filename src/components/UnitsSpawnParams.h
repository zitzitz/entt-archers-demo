#ifndef _UNITS_SPAWN_PARAMS_COMPONENT_H_
#define _UNITS_SPAWN_PARAMS_COMPONENT_H_

#include "utils/support.h"

struct UnitsSpawnParams {
    float spawnInterval;
    int count;
    float spawnPositionX;
    float spawnPositionY;
    Kind kind;
    float timer;
};

#endif