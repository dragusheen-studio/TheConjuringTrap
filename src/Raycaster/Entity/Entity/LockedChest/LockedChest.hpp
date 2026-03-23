/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_LOCKED_CHEST_HPP_ ----- */
#ifndef RAYCASTER_LOCKED_CHEST_HPP_
#define RAYCASTER_LOCKED_CHEST_HPP_

/* ----- INCLUDEs ----- */
#include "Raycaster/Entity/Entity.hpp"
#include "Raycaster/Entity/Interactible/Interactible.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class LockedChest : public Entity, public Interactible
    {
        public:
            LockedChest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position);
            ~LockedChest() = default;

            /* ----- OVERRIDE INTERACTIBLE ----- */
            bool canInteract(Player &player) const override;
            void interact(sdl::Render &render, Player &player) override;
            /* ----- END INTERACTIBLE ----- */

        private:
            bool _isOpen = false;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_LOCKED_CHEST_HPP_ ----- */
#endif
