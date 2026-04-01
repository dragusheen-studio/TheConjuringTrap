/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Pills.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    PillsIndicator::PillsIndicator(sdl::Render &render)
        : Indicator(render, sdl::Vector<double>(16, 16), "pills.png")
    {
        sdl::Vector<int> dim = render.getDimension();
        setPosition(sdl::Vector<double>(dim.x - (_size + 16) * 2, dim.y - _size - 16));
    }

    /* ----- FUNCTIONs ----- */
    void PillsIndicator::update(double deltaTime, const Player *player)
    {
        _icon->setOpacity(player->inventory->hasPill() ? 255 : 64);
    }
}; // namespace Raycaster
