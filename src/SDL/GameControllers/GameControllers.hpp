/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_GAME_CONTROLLER_HPP_ ----- */
#ifndef GRADE_DE_GAME_CONTROLLERS_HPP_
#define GRADE_DE_GAME_CONTROLLERS_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include "SDL/GameControllers/GameController/GameController.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class GameControllers
    {
        public:
            GameControllers() = default;
            ~GameControllers() = default;

            std::shared_ptr<GameController> getController(int id);

            void handleEvent(SDL_Event &e);
            void bindAnyControllerLeftJoystick(std::function<void(double, sdl::Vector<double>)> callback);
            void bindAnyControllerRightJoystick(std::function<void(double, sdl::Vector<double>)> callback);
            void bindAnyControllerOnButtonPressed(SDL_GameControllerButton button, std::function<void(double)> callback);
            void bindAnyControllerOnButtonReleased(SDL_GameControllerButton button, std::function<void(double)> callback);
            void bindOnControllerAdded(std::function<void(std::shared_ptr<GameController>, int)> callback);
            void unbindAnyControllerLeftJoystick();
            void unbindAnyControllerRightJoystick();
            void unbindAnyControllerOnButtonPressed(SDL_GameControllerButton button);
            void unbindAnyControllerOnButtonReleased(SDL_GameControllerButton button);
            void clear();
            void update(double deltaTime);

        private:
            std::vector<std::shared_ptr<GameController>> _controllers;
            std::vector<std::pair<SDL_GameControllerButton, std::function<void(double)>>> _buttonPressed;
            std::vector<std::pair<SDL_GameControllerButton, std::function<void(double)>>> _buttonReleased;
            std::function<void(double, sdl::Vector<double>)> _leftJoystickCallback;
            std::function<void(double, sdl::Vector<double>)> _rightJoystickCallback;
            std::function<void(std::shared_ptr<GameController>, int)> _onControllerAdded;
    };
}; // namespace sdl

/* ----- GRADE_DE_GAME_CONTROLLER_HPP_ ----- */
#endif
