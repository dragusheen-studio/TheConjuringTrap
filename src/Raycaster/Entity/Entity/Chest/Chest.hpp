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
#include "Raycaster/Item/Item.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Chest : public Entity, public Interactible
    {
        public:
            Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string config = "chest.yaml", std::unique_ptr<Item> item = nullptr);
            ~Chest() = default;

            /* ----- OVERRIDE INTERACTIBLE ----- */
            bool canInteract(Player &player) const override;
            bool interact(sdl::Render &render, Player &player, Engine &engine) override;
            /* ----- END INTERACTIBLE ----- */

            void setItem(std::unique_ptr<Item> item);

        protected:
            bool _isOpen = false;
            std::unique_ptr<Item> _item = nullptr;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_CHEST_HPP_ ----- */
#endif
