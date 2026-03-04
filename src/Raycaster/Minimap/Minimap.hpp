/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_MINI_MAP_HPP_ ----- */
#ifndef RAYCASTER_MINI_MAP_HPP_
#define RAYCASTER_MINI_MAP_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"
#include "Raycaster/Map/Map.hpp"
#include "Raycaster/Player/Player.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Minimap : public sdl::Drawable, public sdl::Movable
    {
        public:
            Minimap(sdl::Vector<double> position, int size, double scale);
            ~Minimap();

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(sdl::Render &render) override;
            /* ----- END DRAWABLE ----- */

            void compute(const Map &map, const Player &player);

        private:
            int _size;
            double _scale;
            SDL_Texture *_mapTexture;
            sdl::Vector<double> _pPos;
            double _pAngle;
            const Map *_mapRef;

            void _generateTexture(sdl::Render &render, const Map &map);
    };
}; // namespace Raycaster

/* ----- RAYCASTER_MINI_MAP_HPP_ ----- */
#endif
