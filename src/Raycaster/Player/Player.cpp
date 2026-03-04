/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Player.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Player::Player(sdl::Vector<double> position)
        : Movable(position)
    {
        _angle = 0;
        _delta.x = cos(_angle) * 5;
        _delta.y = sin(_angle) * 5;
    }

    /* ----- GETTERs ----- */
    double Player::getAngle() const
    {
        return _angle;
    }

    /* ----- FUNCTIONs ----- */
    void Player::rotate(double deltaTime, double force)
    {
        _angle += _rotationSpeed * deltaTime * force;
        _setDelta();
    }

    void Player::rotateMouse(int offset)
    {
        _angle += offset * _mouseSensitivity;
        _setDelta();
    }

    void Player::forward(double deltaTime, const Map &map)
    {
        double moveX = _delta.x * _speed * deltaTime;
        double moveY = _delta.y * _speed * deltaTime;

        int offsetX = (moveX > 0) ? _size : -_size;
        int offsetY = (moveY > 0) ? _size : -_size;

        sdl::Vector<double> nextPos = _position;

        sdl::Vector<double> checkX(_position.x + moveX + offsetX, _position.y);
        if (!map.isSolidCellAt(checkX)) nextPos.x += moveX;

        sdl::Vector<double> checkY(_position.x, _position.y + moveY + offsetY);
        if (!map.isSolidCellAt(checkY)) nextPos.y += moveY;

        setPosition(nextPos);
    }

    /* ----- PRIVATE FUNCTIONs ----- */
    void Player::_setDelta()
    {
        if (_angle < 0) _angle += 2 * M_PI;
        if (_angle > 2 * M_PI) _angle -= 2 * M_PI;
        _delta.x = cos(_angle) * 5;
        _delta.y = sin(_angle) * 5;
    }
}; // namespace Raycaster
