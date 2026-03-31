/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_MENTAL_HEALTH_INDICATOR_HPP_ ----- */
#ifndef RAYCASTER_MENTAL_HEALTH_INDICATOR_HPP_
#define RAYCASTER_MENTAL_HEALTH_INDICATOR_HPP_

/* ----- INCLUDEs ----- */
#include "Raycaster/UI/Indicator/Indicator.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class MentalHealthIndicator : public Raycaster::Indicator
    {
        public:
            MentalHealthIndicator(sdl::Render &render);
            ~MentalHealthIndicator() = default;

            void update(double deltaTime, const Player *player) override;
    };
}; // namespace Raycaster

#endif
