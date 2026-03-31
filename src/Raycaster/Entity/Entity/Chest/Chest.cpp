/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Chest.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Chest::Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string config)
        : Entity(engine, render, position, "assets/config/entity/chest/" + config, 0.5)
    {
    }

    /* ----- INTERACTIBLE ----- */
    bool Chest::canInteract(Player &player) const
    {
        return (!_isOpen && isTargeted());
    }

    bool Chest::interact(sdl::Render &render, Player &player)
    {
        if (_isOpen) return false;

        _isOpen = true;
        _animator->play("opening");
        player.inventory->gainPill();
        return true;
    }
}; // namespace Raycaster
