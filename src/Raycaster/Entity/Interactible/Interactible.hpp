/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_INTERACTIBLEENTITY_HPP_ ----- */
#ifndef RAYCASTER_INTERACTIBLE_ENTITY_HPP_
#define RAYCASTER_INTERACTIBLE_ENTITY_HPP_

/* ----- INCLUDEs ----- */
#include "SDL/Render/Render.hpp"
#include "Raycaster/Player/Player.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Engine;

    class Interactible
    {
        public:
            virtual ~Interactible() = default;

            virtual bool canInteract(Player &player) const = 0;
            virtual bool interact(sdl::Render &render, Player &player, Engine &engine) = 0;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_INTERACTIBLE_ENTITY_HPP_ ----- */
#endif
