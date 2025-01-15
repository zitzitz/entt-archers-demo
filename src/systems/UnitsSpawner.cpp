#include "UnitsSpawner.h"
#include "components/UnitsSpawnParams.h"
#include "utils/support.h"
#include "core/Factory.h"

void spawnUnits(entt::registry &registry, float dt)
{
    const auto view = registry.view<UnitsSpawnParams>();
    view.each([&](const auto entity, auto& spawnParams) {

        spawnParams.timer -= dt;

        if ( spawnParams.timer <= 0 )
        {
            auto worldSpawnPositon = isoToWorld(registry, spawnParams.spawnPositionX, spawnParams.spawnPositionY);
            makeArcher(registry, "assets/archer2.png", worldSpawnPositon.x, worldSpawnPositon.y, 1, spawnParams.kind);//, 0, 0, 64, 64);
            spawnParams.count--;
            spawnParams.timer = spawnParams.spawnInterval;
            if ( spawnParams.count <= 0 )
            {
                registry.destroy(entity);
            }
        }
    });
}