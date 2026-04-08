/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Minimap.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Minimap::Minimap(sdl::Vector<double> position, int size, double scale)
        : sdl::Movable(position), _size(size), _scale(scale), _mapTexture(nullptr), _mapRef(nullptr)
    {
    }

    Minimap::~Minimap()
    {
        if (_mapTexture) SDL_DestroyTexture(_mapTexture);
    }

    /* ----- DRAWABLE ----- */
    void Minimap::draw(sdl::Render &render)
    {
        if (!_mapRef) return;
        if (!_mapTexture) _generateTexture(render, *_mapRef);

        SDL_Renderer *renderer = render.getRenderer();

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 180);
        SDL_Rect bg = {(int)_position.x, (int)_position.y, _size, _size};
        SDL_RenderFillRect(renderer, &bg);

        SDL_RenderSetClipRect(renderer, &bg);

        sdl::Vector<int> mapSize = _mapRef->getSize();
        int cs = _mapRef->getCellSize();

        int scaledW = mapSize.x * cs * _scale;
        int scaledH = mapSize.y * cs * _scale;

        int centerX = _position.x + _size / 2;
        int centerY = _position.y + _size / 2;

        SDL_Rect destRect = {
            centerX - (int)(_pPos.x * _scale),
            centerY - (int)(_pPos.y * _scale),
            scaledW,
            scaledH};

        SDL_Point pivot = {(int)(_pPos.x * _scale), (int)(_pPos.y * _scale)};
        double mapRotation = -(_pAngle * (180.0 / M_PI)) - 90.0;

        SDL_RenderCopyEx(renderer, _mapTexture, NULL, &destRect, mapRotation, &pivot, SDL_FLIP_NONE);

        if (_entitiesRef) {
            for (const auto &entity : *_entitiesRef) {
                double relX = entity->getX() - _pPos.x;
                double relY = entity->getY() - _pPos.y;

                double rotX = relX * cos(-_pAngle - M_PI / 2) - relY * sin(-_pAngle - M_PI / 2);
                double rotY = relX * sin(-_pAngle - M_PI / 2) + relY * cos(-_pAngle - M_PI / 2);

                int drawX = centerX + (int)(rotX * _scale);
                int drawY = centerY + (int)(rotY * _scale);

                sdl::Circle entityBlip(3, sdl::Vector<double>(drawX, drawY), sdl::Color::Green);
                entityBlip.draw(render);
            }
        }

        sdl::Circle player(4, sdl::Vector<double>(centerX, centerY), sdl::Color::Yellow);
        player.draw(render);

        SDL_RenderSetClipRect(renderer, NULL);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &bg);
    }

    /* ----- FUNCTIONs ----- */
    void Minimap::compute(const Map &map, const Player &player, const std::vector<std::unique_ptr<Entity>> &entities)
    {
        _pPos = player.getPosition();
        _pAngle = player.getAngle();
        _mapRef = &map;
        _entitiesRef = &entities;
    }

    /* ----- PRIVATE FUNCTIONs ----- */
    void Minimap::_generateTexture(sdl::Render &render, const Map &map)
    {
        SDL_Renderer *renderer = render.getRenderer();
        sdl::Vector<int> mapSize = map.getSize();
        int cs = map.getCellSize();

        _mapTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mapSize.x * cs, mapSize.y * cs);
        SDL_Texture *oldTarget = SDL_GetRenderTarget(renderer);

        SDL_SetRenderTarget(renderer, _mapTexture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        for (int y = 0; y < mapSize.y; y++) {
            for (int x = 0; x < mapSize.x; x++) {
                if (map.isSolidCellAt(sdl::Vector<double>(x * cs, y * cs))) {
                    SDL_Rect r = {x * cs, y * cs, cs, cs};
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_SetRenderTarget(renderer, oldTarget);
    }
}; // namespace Raycaster
