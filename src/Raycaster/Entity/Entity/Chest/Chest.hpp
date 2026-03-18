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
#include "Raycaster/Entity/Entity.hpp"
#include "Raycaster/Entity/Interactible/Interactible.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Chest : public Entity, public Interactible
    {
        public:
            Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position);
            ~Chest() = default;

            bool canInteract() const override;
            void interact(sdl::Render &render) override;

        private:
            bool _isOpen = false;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_CHEST_HPP_ ----- */
#endif
