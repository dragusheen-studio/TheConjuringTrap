/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_KEYS_INDICATOR_HPP_ ----- */
#ifndef RAYCASTER_KEYS_INDICATOR_HPP_
#define RAYCASTER_KEYS_INDICATOR_HPP_

/* ----- INCLUDEs ----- */
#include "Raycaster/UI/Indicator/Indicator.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class KeysIndicator : public Raycaster::Indicator
    {
        public:
            KeysIndicator(sdl::Render &render);
            ~KeysIndicator() = default;

            void update(double deltaTime, const Player *player) override;
    };
}; // namespace Raycaster

#endif
