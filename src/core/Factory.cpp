#include "Factory.h"
#include "entt/entt.hpp"
#include "components/Map.h"
#include "components/Position.h"
#include "components/Drawable.h"
#include "components/Velocity.h"
#include "components/UnitsSpawnParams.h"
#include "components/Battle.h"
#include "components/Health.h"
#include "components/HealthBar.h"
#include "components/Speed.h"
#include "components/CirlceCollider.h"
#include "components/Parabolic.h"
#include "components/MoveFlip.h"
#include "components/MoveRotation.h"
#include "components/YSort.h"
#include "components/Bullet.h"
#include "components/Solid.h"

entt::entity makeMap(entt::registry &registry)
{
    const float mapWidth = 20.f;
    const float mapHeight = 20.f;
    const float tileWidth = 32.f;
    const float tileHeight = 16.f;
    const float tilesDrawLayer = -1.f;
    const float objectsDrawLayer = 10.f;

    const entt::entity entity = registry.create();
    registry.emplace<Map>(entity, mapWidth, mapHeight, tileWidth, tileHeight, tilesDrawLayer, objectsDrawLayer);

    const auto view = registry.view<Map>();
    view.each([&](const auto entity, auto& map) {
        
    });

    return entity;
}

entt::entity makeMapTile(entt::registry &registry, const std::string& tile, float x, float y, float z)
{
    const entt::entity entity = registry.create();
    registry.emplace<MapTile>(entity);
    registry.emplace<Drawable>(entity, tile);
    registry.emplace<Position>(entity, x, y, z);
    registry.emplace<Anchor>(entity, 0.5f, 0.5f);
    return entity;
}

entt::entity makeMapDecoration(entt::registry &registry, const std::string& tile, float x, float y, float z)
{
    const entt::entity entity = registry.create();
    registry.emplace<MapTile>(entity);
    registry.emplace<Solid>(entity);
    registry.emplace<Drawable>(entity, tile);
    registry.emplace<Position>(entity, x, y, z);
    registry.emplace<Anchor>(entity, 0.5f, 0.75f);
    return entity;
}

entt::entity makeUnitsGenerator(entt::registry &registry, Kind kind)
{
    float spawnInterval = 0.1;
    int count = 20;
    float timer = 0.f;
    float positionX = 1;
    float positionY = 1;
    if (kind == Kind::enemy)
    {
        positionX = 18;
        positionY = 18;
    }
    const entt::entity entity = registry.create();
    registry.emplace<UnitsSpawnParams>(entity, spawnInterval, count, positionX, positionY, kind, timer);
    return entity;
}

entt::entity makeArcher(entt::registry &registry, const std::string& tile, float x, float y, float z, Kind kind)
{
    // радиус поражения лучникам - 40 метров
    // Размер тайла 32х16, карта из 20 тайлов которые равны 100 метрам, 32 * 40 / (100 / 20)
    const float attackDistance = 32 * 40 / 5;
    const float attackCooldown = 1.2;
    const entt::entity entity = registry.create();
    registry.emplace<Drawable>(entity, tile);
    registry.emplace<Position>(entity, x, y, z);
    registry.emplace<Velocity>(entity, 0.f, 0.f);
    registry.emplace<Anchor>(entity, 0.5f, 1.0f);
    registry.emplace<Battle>(entity, attackDistance, attackCooldown, 0.f, kind);
    registry.emplace<Health>(entity, 100.f, 100.f);
    registry.emplace<Speed>(entity, 80.f);
    registry.emplace<CircleCollider>(entity, 6.f);
    registry.emplace<MoveFlip>(entity);
    registry.emplace<YSort>(entity);

    const entt::entity healthBarEntity = registry.create();
    registry.emplace<HealthBar>(healthBarEntity, "assets/bar_back.png", "assets/bar_front.png", entity, -6, -24);
    registry.emplace<Position>(healthBarEntity);


    return entity;
}

entt::entity makeArraow(entt::registry &registry, const std::string& tile, entt::entity target, float startPositionX, float startPositionY, float targetPositionX, float targetPositionY)
{
    const float heightMin = 22.f;
    const float heightMax = 65.f;
    // скорость стрелы 40 метров в секунду
    // Также как с радиусом поражения учитывая размер карты и размер тайла
    // Чтоб стрела прошла 40 метров за секунду размер тайла 32 * 40 метров / масштаб
    const float speed = 32 * 40 / 5;
    const float defaultTimer = 0.f;
    const float damage = 20;

    const entt::entity entity = registry.create();
    registry.emplace<Position>(entity, startPositionX, startPositionY, 11.f);
    registry.emplace<Drawable>(entity, tile);
    registry.emplace<Anchor>(entity, 0.f, 0.5f);
    registry.emplace<MoveRotation>(entity, 0., 0.);
    registry.emplace<Bullet>(entity, damage, target);
    registry.emplace<Parabolic>(entity, startPositionX, startPositionY, targetPositionX, targetPositionY, heightMin, heightMax, speed, defaultTimer);
    return entity;
}
