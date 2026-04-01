/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_ITEM_HPP_ ----- */
#ifndef RAYCASTER_ITEM_HPP_
#define RAYCASTER_ITEM_HPP_

/* ----- INCLUDEs ----- */
#include <functional>
#include <memory>
#include <string>
#include "SDL/Render/Render.hpp"
#include "SDL/TextureManager/TextureManager.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Player;

    class Item
    {
        public:
            using OnPickup = std::function<void(Player &)>;

            Item(sdl::Render &render, const std::string &iconPath, OnPickup onPickup);

            std::shared_ptr<sdl::Texture> getIcon() const;

            void pickup(Player &player);

        private:
            std::shared_ptr<sdl::Texture> _icon;
            OnPickup _onPickup;
    };
}; // namespace Raycaster

#endif
