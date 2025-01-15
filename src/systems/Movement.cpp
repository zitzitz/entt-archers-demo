#include "Movement.h"
#include "core/Factory.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/MoveFlip.h"
#include "components/Battle.h"
#include "components/Solid.h"
#include "SDL.h"
#include <iostream>

void movementUnits(entt::registry &registry, float dt)
{
    const auto view = registry.view<Position, Velocity>();

    view.each([&](const auto entity, auto& position, auto& velocity) {
        auto newPosition = Vector2(position.x + velocity.x * dt, position.y + velocity.y * dt);

        const auto viewSolid = registry.view<Position, Solid>();
        viewSolid.each([&](const auto entity, auto& solidPosition) {
            auto solidIsoPosition = worldToIso(registry, solidPosition.x, solidPosition.y);
            auto isoPosition = worldToIso(registry, newPosition.x, newPosition.y);
            if (( solidIsoPosition - isoPosition).length() < 1 )
            {
                newPosition.x = position.x;
                newPosition.y = position.y;
            }
        });

        position.x = newPosition.x;
        position.y = newPosition.y;

        if (registry.all_of<MoveFlip, Battle>(entity))
        {
            if (registry.get<Battle>(entity).target != entt::null)
            {
                registry.get<MoveFlip>(entity).isFlip = registry.get<Position>(registry.get<Battle>(entity).target).x < position.x;
            }
            else
            {
                if(velocity.x < 0)
                {
                    registry.get<MoveFlip>(entity).isFlip = true;
                }
                else if(velocity.x > 0)
                {
                    registry.get<MoveFlip>(entity).isFlip = false;
                }
                
            }
        }

        velocity.x = 0;
        velocity.y = 0;
    });
}