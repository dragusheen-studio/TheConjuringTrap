/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Keyboard.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    Keyboard::Keyboard()
    {
        _oldKeyboardState.resize(SDL_NUM_SCANCODES, 0);
        clear();
    }

    /* ----- FUNCTIONs ----- */
    void Keyboard::bindOnPressed(SDL_Scancode key, std::function<void(double)> callback)
    {
        _pressed.push_back(std::make_pair(key, callback));
    }

    void Keyboard::bindOnReleased(SDL_Scancode key, std::function<void(double)> callback)
    {
        _released.push_back(std::make_pair(key, callback));
    }

    void Keyboard::unbindOnPressed(SDL_Scancode key)
    {
        for (auto it = _pressed.begin(); it != _pressed.end();) {
            if (it->first == key)
                it = _pressed.erase(it);
            else
                ++it;
        }
    }

    void Keyboard::unbindOnReleased(SDL_Scancode key)
    {
        for (auto it = _released.begin(); it != _released.end();) {
            if (it->first == key)
                it = _released.erase(it);
            else
                ++it;
        }
    }

    void Keyboard::update(double deltaTime)
    {
        const Uint8 *currentKeyboardState = SDL_GetKeyboardState(NULL);

        for (auto it = _released.begin(); it != _released.end(); ++it)
            if (currentKeyboardState[it->first] == 0 && _oldKeyboardState[it->first] == 1)
                it->second(deltaTime);

        for (auto it = _pressed.begin(); it != _pressed.end(); ++it)
            if (currentKeyboardState[it->first] == 1)
                it->second(deltaTime);

        std::copy(currentKeyboardState, currentKeyboardState + SDL_NUM_SCANCODES, _oldKeyboardState.begin());
    }

    void Keyboard::clear()
    {
        _pressed.clear();
        _released.clear();
    }
}; // namespace sdl
