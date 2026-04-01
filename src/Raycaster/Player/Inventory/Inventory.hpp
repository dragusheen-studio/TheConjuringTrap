/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_INVENTORY_HPP_ ----- */
#ifndef RAYCASTER_INVENTORY_HPP_
#define RAYCASTER_INVENTORY_HPP_

/* ----- INCLUDEs ----- */

/* ----- CLASS ----- */
namespace Raycaster
{
    class Inventory
    {
        public:
            Inventory() = default;
            ~Inventory() = default;

            bool hasKey() const;
            bool hasPill() const;

            void gainKey();
            void gainPill();

            void useKey();
            void usePill();

        private:
            int _keys = 0;
            int _pills = 0;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_INVENTORY_HPP_ ----- */
#endif
