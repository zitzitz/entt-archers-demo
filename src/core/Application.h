#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "entt/entt.hpp"
#include "SDL.h"
#include "utils/ResourceManager.h"

class Application
{
public:
    Application();
    ~Application();
    bool init();
    void loop();
    entt::registry& getRegystry() { return _registry; }
protected:
    void initWorld();
    void update(float dt);
    void draw();
private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    entt::registry _registry;
    ResourceManager _resourceManager;
};

#endif