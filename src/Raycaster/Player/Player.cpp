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
        return _sprint.maxStamina;
    }

    double Player::getMentalHealth() const
    {
        return _mentalHealth;
    }

    double Player::getMaxMentalHealth() const
    {
        return _maxMentalHealth;
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
        _updateStamina(deltaTime);
    }

    void Player::usePill()
    {
        if (!inventory->hasPill()) return;
        inventory->usePill();
        _mentalHealth += 40;
        if (_mentalHealth > _maxMentalHealth) _mentalHealth = _maxMentalHealth;
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
        if (_sprint.isSprinting && _sprint.isMoving && _sprint.stamina > 0) {
            _sprint.stamina -= _sprint.staminaConsumption * deltaTime;
            if (_sprint.stamina < 0) _sprint.stamina = 0;
        } else {
            if (_sprint.stamina < _sprint.maxStamina) {
                _sprint.stamina += _sprint.staminaRecovery * deltaTime;
                if (_sprint.stamina > _sprint.maxStamina) _sprint.stamina = _sprint.maxStamina;
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
}; // namespace Raycaster
