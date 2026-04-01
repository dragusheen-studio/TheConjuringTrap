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

    bool Inventory::hasPill() const
    {
        return _pills > 0;
    }

    /* ----- FUNCTIONs ----- */
    void Inventory::gainKey()
    {
        _keys++;
    }

    void Inventory::gainPill()
    {
        _pills++;
    }

    void Inventory::useKey()
    {
        _keys--;
    }

    void Inventory::usePill()
    {
        _pills--;
    }
}; // namespace Raycaster
