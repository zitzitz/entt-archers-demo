#include "CollisionResponse.h"
#include "components/CirlceCollider.h"
#include "components/Position.h"
#include "components/Health.h"
#include "math/Vector2.h"

std::optional<std::pair<Vector2, float>> getCircleCollisionPoint(entt::registry &registry, const entt::entity& entityA, const entt::entity& entityB) {
    auto cirlceAPos = Vector2( registry.get<Position>(entityA) );
    auto cirlceBPos = Vector2( registry.get<Position>(entityB) );

    auto& cirlceARadius = registry.get<CircleCollider>(entityA).r;
    auto& cirlceBRadius = registry.get<CircleCollider>(entityB).r;

    Vector2 difference = cirlceAPos - cirlceBPos;
    auto distanceSquared = difference.length() * difference.length();
    auto radiusSum = cirlceARadius + cirlceBRadius;

    if (distanceSquared < (radiusSum * radiusSum)) {
        auto distance = std::sqrt(distanceSquared);
        auto overlap = (radiusSum - distance);

        auto collisionPoint = cirlceAPos + (difference.normalized() * (cirlceARadius - overlap / 2));

        Vector2 direction = collisionPoint - cirlceAPos;
        
        return std::make_pair(direction.normalized(), overlap);
    }

    return {};
}

void collisionResponse(entt::registry &registry)
{
    const auto view = registry.view<Position, CircleCollider, Health>();
    view.each([&](const auto entity, auto& position, const auto& collider, const auto& health) {
        Vector2 correction;
        for(auto collideEntity : view)
        {
            if (collideEntity != entity)
            {
                auto collide = getCircleCollisionPoint(registry, entity, collideEntity);
                if(collide)
                {
                    auto [normal, distance] = *collide;
                    normal.rotate(static_cast<float>(rand() % 181 - 90));
                    auto proj = Vector2::dot(correction, normal);
                    auto compensation = normal * (distance - proj);
                    compensation.normalize();

                    position.x += compensation.x;
                    position.y += compensation.y;
                }
            }
        }
    });
}
