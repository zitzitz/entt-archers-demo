#include "UpdateHealtBar.h"
#include "components/Health.h"
#include "components/HealthBar.h"
#include "components/Position.h"

void updateHealtBar(entt::registry &registry)
{
    const auto view = registry.view<HealthBar, Position>();

    view.each([&](const auto entity, auto& healthBar, auto& position) {
        if(registry.valid(healthBar.unit))
        {
            auto& unitPosition = registry.get<Position>(healthBar.unit);
            auto& unitHealth = registry.get<Health>(healthBar.unit);
            position.x = unitPosition.x + healthBar.offsetX;
            position.y = unitPosition.y + healthBar.offsetY;

            healthBar.progress = unitHealth.currnetHealth / unitHealth.fullHealth;
        }
        else
        {
            registry.destroy(entity);
        }
    });
}