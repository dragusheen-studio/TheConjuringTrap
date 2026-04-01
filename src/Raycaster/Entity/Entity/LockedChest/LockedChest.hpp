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
#include "Raycaster/Entity/Entity/Chest/Chest.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class LockedChest : public Chest
    {
        public:
            LockedChest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position);
            ~LockedChest() = default;

            /* ----- OVERRIDE INTERACTIBLE ----- */
            bool canInteract(Player &player) const override;
            bool interact(sdl::Render &render, Player &player, Engine &engine) override;
            /* ----- END INTERACTIBLE ----- */
    };
}; // namespace Raycaster

/* ----- RAYCASTER_LOCKED_CHEST_HPP_ ----- */
#endif
