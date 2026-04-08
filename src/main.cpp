/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <iostream>
#include "SDL/Error/Error.hpp"
#include "Raycaster/Engine/Engine.hpp"
#include "Utils/Path/Path.hpp"

/* ----- MAIN ----- */
int main(int argc, char *argv[])
{
    try {
        utils::Path::init();
        Raycaster::Engine engine;
        engine.run();
    } catch (sdl::Error &e) {
        e.read();
    } catch (std::exception &e) {
        std::cerr << "Error" << std::endl;
        std::cerr << ">> " << e.what() << std::endl;
    }

    return 0;
}
