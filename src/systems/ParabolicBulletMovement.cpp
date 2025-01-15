#include "ParabolicBulletMovement.h"
#include "components/Position.h"
#include "components/Parabolic.h"
#include "components/MoveRotation.h"
#include "math/Vector2.h"

float parabolicYOffest(float t)
{
    return -(2 * t - 1)*(2 * t - 1) + 1;
}

void parabolicBulletMovement(entt::registry &registry, float dt)
{
    const auto view = registry.view<Position, Parabolic, MoveRotation>();

    view.each([&](const auto entity, auto& position, auto& parabolic, auto& moveRotation) {
        auto startPosotion = Vector2(parabolic.startPositionX, parabolic.startPositionY);
        auto targetPosition = Vector2(parabolic.targetPositionX, parabolic.targetPositionY);
        auto duration = (targetPosition - startPosotion).length() / parabolic.speed;

        parabolic.timer += dt;
        auto t = parabolic.timer / duration;
        if (t >= 1.2f)
        {
            registry.destroy(entity);
        }
        else
        {
            t = std::min(t, 1.f);

            auto newPos = startPosotion + (targetPosition - startPosotion) * t;
            newPos.y = newPos.y - parabolicYOffest(t) * parabolic.height;

            auto oldPos = Vector2(position);
            auto direction = (newPos - oldPos).normalized();
            moveRotation.angle = std::atan2(direction.y, direction.x);

            position.x = newPos.x;
            position.y = newPos.y;
        }
    });
}