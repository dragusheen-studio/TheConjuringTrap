/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_GAME_CONTROLLER_HPP_ ----- */
#ifndef GRADE_DE_GAME_CONTROLLER_HPP_
#define GRADE_DE_GAME_CONTROLLER_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <functional>
#include <utility>
#include <vector>
#include "SDL/Vector/Vector.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class GameController
    {
        public:
            GameController(int id);
            ~GameController();

            int getId() const;

            void bindLeftJoystick(std::function<void(double, sdl::Vector<double>)> callback);
            void bindRightJoystick(std::function<void(double, sdl::Vector<double>)> callback);
            void bindOnButtonPressed(SDL_GameControllerButton button, std::function<void(double)> callback);
            void bindOnButtonReleased(SDL_GameControllerButton button, std::function<void(double)> callback);
            void unbindLeftJoystick();
            void unbindRightJoystick();
            void unbindOnButtonPressed(SDL_GameControllerButton button);
            void unbindOnButtonReleased(SDL_GameControllerButton button);
            void clear();
            void update(double deltaTime);

        private:
            sdl::Vector<double> _leftJoystick;
            sdl::Vector<double> _rightJoystick;
            std::function<void(double, sdl::Vector<double>)> _leftJoystickCallback;
            std::function<void(double, sdl::Vector<double>)> _rightJoystickCallback;
            SDL_GameController *_gameController;
            const int _deadZone = 8000;

            std::vector<Uint8> _oldButtonStates;
            std::vector<std::pair<SDL_GameControllerButton, std::function<void(double)>>> _buttonPressed;
            std::vector<std::pair<SDL_GameControllerButton, std::function<void(double)>>> _buttonReleased;

            void _checkAxisCallback(double deltaTime, SDL_GameControllerAxis xAxis, SDL_GameControllerAxis yAxis, std::function<void(double, sdl::Vector<double>)> callback);
            Sint16 _limitValue(SDL_GameControllerAxis axis);
    };
}; // namespace sdl

/* ----- GRADE_DE_GAME_CONTROLLER_HPP_ ----- */
#endif
