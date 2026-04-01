/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_LOOT_UI_HPP_ ----- */
#ifndef RAYCASTER_LOOT_UI_HPP_
#define RAYCASTER_LOOT_UI_HPP_

/* ----- INCLUDEs ----- */
#include <memory>
#include <string>
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"
#include "SDL/Render/Render.hpp"
#include "Raycaster/Entity/Animation/Animator.hpp"
#include "Raycaster/Entity/Entity.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class LootUI : public sdl::Drawable, public sdl::Movable
    {
        public:
            LootUI(sdl::Render &render, std::shared_ptr<sdl::Texture> icon, const Entity *source);
            ~LootUI() = default;

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(sdl::Render &render) override;
            /* ----- END DRAWABLE ----- */

            bool update(double deltaTime);

        private:
            std::shared_ptr<sdl::Texture> _icon;
            const Entity *_source;
            double _offsetY = 0.0;
            double _alpha = 255.0;
            double _lifetime = 1.5;
            int _currentSize = 48;
            sdl::Vector<int> _baseSize = {48, 48};
    };
}; // namespace Raycaster

#endif
