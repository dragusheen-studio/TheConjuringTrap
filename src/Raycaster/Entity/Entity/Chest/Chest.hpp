/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_CHEST_HPP_ ----- */
#ifndef RAYCASTER_CHEST_HPP_
#define RAYCASTER_CHEST_HPP_

/* ----- INCLUDEs ----- */
#include "Raycaster/Entity/Entity.hpp"
#include "Raycaster/Entity/Interactible/Interactible.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Chest : public Entity, public Interactible
    {
        public:
            Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string config = "chest.yaml");
            ~Chest() = default;

            /* ----- OVERRIDE INTERACTIBLE ----- */
            bool canInteract(Player &player) const override;
            bool interact(sdl::Render &render, Player &player) override;
            /* ----- END INTERACTIBLE ----- */

        protected:
            bool _isOpen = false;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_CHEST_HPP_ ----- */
#endif
