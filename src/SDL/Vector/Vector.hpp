/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_VECTOR_HPP_ ----- */
#ifndef GRADE_DE_VECTOR_HPP_
#define GRADE_DE_VECTOR_HPP_

/* ----- INCLUDEs ----- */
#include <cmath>
#include <type_traits>

/* ----- CLASS ----- */
namespace sdl
{
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value, T>::type * = nullptr>
    class Vector
    {
        public:
            Vector(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
            ~Vector() = default;

            T x;
            T y;
            T z;

            Vector<T> &operator+=(const Vector<T> &other)
            {
                x += other.x;
                y += other.y;
                z += other.z;
                return *this;
            }

            bool operator==(const Vector<T> &other) const
            {
                return x == other.x && y == other.y && z == other.z;
            }

            Vector<T> operator+(const Vector<T> &other) const
            {
                return Vector<T>(x + other.x, y + other.y, z + other.z);
            }

            T dist(const Vector<T> &other) const
            {
                return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2) + pow(other.z - z, 2));
            }
    };
}; // namespace sdl

/* ----- GRADE_DE_VECTOR_HPP_ ----- */
#endif
