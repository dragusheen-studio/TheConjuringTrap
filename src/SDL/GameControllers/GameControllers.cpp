/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./GameControllers.hpp"
#include <iostream>

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */

    /* ----- FUNCTIONs ----- */
    void GameControllers::handleEvent(SDL_Event &e)
    {
        if (e.type == SDL_CONTROLLERDEVICEADDED) {
            std::shared_ptr<GameController> controller = std::make_shared<GameController>(e.cdevice.which);

            if (_leftJoystickCallback) controller->bindLeftJoystick(_leftJoystickCallback);
            if (_rightJoystickCallback) controller->bindRightJoystick(_rightJoystickCallback);
            for (auto &pair : _buttonPressed)
                controller->bindOnButtonPressed(pair.first, pair.second);
            for (auto &pair : _buttonReleased)
                controller->bindOnButtonReleased(pair.first, pair.second);
            if (_onControllerAdded) _onControllerAdded(controller, e.cdevice.which);
            _controllers.push_back(controller);
        }

        if (e.type == SDL_CONTROLLERDEVICEREMOVED) {
            for (auto it = _controllers.begin(); it != _controllers.end();) {
                if ((*it)->getId() == e.cdevice.which)
                    it = _controllers.erase(it);
                else
                    ++it;
            }
        }
    }

    void GameControllers::bindAnyControllerLeftJoystick(std::function<void(double, sdl::Vector<double>)> callback)
    {
        _leftJoystickCallback = callback;
        for (auto &controller : _controllers)
            controller->bindLeftJoystick(callback);
    }

    void GameControllers::bindAnyControllerRightJoystick(std::function<void(double, sdl::Vector<double>)> callback)
    {
        _rightJoystickCallback = callback;
        for (auto &controller : _controllers)
            controller->bindRightJoystick(callback);
    }

    void GameControllers::bindAnyControllerOnButtonPressed(SDL_GameControllerButton button, std::function<void(double)> callback)
    {
        _buttonPressed.push_back(std::make_pair(button, callback));
        for (auto &controller : _controllers)
            controller->bindOnButtonPressed(button, callback);
    }

    void GameControllers::bindAnyControllerOnButtonReleased(SDL_GameControllerButton button, std::function<void(double)> callback)
    {
        _buttonReleased.push_back(std::make_pair(button, callback));
        for (auto &controller : _controllers)
            controller->bindOnButtonReleased(button, callback);
    }

    void GameControllers::bindOnControllerAdded(std::function<void(std::shared_ptr<GameController>, int)> callback)
    {
        _onControllerAdded = callback;
    }

    void GameControllers::unbindAnyControllerLeftJoystick()
    {
        _leftJoystickCallback = nullptr;
        for (auto &controller : _controllers)
            controller->unbindLeftJoystick();
    }

    void GameControllers::unbindAnyControllerRightJoystick()
    {
        _rightJoystickCallback = nullptr;
        for (auto &controller : _controllers)
            controller->unbindRightJoystick();
    }

    void GameControllers::unbindAnyControllerOnButtonPressed(SDL_GameControllerButton button)
    {
        for (auto it = _buttonPressed.begin(); it != _buttonPressed.end();) {
            if (it->first == button)
                it = _buttonPressed.erase(it);
            else
                ++it;
            for (auto &controller : _controllers)
                controller->unbindOnButtonPressed(button);
        }
    }

    void GameControllers::unbindAnyControllerOnButtonReleased(SDL_GameControllerButton button)
    {
        for (auto it = _buttonReleased.begin(); it != _buttonReleased.end();) {
            if (it->first == button)
                it = _buttonReleased.erase(it);
            else
                ++it;
            for (auto &controller : _controllers)
                controller->unbindOnButtonReleased(button);
        }
    }

    void GameControllers::clear()
    {
        _leftJoystickCallback = nullptr;
        _rightJoystickCallback = nullptr;
        _buttonPressed.clear();
        _buttonReleased.clear();

        for (auto &controller : _controllers)
            controller->clear();
    }

    void GameControllers::update(double deltaTime)
    {
        for (auto &controller : _controllers)
            controller->update(deltaTime);
    }
}; // namespace sdl
