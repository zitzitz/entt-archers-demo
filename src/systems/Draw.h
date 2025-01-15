#ifndef _DRAW_IMAGE_SYSTEM_H_
#define _DRAW_IMAGE_SYSTEM_H_

#include "entt/entt.hpp"

class ResourceManager;
class SDL_Renderer;

void ySortProcess(entt::registry &registry);
void drawImage(entt::registry &registry, ResourceManager& resourceManager, SDL_Renderer* window);
void drawHealthBar(entt::registry &registry, ResourceManager& resourceManager, SDL_Renderer* renderer);

#endif