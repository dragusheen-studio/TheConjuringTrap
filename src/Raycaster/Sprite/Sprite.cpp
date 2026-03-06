/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Sprite.hpp"
#include "Raycaster/Engine/Engine.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Sprite::Sprite(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string texturePath, double scale)
        : sdl::Movable(position),
          _scale(scale),
          _renderDimension(render.getDimension()),
          _cellSize(engine.getMap().getCellSize()),
          _fov(engine.getFieldOfView()),
          _dov(engine.getDepthOfView()),
          _numRays(engine.getNumRays()),
          _size(0, 0)
    {
        _texture = sdl::TextureManager::get().get(render, texturePath);
        _aspectRatio = (double)_texture->getWidth() / _texture->getHeight();
    }

    /* ----- DRAWABLE ----- */
    void Sprite::draw(sdl::Render &render)
    {
        if (!_visible || !_zBufferRef || !_texture) return;

        SDL_Renderer *renderer = render.getRenderer();
        double rayWidth3D = (double)_renderDimension.x / _numRays;

        int halfWidthRays = (_size.x / rayWidth3D) / 2.0;
        int startRay = _screenX - halfWidthRays;
        int endRay = _screenX + halfWidthRays;

        int wallBottomY = (_renderDimension.y / 2) + (_spriteSize / 2);
        int drawStartY = wallBottomY - _size.y;

        double shadow = 1.0 - (_distance / (_cellSize * _dov));
        if (shadow < 0.0) shadow = 0.0;
        sdl::Color shadowColor = (sdl::Color)(sdl::Color::WHITE)*shadow;
        _texture->applyOnTexture(shadowColor);

        for (int i = startRay; i < endRay; i++) {
            if (i >= 0 && i < _numRays) {
                if (_distance < (*_zBufferRef)[i]) {
                    int texX = (int)((i - startRay) * _texture->getWidth() / (double)(endRay - startRay));
                    if (texX < 0) texX = 0;
                    if (texX >= _texture->getWidth()) texX = _texture->getWidth() - 1;

                    SDL_Rect srcRect = {texX, 0, 1, _texture->getHeight()};
                    SDL_Rect dstRect = {(int)(i * rayWidth3D), drawStartY, (int)ceil(rayWidth3D), (int)(_size.y)};

                    SDL_RenderCopy(renderer, _texture->getSDLTexture(), &srcRect, &dstRect);
                }
            }
        }
    }

    /* ----- FUNCTIONs ----- */
    void Sprite::compute(const Player &player, const std::vector<double> &zBuffer)
    {
        _zBufferRef = &zBuffer;

        double dx = _position.x - player.getPosition().x;
        double dy = _position.y - player.getPosition().y;
        double dist = sqrt(pow(dx, 2) + pow(dy, 2));

        double angleToSprite = atan2(dy, dx);
        double angleDiff = angleToSprite - player.getAngle();

        while (angleDiff > M_PI)
            angleDiff -= 2.0 * M_PI;
        while (angleDiff < -M_PI)
            angleDiff += 2.0 * M_PI;

        if (std::abs(angleDiff) > M_PI / 2.0) {
            _visible = false;
            return;
        }

        _visible = true;

        double fovRad = _fov * (M_PI / 180.0);
        _screenX = (int)(((angleDiff / fovRad) + 0.5) * _numRays);

        _distance = dist * cos(angleDiff);
        if (_distance < 1.0) _distance = 1.0;

        _spriteSize = (_cellSize * _renderDimension.y) / _distance;

        _size.y = _spriteSize * _scale;
        _size.x = _size.y * _aspectRatio;
    }
}; // namespace Raycaster
