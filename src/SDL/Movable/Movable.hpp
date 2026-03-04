/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_MOVABLE_HPP_ ----- */
#ifndef GRADE_DE_MOVABLE_HPP_
#define GRADE_DE_MOVABLE_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include "SDL/Render/Render.hpp"
#include "SDL/Vector/Vector.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class Movable
    {
        public:
            Movable(Vector<double> position);
            virtual ~Movable() = default;

            Vector<double> getPosition() const;
            double getX() const;
            double getY() const;
            double getZ() const;

            virtual void setPosition(Vector<double> position);
            virtual void setX(double x);
            virtual void setY(double y);
            virtual void setZ(double z);

            virtual void move(Vector<double> offset);
            virtual void moveX(double offset);
            virtual void moveY(double offset);
            virtual void moveZ(double offset);

            virtual void onTransformChanged();

        protected:
            Vector<double> _position;
    };
}; // namespace sdl

/* ----- GRADE_DE_MOVABLE_HPP_ ----- */
#endif
