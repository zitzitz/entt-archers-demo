#include "ResourceManager.h"
#include "components/Drawable.h"
#include "SDL_image.h"

void ResourceManager::setRenderer(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

SDL_Texture* ResourceManager::getTexture(const std::string& texturePath)
{
    if (_textures.count(texturePath) > 0)
    {
        _textures.at(texturePath).first++;
    }
    else
    {
        SDL_Texture* texture = loadTexture(texturePath);
        _textures.insert({texturePath, {1, texture}});
    }

    return _textures.at(texturePath).second;
}

void ResourceManager::decreaseTexture(const std::string& texturePath)
{
    if (_textures.count(texturePath) > 0)
    {
        auto& texture = _textures.at(texturePath);
        texture.first--;
        if(texture.first < 1)
        {
            SDL_DestroyTexture(texture.second);
            _textures.erase(texturePath);
        }
    }
}

SDL_Texture* ResourceManager::loadTexture(std::string path)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
        if( newTexture == nullptr )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void ResourceManager::onDrawbleCreate(entt::registry& registry, entt::entity entity)
{
    auto& drawable = registry.get<Drawable>(entity);
    SDL_QueryTexture(getTexture(drawable.tile), nullptr, nullptr, &drawable.width, &drawable.height);
}

void ResourceManager::onDrawbleDestroy(entt::registry& registry, entt::entity entity) {
    const auto& drawable = registry.get<Drawable>(entity);
    decreaseTexture(drawable.tile);
}