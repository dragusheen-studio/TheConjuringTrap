/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_PLAYER_HPP_ ----- */
#ifndef RAYCASTER_PLAYER_HPP_
#define RAYCASTER_PLAYER_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include "SDL/Color/Color.hpp"
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"
#include "SDL/Primitives/Circle/Circle.hpp"
#include "Raycaster/Map/Map.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Player : public sdl::Movable
    {
        public:
            Player(sdl::Vector<double> position);
            ~Player() = default;

            double getAngle() const;
            double getPitch() const;
            bool hasKey() const;

            void setSprint(bool sprint);

            void gainKey();
            void useKey();
            void rotate(double deltaTime, double force);
            void rotateMouse(int offset);
            void pitch(double deltaTime, double force);
            void pitchMouse(int offset);
            void forward(double deltaTime, const Map &map);
            void strafe(double deltaTime, const Map &map);

        private:
            double _angle;
            double _pitch = 0.0;
            sdl::Vector<double> _delta;

            double _speed = 20;
            double _sprintMultiplier = 2.2;
            double _rotationSpeed = 2.5;
            double _mouseSensitivity = 0.003;
            int _size = 16;
            int _keys = 0;
            bool _sprint = false;

            void _setDelta();
            sdl::Vector<double> _checkMovement(const double &moveX, const double &moveY, const Map &map);
    };
}; // namespace Raycaster

/* ----- RAYCASTER_PLAYER_HPP_ ----- */
#endif
