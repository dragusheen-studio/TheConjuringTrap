/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_STAMINA_INDICATOR_HPP_ ----- */
#ifndef RAYCASTER_STAMINA_INDICATOR_HPP_
#define RAYCASTER_STAMINA_INDICATOR_HPP_

/* ----- INCLUDEs ----- */
#include "Raycaster/UI/Indicator/Indicator.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class StaminaIndicator : public Raycaster::Indicator
    {
        public:
            StaminaIndicator(sdl::Render &render);
            ~StaminaIndicator() = default;

            void update(double deltaTime, const Player *player) override;
    };
}; // namespace Raycaster

#endif
