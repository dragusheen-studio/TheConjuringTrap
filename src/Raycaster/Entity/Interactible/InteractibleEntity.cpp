/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./InteractibleEntity.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    InteractibleEntity::InteractibleEntity(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string yamlPath, double scale)
        : Entity(engine, render, position, yamlPath, scale)
    {
    }

    /* ----- FUNCTIONs ----- */
    bool InteractibleEntity::canInteract() const
    {
        if (!_visible) return false;

        if (_distance > _cellSize * 1.5) return false;

        int centerLeft = _numRays / 3;
        int centerRight = (_numRays / 3) * 2;

        return (_screenX >= centerLeft && _screenX <= centerRight);
    }

    void InteractibleEntity::interact(sdl::Render &render)
    {
    }
}; // namespace Raycaster
