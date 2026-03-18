/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Entity.hpp"
#include "Raycaster/Engine/Engine.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Entity::Entity(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string yamlPath, double scale)
        : sdl::Movable(position),
          _scale(scale),
          _renderDimension(render.getDimension()),
          _cellSize(engine.getMap().getCellSize()),
          _fov(engine.getFieldOfView()),
          _dov(engine.getDepthOfView()),
          _numRays(engine.getNumRays()),
          _size(0, 0)
    {
        _animator = std::make_unique<Animator>(yamlPath, render);
        SDL_Rect srcRect = _animator->getSrcRect();
        _aspectRatio = (double)srcRect.w / srcRect.h;
    }

    /* ----- DRAWABLE ----- */
    void Entity::draw(sdl::Render &render)
    {
        if (!_visible || !_zBufferRef || !_animator) return;

        std::shared_ptr<sdl::Texture> texture = _animator->getTexture();
        if (!texture) return;

        SDL_Renderer *renderer = render.getRenderer();
        double rayWidth3D = (double)_renderDimension.x / _numRays;

        int halfWidthRays = (_size.x / rayWidth3D) / 2.0;
        int startRay = _screenX - halfWidthRays;
        int endRay = _screenX + halfWidthRays;

        int wallBottomY = (_renderDimension.y / 2) + (_entitySize / 2);
        int drawStartY = wallBottomY - _size.y;

        double shadow = 1.0 - (_distance / (_cellSize * _dov));
        if (shadow < 0.0) shadow = 0.0;
        sdl::Color shadowColor = (sdl::Color)(sdl::Color::WHITE)*shadow;
        texture->applyOnTexture(shadowColor);

        // On récupère le rectangle de découpage de la frame actuelle !
        SDL_Rect srcRect = _animator->getSrcRect();

        for (int i = startRay; i < endRay; i++) {
            if (i >= 0 && i < _numRays) {
                if (_distance < (*_zBufferRef)[i]) {

                    // Calcul savant pour piocher la bonne colonne de pixel DANS la frame
                    int texX = srcRect.x + (int)((i - startRay) * srcRect.w / (double)(endRay - startRay));
                    if (texX < srcRect.x) texX = srcRect.x;
                    if (texX >= srcRect.x + srcRect.w) texX = srcRect.x + srcRect.w - 1;

                    SDL_Rect colSrcRect = {texX, srcRect.y, 1, srcRect.h};
                    SDL_Rect dstRect = {(int)(i * rayWidth3D), drawStartY, (int)ceil(rayWidth3D), (int)(_size.y)};

                    SDL_RenderCopy(renderer, texture->getSDLTexture(), &colSrcRect, &dstRect);
                }
            }
        }
    }

    /* ----- FUNCTIONs ----- */
    void Entity::compute(const Player &player, const std::vector<double> &zBuffer)
    {
        _zBufferRef = &zBuffer;

        double dx = _position.x - player.getPosition().x;
        double dy = _position.y - player.getPosition().y;
        double dist = sqrt(pow(dx, 2) + pow(dy, 2));

        double angleToEntity = atan2(dy, dx);
        double angleDiff = angleToEntity - player.getAngle();

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

        _entitySize = (_cellSize * _renderDimension.y) / _distance;

        _size.y = _entitySize * _scale;
        _size.x = _size.y * _aspectRatio;
    }

    void Entity::update(double deltaTime)
    {
        if (_animator) _animator->update(deltaTime);
    }
}; // namespace Raycaster
