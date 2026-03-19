/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Ray.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Ray::Ray(double angle, sdl::Vector<double> position, int depthOfField, double width, double lineX3D, sdl::Vector<int> renderDimension)
        : Movable(position),
          _angle(angle),
          _depthOfField(depthOfField),
          _size(width, 0),
          _lineX3D(lineX3D),
          _renderDimension(renderDimension)
    {
        _changed = true;
    }

    /* ----- DRAWABLE ----- */
    void Ray::draw(sdl::Render &render)
    {
        double maxVisibility = _cellSize * _depthOfField;

        _drawWall(render, maxVisibility);
        _drawFloorAndCeiling(render, maxVisibility);
    }

    /* ----- MOVABLE ----- */
    void Ray::onTransformChanged()
    {
        _changed = true;
    }

    /* ----- GETTERs ----- */
    double Ray::getDistance() const
    {
        return _hit.distance;
    }

    /* ----- SETTERs ----- */
    void Ray::setAngle(double angle)
    {
        if (angle == _angle) return;
        _angle = angle;
        _changed = true;
    }

    void Ray::setDepthOfField(int depthOfField)
    {
        if (depthOfField == _depthOfField) return;
        _depthOfField = depthOfField;
        _changed = true;
    }

    /* ----- FUNCTIONs ----- */
    void Ray::compute(const Map &map, const Player &player)
    {
        if (!_changed) return;
        _changed = false;

        if (_angle < 0) _angle += 2 * M_PI;
        if (_angle > 2 * M_PI) _angle -= 2 * M_PI;

        Hit h = computeHit(_angle > M_PI, _angle < M_PI, -1.0 / tan(_angle), true, map);
        Hit v = computeHit(_angle > M_PI / 2 && _angle < 3 * M_PI / 2, _angle < M_PI / 2 || _angle > 3 * M_PI / 2, -tan(_angle), false, map);

        _hit = (h.distance < v.distance) ? h : v;

        _fisheye = player.getAngle() - _angle;
        if (_fisheye < 0) _fisheye += 2 * M_PI;
        if (_fisheye > M_PI) _fisheye = 2 * M_PI - _fisheye;

        _hit.distance *= cos(_fisheye);
        _size.y = (map.getCellSize() * _renderDimension.y) / _hit.distance;

        _cellSize = map.getCellSize();
        _floorTexture = map.getFloorTexture();
        _ceilingTexture = map.getCeilingTexture();

        if (_hit.texture) {
            double hitCoord = _hit.vertical ? _hit.position.y : _hit.position.x;
            double fraction = fmod(hitCoord, map.getCellSize()) / map.getCellSize();

            _texX = (int)(fraction * _hit.texture->getWidth());

            if (_texX >= _hit.texture->getWidth()) _texX = _hit.texture->getWidth() - 1;
            if (_texX < 0) _texX = 0;
        }
    }

    /* ----- PRIVATE FUNCTIONs ----- */
    Ray::Hit Ray::computeHit(bool c1, bool c2, double tan, bool reverse, const Map &map)
    {
        sdl::Vector<double> r(0, 0);
        sdl::Vector<double> offset(0, 0);
        Hit hit = {_position, std::numeric_limits<double>::max(), nullptr, !reverse};

        if (c1) {
            if (reverse) {
                r.y = floor(_position.y / map.getCellSize()) * map.getCellSize() - 0.0001;
                r.x = (_position.y - r.y) * tan + _position.x;
                offset.y = -map.getCellSize();
                offset.x = -offset.y * tan;
            } else {
                r.x = floor(_position.x / map.getCellSize()) * map.getCellSize() - 0.0001;
                r.y = (_position.x - r.x) * tan + _position.y;
                offset.x = -map.getCellSize();
                offset.y = -offset.x * tan;
            }
        } else if (c2) {
            if (reverse) {
                r.y = floor(_position.y / map.getCellSize()) * map.getCellSize() + map.getCellSize();
                r.x = (_position.y - r.y) * tan + _position.x;
                offset.y = map.getCellSize();
                offset.x = -offset.y * tan;
            } else {
                r.x = floor(_position.x / map.getCellSize()) * map.getCellSize() + map.getCellSize();
                r.y = (_position.x - r.x) * tan + _position.y;
                offset.x = map.getCellSize();
                offset.y = -offset.x * tan;
            }
        } else {
            return hit;
        }

        for (int _ = 0; _ <= _depthOfField + 1; _++) {
            std::optional<Map::CellData> mapCell = map.getCellAt(r);
            if (!mapCell) break;

            if (mapCell->isSolid()) {
                hit.position = r;
                hit.distance = _position.dist(hit.position);
                hit.texture = mapCell->getTexture();
                break;
            }
            r += offset;
        }
        return hit;
    }

    void Ray::_drawWall(sdl::Render &render, double maxVisibility)
    {
        SDL_Rect dstRect = {int(_lineX3D), int(_renderDimension.y / 2 - _size.y / 2), int(_size.x), int(_size.y)};

        if (_hit.distance < maxVisibility && _hit.texture) {
            SDL_Rect srcRect = {_texX, 0, 1, _hit.texture->getHeight()};

            double shadow = 1.0 - (_hit.distance / maxVisibility);
            if (shadow < 0.0) shadow = 0.0;

            sdl::Color shadowColor = (sdl::Color)(sdl::Color::WHITE)*shadow;
            if (_hit.vertical) shadowColor *= 0.6;

            _hit.texture->applyOnTexture(shadowColor);
            SDL_RenderCopy(render.getRenderer(), _hit.texture->getSDLTexture(), &srcRect, &dstRect);
        } else {
            _fogColor.apply(render);
            SDL_RenderFillRect(render.getRenderer(), &dstRect);
        }
    }

    void Ray::_drawFloorAndCeiling(sdl::Render &render, double maxVisibility)
    {
        if (!_floorTexture || !_ceilingTexture) return;

        int drawEnd = (_renderDimension.y / 2) + (_size.y / 2);
        if (drawEnd < 0) drawEnd = 0;
        if (drawEnd > _renderDimension.y) drawEnd = _renderDimension.y;

        int minY = (_renderDimension.y / 2) + (_cellSize * (double)(_renderDimension.y / 2)) / (maxVisibility * cos(_fisheye));

        if (minY < drawEnd) minY = drawEnd;

        if (minY > drawEnd) {
            _fogColor.apply(render);

            SDL_Rect fogFloor = {int(_lineX3D), drawEnd, int(_size.x), minY - drawEnd};
            SDL_RenderFillRect(render.getRenderer(), &fogFloor);

            SDL_Rect fogCeil = {int(_lineX3D), _renderDimension.y - minY, int(_size.x), minY - drawEnd};
            SDL_RenderFillRect(render.getRenderer(), &fogCeil);
        }

        for (int y = minY; y < _renderDimension.y; y++) {
            double p = y - (double)(_renderDimension.y / 2);
            double straightDist = (_cellSize * (double)(_renderDimension.y / 2)) / p;
            double realDist = straightDist / cos(_fisheye);

            double floorX = _position.x + cos(_angle) * realDist;
            double floorY = _position.y + sin(_angle) * realDist;

            double fractionX = fmod(floorX, _cellSize) / _cellSize;
            double fractionY = fmod(floorY, _cellSize) / _cellSize;
            if (fractionX < 0) fractionX += 1.0;
            if (fractionY < 0) fractionY += 1.0;

            double shadow = 1.0 - (realDist / maxVisibility);
            if (shadow < 0.0) shadow = 0.0;

            std::pair<std::shared_ptr<sdl::Texture>, int> a = std::make_pair(_floorTexture, y);
            std::pair<std::shared_ptr<sdl::Texture>, int> b = std::make_pair(_ceilingTexture, _renderDimension.y - y - 1);
            for (auto it : {&a, &b}) {
                int texX = (int)(fractionX * it->first->getWidth());
                int texY = (int)(fractionY * it->first->getHeight());
                if (texX >= it->first->getWidth()) texX = it->first->getWidth() - 1;
                if (texY >= it->first->getHeight()) texY = it->first->getHeight() - 1;

                sdl::Color ceilColor = it->first->getPixel(texX, texY) * shadow;
                ceilColor.apply(render);

                SDL_Rect ceilRect = {int(_lineX3D), it->second, int(_size.x), 1};
                SDL_RenderFillRect(render.getRenderer(), &ceilRect);
            }
        }
    }
}; // namespace Raycaster
