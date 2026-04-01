/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./LootUI.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    LootUI::LootUI(sdl::Render &render, std::shared_ptr<sdl::Texture> icon, const Entity *source)
        : _icon(std::make_shared<sdl::Texture>(render, icon->getPath())), _source(source)
    {
    }

    /* ----- DRAWABLE ----- */
    void LootUI::draw(sdl::Render &render)
    {
        if (!_source || !_icon || _alpha <= 0) return;

        int x = _source->getScreenX();
        int y = _source->getScreenY();

        SDL_Rect dstRect = {x - (_currentSize / 2), y - _currentSize - (int)_offsetY, _currentSize, _currentSize};
        _icon->setOpacity((int)_alpha);
        SDL_RenderCopy(render.getRenderer(), _icon->getSDLTexture(), NULL, &dstRect);
    }

    /* ----- FUNCTIONs ----- */
    bool LootUI::update(double deltaTime)
    {
        _lifetime -= deltaTime;
        if (_lifetime <= 0) return false;

        _offsetY += 60.0 * deltaTime;
        _alpha = (_lifetime / 1.5) * 255.0;

        if (_source) {
            double distance = _source->getDistance();
            double maxDist = 96.0;
            double minDist = 32.0;

            double t = (maxDist - distance) / (maxDist - minDist);
            if (t < 0.0) t = 0.0;
            if (t > 1.0) t = 1.0;

            double minSize = 24.0;
            double maxSize = 48.0;
            _currentSize = (int)(minSize + (maxSize - minSize) * t);
        }

        return true;
    }
}; // namespace Raycaster
