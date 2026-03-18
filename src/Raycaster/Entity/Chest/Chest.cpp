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
        : InteractibleEntity(engine, render, position, "chest/Metal Chest - Closed.png", 0.5)
    {
    }

    /* ----- FUNCTIONs ----- */
    void Chest::interact(sdl::Render &render)
    {
        if (_isOpen) return;

        _isOpen = true;
        _texture = sdl::TextureManager::get().get(render, "chest/Metal Chest - Open.png");
    }
}; // namespace Raycaster
