/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Engine.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Engine::Engine(double fov, int numRays)
        : _quit(false),
          _render(sdl::Vector<int>(960, 540), "Horror Raycaster - 3D", sdl::Color::BLACK, sdl::Vector<int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)),
          _map(64, "./assets/config/map.txt", _render),
          _minimap(sdl::Vector<double>(16, 16), 128, 0.3),
          _player(sdl::Vector<double>(0, 0)),
          _fov(fov),
          _numRays(numRays)
    {
        _player.setPosition(_map.getPlayerStart());

        double fovRadians = _fov * (M_PI / 180.0);
        double halfFov = fovRadians / 2.0;
        double step = fovRadians / (_numRays - 1);

        double rayWidth3D = 960.0 / _numRays;

        for (int i = 0; i < _numRays; i++)
            _rays.push_back({-halfFov + (i * step), Ray(0, sdl::Vector<double>(0, 0), 5, rayWidth3D, rayWidth3D * i, _render.getDimension())});

        _render.setUseMouse(true);
    }

    /* ----- FUNCTIONs ----- */
    void Engine::run()
    {
        Uint32 lastTime = SDL_GetTicks();
        double deltaTime = 0;

        while (!_quit) {
            Uint32 currentTime = SDL_GetTicks();
            deltaTime = (currentTime - lastTime) / 1000.0;
            lastTime = currentTime;

            handleInput(deltaTime);
            compute();
            render();
        }
    }

    void Engine::handleInput(double deltaTime)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) _quit = true;
            if (e.type == SDL_MOUSEMOTION) {
                _player.rotateMouse(e.motion.xrel);
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE]) _quit = true;

        if (state[SDL_SCANCODE_W]) _player.forward(deltaTime, _map);
        if (state[SDL_SCANCODE_S]) _player.forward(-deltaTime, _map);

        if (state[SDL_SCANCODE_A]) _player.strafe(-deltaTime, _map);
        if (state[SDL_SCANCODE_D]) _player.strafe(deltaTime, _map);

        if (state[SDL_SCANCODE_LEFT]) _player.rotate(deltaTime, -1);
        if (state[SDL_SCANCODE_RIGHT]) _player.rotate(deltaTime, 1);
    }

    void Engine::compute()
    {
        _minimap.compute(_map, _player);
        double playerAngle = _player.getAngle();
        sdl::Vector<double> pPos = _player.getPosition();

        for (Raycaster::Engine::RayData &data : _rays) {
            data.ray.setAngle(playerAngle + data.offset);
            data.ray.setPosition(pPos);
            data.ray.compute(_map, _player);
        }
    }

    void Engine::render()
    {
        _render.clear();

        for (Raycaster::Engine::RayData &data : _rays)
            data.ray.draw(_render);
        _minimap.draw(_render);

        _render.present();
    }
}; // namespace Raycaster
