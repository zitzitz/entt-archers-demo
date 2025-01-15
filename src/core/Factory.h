#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "entt/entt.hpp"
#include "utils/support.h"

entt::entity makeMap(entt::registry &registry);
entt::entity makeMapTile(entt::registry &registry, const std::string& tile, float x, float y, float z);
entt::entity makeMapDecoration(entt::registry &registry, const std::string& tile, float x, float y, float z);
entt::entity makeUnitsGenerator(entt::registry &registry, Kind kind);
entt::entity makeArcher(entt::registry &registry, const std::string& tile, float x, float y, float z, Kind kind);
entt::entity makeArraow(entt::registry &registry, const std::string& tile, entt::entity target, float startPositionX, float startPositionY, float targetPositionX, float targetPositionY);

#endif