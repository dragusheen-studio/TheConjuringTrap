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

    double Player::getPitch() const
    {
        return _pitch;
    }

    bool Player::hasKey() const
    {
        return _keys > 0;
    }

    /* ----- FUNCTIONs ----- */
    void Player::gainKey()
    {
        _keys++;
        std::cout << _keys << std::endl;
    }

    void Player::useKey()
    {
        _keys--;
        std::cout << _keys << std::endl;
    }

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

    void Player::pitch(double deltaTime, double force)
    {
        _pitch += _rotationSpeed * deltaTime * force;
    }

    void Player::pitchMouse(int offset)
    {
        _pitch -= offset * 2.0;

        double limit = 200.0;
        if (_pitch > limit) _pitch = limit;
        if (_pitch < -limit) _pitch = -limit;
    }

    void Player::forward(double deltaTime, const Map &map)
    {
        double moveX = _delta.x * _speed * deltaTime;
        double moveY = _delta.y * _speed * deltaTime;

        setPosition(_checkMovement(moveX, moveY, map));
    }

    void Player::strafe(double deltaTime, const Map &map)
    {
        double strafeAngle = _angle + (M_PI / 2.0);

        double moveX = cos(strafeAngle) * 5 * _speed * deltaTime;
        double moveY = sin(strafeAngle) * 5 * _speed * deltaTime;

        setPosition(_checkMovement(moveX, moveY, map));
    }

    /* ----- PRIVATE FUNCTIONs ----- */
    void Player::_setDelta()
    {
        if (_angle < 0) _angle += 2 * M_PI;
        if (_angle > 2 * M_PI) _angle -= 2 * M_PI;
        _delta.x = cos(_angle) * 5;
        _delta.y = sin(_angle) * 5;
    }

    sdl::Vector<double> Player::_checkMovement(const double &moveX, const double &moveY, const Map &map)
    {
        int offsetX = (moveX > 0) ? _size : -_size;
        int offsetY = (moveY > 0) ? _size : -_size;

        sdl::Vector<double> nextPos = _position;

        sdl::Vector<double> checkX(_position.x + moveX + offsetX, _position.y);
        if (!map.isSolidCellAt(checkX)) nextPos.x += moveX;

        sdl::Vector<double> checkY(_position.x, _position.y + moveY + offsetY);
        if (!map.isSolidCellAt(checkY)) nextPos.y += moveY;

        return nextPos;
    }
}; // namespace Raycaster
