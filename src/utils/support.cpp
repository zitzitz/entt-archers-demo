#include "support.h"
#include "components/Map.h"

Vector2 isoToWorld(entt::registry& registry, float x, float y)
{
    const auto view = registry.view<Map>();
    auto mapEntity = view.front();
    auto& map = registry.get<Map>(mapEntity);
    float ix = (x + y) / 2 * map.tileWidth;
    float iy = (x - y) / 2 * map.tileHeight;
    return {ix, iy};
}

Vector2 worldToIso(entt::registry& registry, float x, float y)
{
    const auto view = registry.view<Map>();
    auto mapEntity = view.front();
    auto& map = registry.get<Map>(mapEntity);
    float ix = (x / map.tileWidth) - (y / map.tileHeight);
    float iy = (y / map.tileHeight) + (x / map.tileWidth);
    return {ix, iy};
}