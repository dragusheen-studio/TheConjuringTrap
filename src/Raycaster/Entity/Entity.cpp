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
        if (_distance > (_cellSize * _dov)) return;

        std::shared_ptr<sdl::Texture> texture = _animator->getTexture();
        if (!texture) return;

        SDL_Renderer *renderer = render.getRenderer();
        double rayWidth3D = (double)_renderDimension.x / _numRays;

        int halfWidthRays = (_size.x / rayWidth3D) / 2.0;
        int startRay = _screenX - halfWidthRays;
        int endRay = _screenX + halfWidthRays;

        int horizon = (_renderDimension.y / 2) + _pitch;
        int wallBottomY = horizon + (_entitySize / 2);
        int drawStartY = wallBottomY - _size.y;

        SDL_Rect srcRect = _animator->getSrcRect();

        double shadow = 1.0 - (_distance / (_cellSize * _dov));
        if (shadow < 0.0) shadow = 0.0;
        sdl::Color finalColor = (sdl::Color)(sdl::Color::WHITE)*shadow;
        finalColor *= shadow;

        if (_selected) {
            sdl::Color glowColor(255, 200, 0, 255);
            glowColor *= shadow;
            texture->setColor(glowColor);

            texture->setBlendMode(SDL_BLENDMODE_ADD);

            double timeSec = SDL_GetTicks() / 1000.0;
            double pulse = (sin(timeSec * 5.0) + 1.0) / 2.0;
            int padding = 2 + (int)((_size.y * 0.05) * pulse);

            for (int i = startRay; i < endRay; i++) {
                if (i >= 0 && i < _numRays) {
                    if (_distance < (*_zBufferRef)[i]) {
                        int texX = srcRect.x + (int)((i - startRay) * srcRect.w / (double)(endRay - startRay));
                        if (texX < srcRect.x) texX = srcRect.x;
                        if (texX >= srcRect.x + srcRect.w) texX = srcRect.x + srcRect.w - 1;

                        SDL_Rect colSrcRect = {texX, srcRect.y, 1, srcRect.h};

                        SDL_Rect dstRect = {
                            (int)(i * rayWidth3D) - padding,
                            drawStartY - padding,
                            (int)ceil(rayWidth3D) + (padding * 2),
                            (int)(_size.y) + (padding * 2)};

                        SDL_RenderCopy(renderer, texture->getSDLTexture(), &colSrcRect, &dstRect);
                    }
                }
            }
            texture->setBlendMode(SDL_BLENDMODE_BLEND);
        }

        texture->setColor(finalColor);
        for (int i = startRay; i < endRay; i++) {
            if (i >= 0 && i < _numRays) {
                if (_distance < (*_zBufferRef)[i]) {
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

    /* ----- GETTERS ----- */
    double Entity::getDistance() const
    {
        return _distance;
    }

    int Entity::getScreenX() const
    {
        double rayWidth3D = (double)_renderDimension.x / _numRays;
        return (int)(_screenX * rayWidth3D) - (_size.x / 6);
    }

    int Entity::getScreenY() const
    {
        int horizon = (_renderDimension.y / 2) + _pitch;
        int wallBottomY = horizon + (_entitySize / 2);
        int drawStartY = wallBottomY - _size.y;
        return drawStartY;
    }

    /* ----- SETTERS ----- */
    void Entity::setSelected(bool selected)
    {
        _selected = selected;
    }

    /* ----- FUNCTIONs ----- */
    bool Entity::isTargeted(double maxDistance) const
    {
        if (!_visible) return false;
        if (_distance > _cellSize * maxDistance) return false;

        int centerLeft = _numRays / 3;
        int centerRight = (_numRays / 3) * 2;
        return (_screenX >= centerLeft && _screenX <= centerRight);
    }

    void Entity::compute(const Player &player, const std::vector<double> &zBuffer)
    {
        _zBufferRef = &zBuffer;

        double mentalRatio = player.getMentalHealth() / player.getMaxMentalHealth();
        double scaredFactor = player.getScaredFactor();
        double scaredEffect = 1.0 - (scaredFactor * 0.8);
        _dov = (2.0 + (mentalRatio * (5.0 - 2.0))) * scaredEffect;
        if (_dov < 0.5) _dov = 0.5;

        double dx = _position.x - player.getPosition().x;
        double dy = _position.y - player.getPosition().y;
        double dist = sqrt(pow(dx, 2) + pow(dy, 2));

        double angleToEntity = atan2(dy, dx);
        double angleDiff = angleToEntity - player.getAngle();
        _pitch = player.getPitch();

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
        _selected = false;
    }
}; // namespace Raycaster
