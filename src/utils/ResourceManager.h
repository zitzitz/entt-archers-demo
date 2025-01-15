#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <unordered_map>
#include "SDL.h"
#include "entt/entt.hpp"

class ResourceManager {
public:
    void setRenderer(SDL_Renderer* renderer);
    SDL_Texture* getTexture(const std::string& texturePath);
    void decreaseTexture(const std::string& texturePath);
    void onDrawbleCreate(entt::registry& registry, entt::entity entity);
    void onDrawbleDestroy(entt::registry& registry, entt::entity entity);
protected:
    SDL_Texture* loadTexture(std::string path);
private:
    SDL_Renderer* _renderer;
    std::unordered_map<std::string, std::pair<int, SDL_Texture*>> _textures;
};

#endif