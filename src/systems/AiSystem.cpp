#include "AiSystem.h"
#include "components/Battle.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Speed.h"
#include "components/Drawable.h"
#include "components/MoveFlip.h"
#include "math/Vector2.h"
#include "utils/support.h"
#include "core/Factory.h"

entt::entity findNearestEnemy(entt::registry& registry, entt::entity entity)
{
    auto getDistance = [](float x1, float y1, float x2, float y2) -> float {
        return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    };
    auto& entityPos = registry.get<Position>(entity);
    auto& entityBattle = registry.get<Battle>(entity);

    const auto view = registry.view<Battle, Position>();
    float distance = std::numeric_limits<float>::max();

    entt::entity result = entt::null;

    view.each([&](const auto enemyEntity, const auto& battle, const auto& position) {
        auto newDistance = getDistance(entityPos.x, entityPos.y, position.x, position.y);
        if ( entityBattle.kind != battle.kind && newDistance < distance)
        {
            distance = newDistance;
            result = enemyEntity;
        }    
    });

    return result;
}

void aiUpdate(entt::registry &registry, float dt)
{
    const auto view = registry.view<Battle, Position, Velocity, Speed, Drawable>();
    view.each([&](const auto entity, auto& battle, auto& position, auto& velocity, const auto& speed, const auto& drawable) {
        auto enemy = findNearestEnemy(registry, entity);
        battle.target = enemy;
        if (enemy != entt::null)
        {
            auto enemyPosition = registry.get<Position>(enemy);
            auto vectorPosition = Vector2(position);
            auto enemyVectorPosition = Vector2(enemyPosition);

            auto dist = (enemyVectorPosition - vectorPosition).length();

            battle.timer -= dt;
            if (dist <= battle.attackDistance)
            {
                if (registry.any_of<MoveFlip>(entity))
                {
                    registry.get<MoveFlip>(entity).isFlip = enemyPosition.x < position.x ? true : false;
                }

                if (battle.timer <= 0)
                {
                    makeArraow(registry, "assets/arrow.png", enemy, position.x, position.y - drawable.height / 2, enemyPosition.x, enemyPosition.y - drawable.height / 2);
                    battle.timer = battle.cooldown;
                }
            }
            else
            {
                auto dir = (Vector2{enemyPosition.x, enemyPosition.y} - Vector2{position.x, position.y}).normalized();
                velocity.x = dir.x * speed.value;
                velocity.y = dir.y * speed.value * 0.5;
            }
        }
    });
}