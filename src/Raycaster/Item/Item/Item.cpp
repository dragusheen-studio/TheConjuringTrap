/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Item.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Item::Item(sdl::Render &render, const std::string &iconPath, OnPickup onPickup)
        : _onPickup(onPickup)
    {
        _icon = sdl::TextureManager::get().get(render, iconPath);
    }

    /* ----- FUNCTIONs ----- */
    void Item::pickup(Player &player)
    {
        _onPickup(player);
    }

    std::shared_ptr<sdl::Texture> Item::getIcon() const
    {
        return _icon;
    }
}; // namespace Raycaster
