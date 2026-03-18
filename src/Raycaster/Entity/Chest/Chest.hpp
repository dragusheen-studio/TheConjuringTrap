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
#include "Raycaster/Entity/Interactible/InteractibleEntity.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Chest : public InteractibleEntity
    {
        public:
            Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position);
            ~Chest() = default;

            void interact(sdl::Render &render) override;

        private:
            bool _isOpen = false;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_CHEST_HPP_ ----- */
#endif
