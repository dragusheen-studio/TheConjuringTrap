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
#include "Raycaster/Entity/Entity.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class InteractibleEntity : public Raycaster::Entity
    {
        public:
            InteractibleEntity(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string texturePath, double scale = 1.0);
            virtual ~InteractibleEntity() = default;

            virtual bool canInteract() const;
            virtual void interact(sdl::Render &render);
    };
}; // namespace Raycaster

/* ----- RAYCASTER_INTERACTIBLE_ENTITY_HPP_ ----- */
#endif
