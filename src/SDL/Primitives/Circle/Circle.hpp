/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_CIRCLE_HPP_ ----- */
#ifndef GRADE_DE_CIRCLE_HPP_
#define GRADE_DE_CIRCLE_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include "SDL/Color/Color.hpp"
#include "SDL/Drawable/Drawable.hpp"
#include "SDL/Movable/Movable.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class Circle : public Drawable, public Movable
    {
        public:
            Circle(int radius, Vector<double> position = Vector<double>(0, 0), Color color = Color::BLACK);
            ~Circle() = default;

            /* ----- OVERRIDE DRAWABLE ----- */
            void draw(Render &render) override;
            /* ----- END DRAWABLE ----- */

        protected:
            int _radius;
            Color _color;
    };
}; // namespace sdl

/* ----- GRADE_DE_CIRCLE_HPP_ ----- */
#endif
