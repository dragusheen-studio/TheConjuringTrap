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

            void gainKey();
            void useKey();

        private:
            int _keys = 0;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_INVENTORY_HPP_ ----- */
#endif
