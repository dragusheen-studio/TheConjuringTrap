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
          _map(64, "./assets/config/map/map.txt", _render),
          _minimap(sdl::Vector<double>(16, 16), 128, 0.3),
          _player(sdl::Vector<double>(0, 0)),
          _fov(fov),
          _numRays(numRays),
          _keyboard()
    {
        _player.setPosition(_map.getPlayerStart());

        double fovRadians = _fov * (M_PI / 180.0);
        double halfFov = fovRadians / 2.0;
        double step = fovRadians / (_numRays - 1);

        double rayWidth3D = 960.0 / _numRays;

        for (int i = 0; i < _numRays; i++)
            _rays.push_back({-halfFov + (i * step), Ray(0, sdl::Vector<double>(0, 0), _dov, rayWidth3D, rayWidth3D * i, _render.getDimension())});
        _zBuffer.resize(_numRays, 0.0);

        const std::vector<Map::EntitySpawn> &spawns = _map.getEntitySpawns();
        for (const auto &spawn : spawns) {
            if (spawn.type == CellType::CHEST)
                _entities.push_back(std::make_unique<Chest>(*this, _render, spawn.position));
            else if (spawn.type == CellType::LOCKED_CHEST)
                _entities.push_back(std::make_unique<LockedChest>(*this, _render, spawn.position));
        }
        _promptUI = std::make_unique<PromptUI>(_render, "assets/config/ui/interact/interact.yaml");

        _render.setUseMouse(true);

        _keyboard.bindOnReleased(SDL_SCANCODE_ESCAPE, [&](double deltaTime) { _quit = true; });
        _keyboard.bindOnPressed(SDL_SCANCODE_W, [&](double deltaTime) { _player.forward(deltaTime, _map); });
        _keyboard.bindOnPressed(SDL_SCANCODE_S, [&](double deltaTime) { _player.forward(-deltaTime, _map); });
        _keyboard.bindOnPressed(SDL_SCANCODE_A, [&](double deltaTime) { _player.strafe(-deltaTime, _map); });
        _keyboard.bindOnPressed(SDL_SCANCODE_D, [&](double deltaTime) { _player.strafe(deltaTime, _map); });
        _keyboard.bindOnPressed(SDL_SCANCODE_LEFT, [&](double deltaTime) { _player.rotate(deltaTime, -1); });
        _keyboard.bindOnPressed(SDL_SCANCODE_RIGHT, [&](double deltaTime) { _player.rotate(deltaTime, 1); });
        _keyboard.bindOnReleased(SDL_SCANCODE_E, [&](double deltaTime) {
            if (_currentTarget) {
                Interactible *interactObj = dynamic_cast<Interactible *>(_currentTarget);
                if (interactObj) interactObj->interact(_render, _player);
            }
        });

        _gameController.bindAnyControllerLeftJoystick([&](double deltaTime, sdl::Vector<double> values) {
            _player.forward(-deltaTime * values.y, _map);
            _player.strafe(deltaTime * values.x, _map);
        });
        _gameController.bindAnyControllerRightJoystick([&](double deltaTime, sdl::Vector<double> values) {
            _player.rotate(deltaTime, values.x);
            _player.pitchMouse(values.y * 15.0);
        });
        _gameController.bindAnyControllerOnButtonReleased(SDL_CONTROLLER_BUTTON_START, [&](double deltaTime) { _quit = true; });
        _gameController.bindAnyControllerOnButtonReleased(SDL_CONTROLLER_BUTTON_A, [&](double deltaTime) {
            if (_currentTarget) {
                Interactible *interactObj = dynamic_cast<Interactible *>(_currentTarget);
                if (interactObj) interactObj->interact(_render, _player);
            }
        });
    }

    /* ----- GETTERS ----- */
    const Map &Engine::getMap() const
    {
        return _map;
    }

    double Engine::getFieldOfView() const
    {
        return _fov;
    }

    double Engine::getDepthOfView() const
    {
        return _dov;
    }

    int Engine::getNumRays() const
    {
        return _numRays;
    }

    const sdl::Render &Engine::getRender() const
    {
        return _render;
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
            update(deltaTime);
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
                _player.pitchMouse(e.motion.yrel);
            }
            _gameController.handleEvent(e);
        }

        _keyboard.update(deltaTime);
        _gameController.update(deltaTime);
    }

    void Engine::compute()
    {
        _minimap.compute(_map, _player, _entities);

        double playerAngle = _player.getAngle();
        sdl::Vector<double> pPos = _player.getPosition();

        for (int i = 0; i < _numRays; i++) {
            _rays[i].ray.setAngle(playerAngle + _rays[i].offset);
            _rays[i].ray.setPosition(pPos);
            _rays[i].ray.setPitch(_player.getPitch());
            _rays[i].ray.compute(_map, _player);

            _zBuffer[i] = _rays[i].ray.getDistance();
        }

        for (auto &entity : _entities)
            entity->compute(_player, _zBuffer);
    }

    void Engine::update(double deltaTime)
    {
        for (auto &entity : _entities)
            entity->update(deltaTime);

        std::sort(_entities.begin(), _entities.end(), [](const std::unique_ptr<Entity> &a, const std::unique_ptr<Entity> &b) {
            return a->getDistance() > b->getDistance();
        });

        _currentTarget = nullptr;
        for (auto &entity : _entities) {
            Interactible *interactObj = dynamic_cast<Interactible *>(entity.get());
            if (interactObj != nullptr && interactObj->canInteract(_player)) _currentTarget = entity.get();
        }
        if (_promptUI && _currentTarget) {
            _promptUI->update(deltaTime, _currentTarget);
            _currentTarget->setSelected(true);
        }
    }

    void Engine::render()
    {
        _render.clear();

        for (Raycaster::Engine::RayData &data : _rays)
            data.ray.draw(_render);
        for (auto &entity : _entities)
            entity->draw(_render);
        _minimap.draw(_render);

        if (_currentTarget && _promptUI) _promptUI->draw(_render);

        _render.present();
    }
}; // namespace Raycaster
