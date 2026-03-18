/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_ENTITY_HPP_ ----- */
#ifndef RAYCASTER_ENTITY_HPP_
#define RAYCASTER_ENTITY_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"
#include "SDL/Texture/Texture.hpp"
#include "SDL/TextureManager/TextureManager.hpp"
#include "Raycaster/Player/Player.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Engine;

    class Entity : public sdl::Drawable, public sdl::Movable
    {
        public:
            Entity(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string texturePath, double scale = 1.0);
            ~Entity() = default;

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(sdl::Render &render) override;
            /* ----- END DRAWABLE ----- */

            virtual void compute(const Player &player, const std::vector<double> &zBuffer);

        protected:
            std::shared_ptr<sdl::Texture> _texture;

            double _scale;
            double _fov;
            double _dov;
            double _aspectRatio;
            bool _visible = false;
            double _distance = 0;
            int _screenX = 0;
            int _entitySize = 0;
            int _numRays = 0;
            int _cellSize = 0;
            sdl::Vector<double> _size;
            sdl::Vector<int> _renderDimension;
            const std::vector<double> *_zBufferRef = nullptr;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_ENTITY_HPP_ ----- */
#endif
