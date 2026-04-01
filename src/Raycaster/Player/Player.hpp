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
#include <memory>
#include "SDL/AudioManager/AudioManager.hpp"
#include "SDL/Color/Color.hpp"
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"
#include "SDL/Primitives/Circle/Circle.hpp"
#include "./Inventory/Inventory.hpp"
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
            double getStamina() const;
            double getMaxStamina() const;
            double getMentalHealth() const;
            double getMaxMentalHealth() const;
            double getScaredFactor() const;

            void setSprint(bool sprint);

            void rotate(double deltaTime, double force);
            void rotateMouse(int offset);
            void pitch(double deltaTime, double force);
            void pitchMouse(int offset);
            void forward(double deltaTime, const Map &map);
            void strafe(double deltaTime, const Map &map);
            void update(double deltaTime);
            void usePill();
            void scare(double force = 1.0);

            std::shared_ptr<Inventory> inventory;

        private:
            /* ----- STRUCTs ----- */
            struct Sprint {
                    bool isSprinting = false;
                    double stamina = 100.0;
                    double max = 100.0;
                    double consumption = 20.0;
                    double recovery = 10.0;
                    bool isMoving = false;
            };
            struct FootstepSound {
                    double distanceCounter = 0.0;
                    double stepThreshold = 45.0;
                    std::vector<std::string> sounds = {
                        "footsteps/Foodstep Metal 1.ogg",
                        "footsteps/Foodstep Metal 2.ogg",
                        "footsteps/Foodstep Metal 3.ogg",
                        "footsteps/Foodstep Metal 4.ogg",
                        "footsteps/Foodstep Metal 5.ogg",
                    };
                    int index = 0;
            };
            struct MentalHealth {
                    double value = 100.0;
                    double max = 100.0;
                    double recovery = 1.5;
                    double idleTimer = 0.0;
                    const double idleThreshold = 4.0;
            };

            double _angle;
            double _pitch = 0.0;
            sdl::Vector<double> _delta;

            double _speed = 20;
            double _sprintMultiplier = 2.2;
            double _rotationSpeed = 2.5;
            double _mouseSensitivity = 0.003;
            int _size = 16;

            double _scaredFactor = 0.0;

            Sprint _sprint;
            FootstepSound _footstepSound;
            MentalHealth _mentalHealth;

            void _setDelta();
            sdl::Vector<double> _checkMovement(const double &moveX, const double &moveY, const Map &map);
            void _updateStamina(double deltaTime);
            void _updateMentalHealth(double deltaTime);
            void _updateFootsteps(sdl::Vector<double> oldPos);
            void _updateScaredFactor(double deltaTime);
    };
}; // namespace Raycaster

/* ----- RAYCASTER_PLAYER_HPP_ ----- */
#endif
