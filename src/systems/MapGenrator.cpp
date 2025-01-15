#include "MapGenrator.h"
#include "components/Map.h"
#include "core/Factory.h"
#include "utils/support.h"
#include "math/MathHelper.h"

void spawnMapTiles(entt::registry &registry)
{
    const auto view = registry.view<Map>();
    view.each([&](const auto entity, auto& map) {
        std::vector<std::vector<bool>> solid(map.mapHeight, std::vector<bool>(map.mapWidth, false));
        for (int y = 0; y < map.mapHeight; y++)
        {
            for (int x = 0; x < map.mapWidth; x++)
            {
                auto worldTilePosition = isoToWorld(registry, x, y);

                auto tile = "assets/tile_024.png";
                makeMapTile(registry, tile, worldTilePosition.x, worldTilePosition.y, 0.001 * worldTilePosition.y + map.mapLayer);
                if(getRandomNumber(0, map.mapWidth*map.mapHeight) < 20 && x > 1 && y > 1 && x < map.mapWidth-1 && y < map.mapHeight-1 &&  !solid[x-1][y] && !solid[x][y-1] && !solid[x-1][y-1] && !solid[x+1][y-1])
                {
                    solid[x][y] = true;
                    makeMapDecoration(registry, "assets/tile_064.png", worldTilePosition.x, worldTilePosition.y,  0.001 * worldTilePosition.y + map.objectslayer);
                }
            }
        }
    });
}