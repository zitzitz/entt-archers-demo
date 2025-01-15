#include "Application.h"
#include "SDL_image.h"
#include "core/Factory.h"
#include "components/Drawable.h"
#include "components/Parabolic.h"
#include "systems/Draw.h"
#include "systems/MapGenrator.h"
#include "systems/UnitsSpawner.h"
#include "systems/AiSystem.h"
#include "systems/Movement.h"
#include "systems/CollisionResponse.h"
#include "systems/ParabolicBulletMovement.h"
#include "systems/ApplyDamage.h"
#include "systems/UpdateHealtBar.h"
#include "utils/support.h"
#include "math/MathHelper.h"

const int screen_width = 1280;
const int screen_height = 720;

void onParabolicConnect(entt::registry& registry, entt::entity entity)
{
    auto& parabolic = registry.get<Parabolic>(entity);
    parabolic.height = getRandomNumber(parabolic.heightMin, parabolic.heightMax);
}

Application::Application()
{

}

Application::~Application()
{
    SDL_DestroyRenderer( _renderer );
    _renderer = nullptr;
    SDL_DestroyWindow( _window );
    _window = nullptr;
    IMG_Quit();
    SDL_Quit();
}

bool Application::init()
{
    auto initStatus = SDL_Init( SDL_INIT_VIDEO );
    _window = SDL_CreateWindow( "Archers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN );
    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
    SDL_RenderSetScale(_renderer, 2.f, 2.f);
    _resourceManager.setRenderer(_renderer);
    SDL_SetRenderDrawColor( _renderer, 0x80, 0x90, 0xa0, 0xFF );
    auto imageInit = IMG_Init(IMG_INIT_PNG);

    initWorld();
    
    return initStatus >= 0 && _window && _renderer && (imageInit & IMG_INIT_PNG);
}

void Application::loop()
{
    bool isOpen = true;
    
    Uint32 lastTime = SDL_GetTicks();

    SDL_Event e;
    while(isOpen)
    {
        while(SDL_PollEvent( &e ) != 0)
        {
            if( e.type == SDL_QUIT )
            {
                isOpen = false;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        update(deltaTime);

        SDL_RenderClear( _renderer );
        draw();
        SDL_RenderPresent( _renderer );
        SDL_Delay(50);
    }
}

void Application::initWorld()
{
    _registry.on_construct<Drawable>().connect<&ResourceManager::onDrawbleCreate>(_resourceManager);
    _registry.on_destroy<Drawable>().connect<&ResourceManager::onDrawbleDestroy>(_resourceManager);
    _registry.on_construct<Parabolic>().connect<&onParabolicConnect>();

    makeMap(_registry);
    spawnMapTiles(_registry);
    makeUnitsGenerator(_registry, Kind::player);
    makeUnitsGenerator(_registry, Kind::enemy);
}

void Application::update(float dt)
{
    spawnUnits(_registry, dt);
    aiUpdate(_registry, dt);
    movementUnits(_registry, dt);
    parabolicBulletMovement(_registry, dt);
    collisionResponse(_registry);
    ySortProcess(_registry);
    applyDamage(_registry);
    updateHealtBar(_registry);
}

void Application::draw()
{
    drawImage( _registry, _resourceManager, _renderer );
    drawHealthBar( _registry, _resourceManager, _renderer );
}