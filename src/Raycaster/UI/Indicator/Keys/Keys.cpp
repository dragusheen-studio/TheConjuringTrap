/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Keys.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    KeysIndicator::KeysIndicator(sdl::Render &render)
        : Indicator(render, sdl::Vector<double>(16, 16), "keys.png")
    {
        sdl::Vector<int> dim = render.getDimension();
        setPosition(sdl::Vector<double>(dim.x - _size - 16, dim.y - _size - 16));
    }

    /* ----- FUNCTIONs ----- */
    void KeysIndicator::update(double deltaTime, const Player *player)
    {
        _icon->setOpacity(player->inventory->hasKey() ? 255 : 64);
    }
}; // namespace Raycaster
