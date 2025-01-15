#include "ApplyDamage.h"
#include "components/Bullet.h"
#include "components/Position.h"
#include "components/Health.h"
#include "components/Drawable.h"
#include "math/Vector2.h"

bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

void applyDamage(entt::registry &registry)
{
    const auto view = registry.view<Bullet, Position, Drawable, Anchor>();
    view.each([&](const auto entity, auto& bullet, auto& position, const auto& drawable, const auto& anchor) {
        if ( registry.valid(bullet.target) && registry.any_of<Health>(bullet.target) )
        {
            auto targetPosition = registry.get<Position>(bullet.target);
            auto targetDrawable = registry.get<Drawable>(bullet.target);
            auto targetAnchor = registry.get<Anchor>(bullet.target);

            auto isCollide = checkCollision(position.x - drawable.width * anchor.x, position.y - drawable.height * anchor.y,
                                            drawable.width, drawable.height,
                                            targetPosition.x - targetDrawable.width * targetAnchor.x, targetPosition.y - targetDrawable.height * targetAnchor.y,
                                            targetDrawable.width, targetDrawable.height);
            if(isCollide)
            {
                auto& targetHealth = registry.get<Health>(bullet.target);
                targetHealth.currnetHealth = std::max(0.f, targetHealth.currnetHealth - bullet.damage);
                if (targetHealth.currnetHealth < 0.0001f)
                {
                    registry.destroy(bullet.target);
                }
                registry.destroy(entity);
            }
        }
    });
}