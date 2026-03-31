/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./LockedChest.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    LockedChest::LockedChest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position)
        : Chest(engine, render, position, "locked_chest.yaml")
    {
    }

    /* ----- INTERACTIBLE ----- */
    bool LockedChest::canInteract(Player &player) const
    {
        return (Chest::canInteract(player) && player.inventory->hasKey());
    }

    bool LockedChest::interact(sdl::Render &render, Player &player)
    {
        if (Chest::interact(render, player)) {
            player.inventory->useKey();
            return true;
        }
        return false;
    }
}; // namespace Raycaster
