/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Movable.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    Movable::Movable(Vector<double> position)
        : _position(position)
    {
    }

    /* ----- GETTERs ----- */
    Vector<double> Movable::getPosition() const
    {
        return _position;
    }

    double Movable::getX() const
    {
        return _position.x;
    }

    double Movable::getY() const
    {
        return _position.y;
    }

    double Movable::getZ() const
    {
        return _position.z;
    }

    /* ----- SETTERs ----- */
    void Movable::setPosition(Vector<double> position)
    {
        if (_position == position) return;
        _position = position;
        onTransformChanged();
    }

    void Movable::setX(double x)
    {
        if (_position.x == x) return;
        _position.x = x;
        onTransformChanged();
    }

    void Movable::setY(double y)
    {
        if (_position.y == y) return;
        _position.y = y;
        onTransformChanged();
    }

    void Movable::setZ(double z)
    {
        if (_position.z == z) return;
        _position.z = z;
        onTransformChanged();
    }

    /* ----- FUNCTIONs ----- */
    void Movable::move(Vector<double> offset)
    {
        if (_position + offset == _position) return;
        _position += offset;
        onTransformChanged();
    }

    void Movable::moveX(double offset)
    {
        if (_position.x + offset == _position.x) return;
        _position.x += offset;
        onTransformChanged();
    }

    void Movable::moveY(double offset)
    {
        if (_position.y + offset == _position.y) return;
        _position.y += offset;
        onTransformChanged();
    }

    void Movable::moveZ(double offset)
    {
        if (_position.z + offset == _position.z) return;
        _position.z += offset;
        onTransformChanged();
    }

    void Movable::onTransformChanged()
    {
    }
}; // namespace sdl
