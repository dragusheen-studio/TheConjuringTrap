/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_PROMPT_UI_HPP_ ----- */
#ifndef RAYCASTER_PROMPT_UI_HPP_
#define RAYCASTER_PROMPT_UI_HPP_

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
    class PromptUI : public sdl::Drawable, public sdl::Movable
    {
        public:
            PromptUI(sdl::Render &render, const std::string &yamlPath);
            ~PromptUI() = default;

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(sdl::Render &render) override;
            /* ----- END DRAWABLE ----- */

            void update(double deltaTime, const Entity *target);

        private:
            std::unique_ptr<Animator> _animator;
            sdl::Vector<int> _size = {48, 48};
    };
}; // namespace Raycaster

#endif
