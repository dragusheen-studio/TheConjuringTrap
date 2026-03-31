/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./MentalHealth.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    MentalHealthIndicator::MentalHealthIndicator(sdl::Render &render)
        : Indicator(render, sdl::Vector<double>(16, 16), "mentalHealth.png")
    {
        sdl::Vector<int> dim = render.getDimension();
        setPosition(sdl::Vector<double>(_size + 32, dim.y - _size - 16));
    }

    /* ----- FUNCTIONs ----- */
    void MentalHealthIndicator::update(double deltaTime, const Player *player)
    {
        double staminaPct = player->getMentalHealth() / player->getMaxMentalHealth();
        Uint8 alpha = (Uint8)(staminaPct * 255);

        _icon->setOpacity(255 - alpha);
    }
}; // namespace Raycaster
