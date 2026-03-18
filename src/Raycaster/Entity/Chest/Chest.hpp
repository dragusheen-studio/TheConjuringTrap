/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_CHEST_HPP_ ----- */
#ifndef RAYCASTER_CHEST_HPP_
#define RAYCASTER_CHEST_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "Raycaster/Entity/Entity.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Chest : public Raycaster::Entity
    {
        public:
            Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position);
            ~Chest() = default;

            void compute(const Player &player, const std::vector<double> &zBuffer) override;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_CHEST_HPP_ ----- */
#endif
