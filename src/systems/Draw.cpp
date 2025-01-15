#include "Draw.h"
#include "core/Factory.h"
#include "components/Position.h"
#include "components/Drawable.h"
#include "components/MoveFlip.h"
#include "components/MoveRotation.h"
#include "components/Map.h"
#include "components/YSort.h"
#include "components/HealthBar.h"
#include "utils/ResourceManager.h"
#include "SDL.h"
#include "math/MathHelper.h"

const int screenOffsetX = (1280 / 2) / 2 - 32 * 20 / 2 + 32 / 2;
const int screenOffsetY = (720 / 2) / 2;

void ySortProcess(entt::registry &registry)
{
    const auto mapView = registry.view<Map>();
    auto mapEntity = mapView.front();
    auto& map = registry.get<Map>(mapEntity);
    const auto view = registry.view<Position, YSort>();
    view.each([&](const auto entity, auto& position) {
        position.z = 0.001 * position.y + map.objectslayer;
    });
}

void drawImage(entt::registry &registry, ResourceManager& resourceManager, SDL_Renderer* renderer)
{
    registry.sort<Position>([](const auto &lhs, const auto &rhs) {
    return lhs.z < rhs.z;
    });
    auto view = registry.view<Drawable, Position, Anchor>();
    view.use<Position>();
    view.each([&](const auto entity, const auto& drawble, const auto& position, const auto& anchor) {
        auto texture = resourceManager.getTexture(drawble.tile);

        int width;
        int height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        SDL_Rect srcRect{0, 0, width, height};

        SDL_Rect dstRect{static_cast<int>(position.x + screenOffsetX - width * anchor.x), static_cast<int>(position.y + screenOffsetY - height * anchor.y), width, height};

        double angle = 0.;
        if(registry.any_of<MoveRotation>(entity))
        {
            auto& moveDirection = registry.get<MoveRotation>(entity);
            angle = radToDegress(moveDirection.angle + moveDirection.additionalAngle);
        }

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (registry.any_of<MoveFlip>(entity))
        {
            flip = registry.get<MoveFlip>(entity).isFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        }
        SDL_Point center{static_cast<int>(width * anchor.x), static_cast<int>(height * anchor.y)};
        SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, &center, flip);
    });
}

void drawHealthBar(entt::registry &registry, ResourceManager& resourceManager, SDL_Renderer* renderer)
{
    const auto view = registry.view<HealthBar, Position>();
    view.each([&](const auto entity, const auto& healthBar, const auto& position) {
        if (registry.valid(healthBar.unit))
        {
            auto backTexture = resourceManager.getTexture(healthBar.back);
            auto frontTexture = resourceManager.getTexture(healthBar.front);

            int width;
            int height;
            SDL_QueryTexture(backTexture, nullptr, nullptr, &width, &height);
            SDL_Rect srcRect{0, 0, width, height};
            SDL_Rect dstRect{static_cast<int>(position.x + screenOffsetX), static_cast<int>(position.y + screenOffsetY), width, height};
            SDL_RenderCopy(renderer, backTexture, &srcRect, &dstRect);
            dstRect.w = static_cast<int>(dstRect.w * healthBar.progress);
            SDL_RenderCopy(renderer, frontTexture, &srcRect, &dstRect);
        }
    });
}