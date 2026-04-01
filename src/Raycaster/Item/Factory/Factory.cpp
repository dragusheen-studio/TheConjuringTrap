/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Factory.hpp"
#include "Raycaster/Player/Player.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    ItemFactory &ItemFactory::get()
    {
        static ItemFactory instance;
        return instance;
    }

    ItemFactory::ItemFactory()
    {
        _factories[Type::KEY] = std::bind(&ItemFactory::createKey, this, std::placeholders::_1);
        _factories[Type::PILL] = std::bind(&ItemFactory::createPill, this, std::placeholders::_1);
        _factories[Type::SCREAMER] = std::bind(&ItemFactory::createScreamer, this, std::placeholders::_1);
    }

    /* ----- FUNCTIONs ----- */
    std::unique_ptr<Item> ItemFactory::create(Type type, sdl::Render &render)
    {
        if (_factories.find(type) == _factories.end())
            return nullptr;
        return _factories[type](render);
    }

    /* ----- PRIVATEs FUNCTIONs ----- */
    std::unique_ptr<Item> ItemFactory::createKey(sdl::Render &render)
    {
        return std::make_unique<Item>(render, "ui/keys.png", [](Player &p) {
            p.inventory->gainKey();
        });
    }

    std::unique_ptr<Item> ItemFactory::createPill(sdl::Render &render)
    {
        return std::make_unique<Item>(render, "ui/pills.png", [](Player &p) {
            p.inventory->gainPill();
        });
    }

    std::unique_ptr<Item> ItemFactory::createScreamer(sdl::Render &render)
    {
        return std::make_unique<Item>(render, "ui/mentalHealth.png", [](Player &p) {
            sdl::AudioManager::get().playSound("jumpscare.mp3");
            p.scare();
        });
    }
}; // namespace Raycaster
