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
        : Entity(engine, render, position, "assets/config/entity/chest/locked_chest.yaml", 0.5)
    {
    }

    /* ----- INTERACTIBLE ----- */
    bool LockedChest::canInteract(Player &player) const
    {
        return (!_isOpen && isTargeted() && player.hasKey());
    }

    void LockedChest::interact(sdl::Render &render, Player &player)
    {
        if (_isOpen) return;

        _isOpen = true;
        _animator->play("opening");
        player.useKey();
    }
}; // namespace Raycaster
