/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_INDICATOR_HPP_ ----- */
#ifndef RAYCASTER_INDICATOR_HPP_
#define RAYCASTER_INDICATOR_HPP_

/* ----- INCLUDEs ----- */
#include <memory>
#include <string>
#include "SDL/Color/Color.hpp"
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"
#include "SDL/Render/Render.hpp"
#include "SDL/Texture/Texture.hpp"
#include "Raycaster/Player/Player.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Indicator : public sdl::Drawable, public sdl::Movable
    {
        public:
            Indicator(sdl::Render &render, sdl::Vector<double> position, const std::string &iconPath);
            ~Indicator() = default;

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(sdl::Render &render) override;
            /* ----- END DRAWABLE ----- */

            /* ----- OVERRIDE MOVABLE ----- */
            void onTransformChanged() override;
            /* ----- END MOVABLE ----- */

            virtual void update(double deltaTime, const Player *player);

        protected:
            int _size = 64;
            int _iconPadding = 4;
            std::shared_ptr<sdl::Texture> _bg;
            std::shared_ptr<sdl::Texture> _icon;
            SDL_Rect _bgRect;
            SDL_Rect _iconRect;
    };
}; // namespace Raycaster

#endif
