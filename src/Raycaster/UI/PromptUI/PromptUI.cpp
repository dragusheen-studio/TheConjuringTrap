/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./PromptUI.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    PromptUI::PromptUI(sdl::Render &render, const std::string &yamlPath)
    {
        _animator = std::make_unique<Animator>(yamlPath, render);
    }

    /* ----- DRAWABLE ----- */
    void PromptUI::draw(sdl::Render &render)
    {
        if (!_animator) return;

        std::shared_ptr<sdl::Texture> texture = _animator->getTexture();
        if (!texture) return;

        SDL_Rect srcRect = _animator->getSrcRect();
        SDL_Rect dstRect = {(int)_position.x, (int)_position.y, _size.x, _size.y};
        SDL_RenderCopy(render.getRenderer(), texture->getSDLTexture(), &srcRect, &dstRect);
    }

    /* ----- FUNCTIONs ----- */
    void PromptUI::update(double deltaTime, const Entity *target)
    {
        if (_animator) _animator->update(deltaTime);

        if (!target) return;

        _position.x = target->getScreenX() - _size.x / 2;
        _position.y = target->getScreenY() - _size.y / 2;
    }
}; // namespace Raycaster
