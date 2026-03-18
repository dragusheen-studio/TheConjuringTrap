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

/* ----- CLASS ----- */
namespace Raycaster
{
    class Interactible
    {
        public:
            virtual ~Interactible() = default;

            virtual bool canInteract() const = 0;
            virtual void interact(sdl::Render &render) = 0;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_INTERACTIBLE_ENTITY_HPP_ ----- */
#endif
