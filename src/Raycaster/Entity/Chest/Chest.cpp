/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Chest.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Chest::Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position)
        : Raycaster::Entity(engine, render, position, "chest/Metal Chest - Closed.png", 0.5)
    {
    }

    /* ----- FUNCTIONs ----- */
    void Chest::compute(const Player &player, const std::vector<double> &zBuffer)
    {
        Raycaster::Entity::compute(player, zBuffer);
    }
}; // namespace Raycaster
