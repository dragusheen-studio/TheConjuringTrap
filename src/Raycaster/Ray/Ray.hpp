/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_RAY_HPP_ ----- */
#ifndef RAYCASTER_RAY_HPP_
#define RAYCASTER_RAY_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <cmath>
#include <functional>
#include <limits>
#include "SDL/Color/Color.hpp"
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"
#include "SDL/Render/Render.hpp"
#include "Raycaster/Map/Map.hpp"
#include "Raycaster/Player/Player.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Ray : public sdl::Drawable, public sdl::Movable
    {
        public:
            Ray(double angle, sdl::Vector<double> position, int depthOfField, double lineWidth3D, double lineX3D, sdl::Vector<int> renderDimension);
            ~Ray() = default;

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(sdl::Render &render) override;
            /* ----- END DRAWABLE ----- */

            /* ----- OVERRIDE MOVABLE ----- */
            void onTransformChanged() override;
            /* ----- END MOVABLE ----- */

            double getDistance() const;

            void setAngle(double angle);
            void setPitch(double pitch);
            void setDepthOfField(int depthOfField);

            void compute(const Map &map, const Player &player);

        private:
            struct Hit {
                    sdl::Vector<double> position;
                    double distance;
                    std::shared_ptr<sdl::Texture> texture;
                    bool vertical;
            };

            double _angle;
            double _pitch;
            int _depthOfField;
            Hit _hit;
            bool _changed = true;
            sdl::Vector<double> _size;
            double _lineX3D;
            int _texX;
            double _fisheye;
            int _cellSize;
            std::shared_ptr<sdl::Texture> _floorTexture;
            std::shared_ptr<sdl::Texture> _ceilingTexture;
            sdl::Color _fogColor = sdl::Color::BLACK;
            sdl::Vector<int> _renderDimension;

            Hit computeHit(bool c1, bool c2, double tan, bool reverse, const Map &map);
            void _drawWall(sdl::Render &render, double maxVisibility);
            void _drawFloorAndCeiling(sdl::Render &render, double maxVisibility);
    };
}; // namespace Raycaster

/* ----- RAYCASTER_RAY_HPP_ ----- */
#endif
