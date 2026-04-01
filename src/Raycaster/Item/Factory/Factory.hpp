/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_ITEM_FACTORY_HPP_ ----- */
#ifndef RAYCASTER_ITEM_FACTORY_HPP_
#define RAYCASTER_ITEM_FACTORY_HPP_

/* ----- INCLUDEs ----- */
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "Raycaster/Item/Item/Item.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class ItemFactory
    {
        public:
            enum Type {
                KEY,
                PILL,
                SCREAMER
            };

            static ItemFactory &get();
            ~ItemFactory() = default;

            std::unique_ptr<Item> create(Type type, sdl::Render &render);

        private:
            std::unordered_map<Type, std::function<std::unique_ptr<Item>(sdl::Render &)>> _factories;

            ItemFactory();

            std::unique_ptr<Item> createKey(sdl::Render &render);
            std::unique_ptr<Item> createPill(sdl::Render &render);
            std::unique_ptr<Item> createScreamer(sdl::Render &render);
    };
}; // namespace Raycaster

#endif
