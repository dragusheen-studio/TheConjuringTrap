/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Chest.hpp"
#include "Raycaster/Engine/Engine.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Chest::Chest(const Engine &engine, sdl::Render &render, sdl::Vector<double> position, std::string config, std::unique_ptr<Item> item)
        : Entity(engine, render, position, "assets/config/entity/chest/" + config, 0.5), _item(std::move(item))
    {
    }

    /* ----- INTERACTIBLE ----- */
    bool Chest::canInteract(Player &player) const
    {
        return (!_isOpen && isTargeted());
    }

    bool Chest::interact(sdl::Render &render, Player &player, Engine &engine)
    {
        if (_isOpen) return false;

        _isOpen = true;
        _animator->play("opening");

        if (_item != nullptr) {
            _item->pickup(player);
            engine.addLootUI(_item->getIcon(), this);
        }
        return true;
    }

    /* ----- SETTERs ----- */
    void Chest::setItem(std::unique_ptr<Item> item)
    {
        _item = std::move(item);
    }
}; // namespace Raycaster
