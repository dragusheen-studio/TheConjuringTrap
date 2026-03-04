/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_ENGINE_HPP_ ----- */
#ifndef RAYCASTER_ENGINE_HPP_
#define RAYCASTER_ENGINE_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <cmath>
#include <limits>
#include "SDL/Keyboard/Keyboard.hpp"
#include "SDL/Render/Render.hpp"
#include "Raycaster/Map/Map.hpp"
#include "Raycaster/Minimap/Minimap.hpp"
#include "Raycaster/Player/Player.hpp"
#include "Raycaster/Ray/Ray.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Engine
    {
        public:
            Engine(double fov = 60.0, int numRays = 320);
            ~Engine();

            void run();

        private:
            void handleInput(double deltaTime);
            void compute();
            void render();

            bool _quit;

            sdl::Render _render;
            Map _map;
            Minimap _minimap;
            Player _player;
            sdl::Keyboard _keyboard;

            SDL_GameController *_gamepad;
            const int JOYSTICK_DEAD_ZONE = 8000;

            struct RayData {
                    double offset;
                    Ray ray;
            };

            int _numRays;
            double _fov;
            std::vector<RayData> _rays;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_ENGINE_HPP_ ----- */
#endif
