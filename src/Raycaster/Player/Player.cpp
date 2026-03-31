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
        inventory = std::make_shared<Inventory>();

        _angle = 0;
        _delta.x = cos(_angle) * 5;
        _delta.y = sin(_angle) * 5;
        _footstepSound.stepThreshold = _speed * _sprintMultiplier;
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

    double Player::getStamina() const
    {
        return _sprint.stamina;
    }

    double Player::getMaxStamina() const
    {
        return _sprint.max;
    }

    double Player::getMentalHealth() const
    {
        return _mentalHealth.value;
    }

    double Player::getMaxMentalHealth() const
    {
        return _mentalHealth.max;
    }

    /* ----- SETTERs ----- */
    void Player::setSprint(bool sprint)
    {
        _sprint.isSprinting = sprint;
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
        _sprint.isMoving = true;
        sdl::Vector<double> oldPos = _position;

        double speed = _speed;
        if (_sprint.isSprinting && _sprint.stamina > 0) speed *= _sprintMultiplier;

        double moveY = _delta.y * speed * deltaTime;
        double moveX = _delta.x * speed * deltaTime;

        setPosition(_checkMovement(moveX, moveY, map));
        _updateFootsteps(oldPos);
    }

    void Player::strafe(double deltaTime, const Map &map)
    {
        _sprint.isMoving = true;
        sdl::Vector<double> oldPos = _position;

        double speed = _speed;
        if (_sprint.isSprinting && _sprint.stamina > 0) speed *= _sprintMultiplier;

        double strafeAngle = _angle + (M_PI / 2.0);

        double moveX = cos(strafeAngle) * 5 * speed * deltaTime;
        double moveY = sin(strafeAngle) * 5 * speed * deltaTime;

        setPosition(_checkMovement(moveX, moveY, map));
        _updateFootsteps(oldPos);
    }

    void Player::update(double deltaTime)
    {
        _updateMentalHealth(deltaTime);
        _updateStamina(deltaTime);
    }

    void Player::usePill()
    {
        if (!inventory->hasPill()) return;
        inventory->usePill();
        _mentalHealth.value += 40;
        if (_mentalHealth.value > _mentalHealth.max) _mentalHealth.value = _mentalHealth.max;
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

    void Player::_updateStamina(double deltaTime)
    {
        double fatigueMult = 1.0 + (1.0 - (_mentalHealth.value / _mentalHealth.max)) * 1.5;

        if (_sprint.isSprinting && _sprint.isMoving && _sprint.stamina > 0) {
            _sprint.stamina -= (_sprint.consumption * fatigueMult) * deltaTime;
            if (_sprint.stamina < 0) _sprint.stamina = 0;
        } else {
            if (_mentalHealth.value > _mentalHealth.max / 2 && _sprint.stamina < _sprint.max) {
                _sprint.stamina += _sprint.recovery * deltaTime;
                if (_sprint.stamina > _sprint.max) _sprint.stamina = _sprint.max;
            }
        }

        _sprint.isMoving = false;
    }

    void Player::_updateFootsteps(sdl::Vector<double> oldPos)
    {
        double distanceMoved = _position.dist(oldPos);
        if (distanceMoved <= 0) return;

        _footstepSound.distanceCounter += distanceMoved;
        if (_footstepSound.distanceCounter >= _footstepSound.stepThreshold) {
            _footstepSound.distanceCounter = 0;
            sdl::AudioManager::get().playSound(_footstepSound.sounds[_footstepSound.index], (_sprint.isSprinting && _sprint.stamina > 2) ? -1 : 60);
            _footstepSound.index = (_footstepSound.index + 1) % _footstepSound.sounds.size();
        }
    }

    void Player::_updateMentalHealth(double deltaTime)
    {
        _mentalHealth.idleTimer = _sprint.isMoving ? 0.0 : _mentalHealth.idleTimer + deltaTime;
        if (_mentalHealth.idleTimer >= _mentalHealth.idleThreshold) {
            if (_mentalHealth.value < _mentalHealth.max) {
                _mentalHealth.value += _mentalHealth.recovery * deltaTime;
                if (_mentalHealth.value > _mentalHealth.max) _mentalHealth.value = _mentalHealth.max;
            }
        }
    }
}; // namespace Raycaster
