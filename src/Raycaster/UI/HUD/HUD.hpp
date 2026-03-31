/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_HUD_HPP_ ----- */
#ifndef RAYCASTER_HUD_HPP_
#define RAYCASTER_HUD_HPP_

/* ----- INCLUDEs ----- */
#include <memory>
#include <vector>
#include "Raycaster/Player/Player.hpp"
#include "Raycaster/UI/Indicator/Indicator.hpp"
#include "Raycaster/UI/Indicator/Stamina/Stamina.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class HUD : public sdl::Drawable
    {
        public:
            HUD(sdl::Render &render);
            ~HUD() = default;

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(sdl::Render &render) override;
            /* ----- END DRAWABLE ----- */

            void update(double deltaTime, const Player *player);

        private:
            std::vector<std::unique_ptr<Indicator>> _indicators;
    };
}; // namespace Raycaster

#endif
