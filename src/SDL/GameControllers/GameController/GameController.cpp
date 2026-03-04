/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./GameController.hpp"
#include <iostream>

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    GameController::GameController(int id)
        : _leftJoystick(0, 0), _rightJoystick(0, 0), _leftJoystickCallback(nullptr), _rightJoystickCallback(nullptr)
    {
        _gameController = SDL_GameControllerOpen(id);
        _oldButtonStates.resize(SDL_CONTROLLER_BUTTON_MAX, 0);
    }

    GameController::~GameController()
    {
        SDL_GameControllerClose(_gameController);
        _gameController = nullptr;
    }

    /* ----- GETTERs ----- */
    int GameController::getId() const
    {
        if (_gameController)
            return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(_gameController));
        return -1;
    }

    /* ----- FUNCTIONs ----- */
    void GameController::bindLeftJoystick(std::function<void(double, sdl::Vector<double>)> callback)
    {
        _leftJoystickCallback = callback;
    }

    void GameController::bindRightJoystick(std::function<void(double, sdl::Vector<double>)> callback)
    {
        _rightJoystickCallback = callback;
    }

    void GameController::unbindLeftJoystick()
    {
        _leftJoystickCallback = nullptr;
    }

    void GameController::unbindRightJoystick()
    {
        _rightJoystickCallback = nullptr;
    }

    void GameController::bindOnButtonPressed(SDL_GameControllerButton button, std::function<void(double)> callback)
    {
        _buttonPressed.push_back(std::make_pair(button, callback));
    }

    void GameController::bindOnButtonReleased(SDL_GameControllerButton button, std::function<void(double)> callback)
    {
        _buttonReleased.push_back(std::make_pair(button, callback));
    }

    void GameController::unbindOnButtonPressed(SDL_GameControllerButton button)
    {
        for (auto it = _buttonPressed.begin(); it != _buttonPressed.end();) {
            if (it->first == button)
                it = _buttonPressed.erase(it);
            else
                ++it;
        }
    }

    void GameController::unbindOnButtonReleased(SDL_GameControllerButton button)
    {
        for (auto it = _buttonReleased.begin(); it != _buttonReleased.end();) {
            if (it->first == button)
                it = _buttonReleased.erase(it);
            else
                ++it;
        }
    }

    void GameController::clear()
    {
        _buttonPressed.clear();
        _buttonReleased.clear();
        _leftJoystickCallback = nullptr;
        _rightJoystickCallback = nullptr;
    }

    void GameController::update(double deltaTime)
    {
        if (!_gameController) return;
        if (_leftJoystickCallback) _checkAxisCallback(deltaTime, SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY, _leftJoystickCallback);
        if (_rightJoystickCallback) _checkAxisCallback(deltaTime, SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY, _rightJoystickCallback);

        for (auto it = _buttonReleased.begin(); it != _buttonReleased.end(); ++it) {
            Uint8 currentState = SDL_GameControllerGetButton(_gameController, it->first);
            if (currentState == 0 && _oldButtonStates[it->first] == 1) it->second(deltaTime);
        }

        for (auto it = _buttonPressed.begin(); it != _buttonPressed.end(); ++it) {
            Uint8 currentState = SDL_GameControllerGetButton(_gameController, it->first);
            if (currentState == 1) it->second(deltaTime);
        }

        for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
            _oldButtonStates[i] = SDL_GameControllerGetButton(_gameController, (SDL_GameControllerButton)i);
    }

    /* ----- PRIVATE FUNCTIONs ----- */
    void GameController::_checkAxisCallback(double deltaTime, SDL_GameControllerAxis xAxis, SDL_GameControllerAxis yAxis, std::function<void(double, sdl::Vector<double>)> callback)
    {
        Sint16 x = _limitValue(xAxis);
        Sint16 y = _limitValue(yAxis);
        if (x != 0 || y != 0) callback(deltaTime, sdl::Vector<double>{(double)x / 32767.0, (double)y / 32767.0});
    }

    Sint16 GameController::_limitValue(SDL_GameControllerAxis axis)
    {
        Sint16 value = SDL_GameControllerGetAxis(_gameController, axis);
        return (std::abs(value) < _deadZone) ? 0 : value;
    }
}; // namespace sdl
