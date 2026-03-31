/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./HUD.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    HUD::HUD(sdl::Render &render)
    {
        _indicators.push_back(std::make_unique<StaminaIndicator>(render));
    }

    /* ----- DRAWABLE ----- */
    void HUD::draw(sdl::Render &render)
    {
        for (auto &indicator : _indicators)
            indicator->draw(render);
    }

    /* ----- FUNCTIONs ----- */
    void HUD::update(double deltaTime, const Player *player)
    {
        for (auto &indicator : _indicators)
            indicator->update(deltaTime, player);
    }
}; // namespace Raycaster
