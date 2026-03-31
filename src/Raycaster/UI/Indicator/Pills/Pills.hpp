/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_PILLS_INDICATOR_HPP_ ----- */
#ifndef RAYCASTER_PILLS_INDICATOR_HPP_
#define RAYCASTER_PILLS_INDICATOR_HPP_

/* ----- INCLUDEs ----- */
#include "Raycaster/UI/Indicator/Indicator.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class PillsIndicator : public Raycaster::Indicator
    {
        public:
            PillsIndicator(sdl::Render &render);
            ~PillsIndicator() = default;

            void update(double deltaTime, const Player *player) override;
    };
}; // namespace Raycaster

#endif
