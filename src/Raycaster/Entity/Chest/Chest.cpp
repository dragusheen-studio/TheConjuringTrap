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
    Chest::Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position)
        : InteractibleEntity(engine, render, position, "assets/config/entity/chest/chest.yaml", 0.5)
    {
    }

    /* ----- FUNCTIONs ----- */
    void Chest::interact(sdl::Render &render)
    {
        if (_isOpen) return;

        _isOpen = true;
        _animator->play("opening");
    }
}; // namespace Raycaster
