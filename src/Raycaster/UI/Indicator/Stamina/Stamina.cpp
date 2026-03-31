/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Stamina.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    StaminaIndicator::StaminaIndicator(sdl::Render &render)
        : Indicator(render, sdl::Vector<double>(16, 16), "stamina.png")
    {
        setY(render.getDimension().y - _size - 16);
    }

    /* ----- FUNCTIONs ----- */
    void StaminaIndicator::update(double deltaTime, const Player *player)
    {
        double staminaPct = player->getStamina() / player->getMaxStamina();
        Uint8 alpha = (Uint8)(64 + (staminaPct * (255 - 64)));
        Uint8 gbValue = (Uint8)(staminaPct * 255);
        sdl::Color color(255, gbValue, gbValue);

        _icon->setColor(color);
        _icon->setOpacity(alpha);
    }
}; // namespace Raycaster
