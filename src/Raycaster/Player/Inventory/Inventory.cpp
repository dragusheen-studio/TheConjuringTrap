/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Inventory.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- GETTERs ----- */
    bool Inventory::hasKey() const
    {
        return _keys > 0;
    }

    /* ----- FUNCTIONs ----- */
    void Inventory::gainKey()
    {
        _keys++;
    }

    void Inventory::useKey()
    {
        _keys--;
    }

}; // namespace Raycaster
