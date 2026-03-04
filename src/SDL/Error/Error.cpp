/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Error.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    Error::Error(std::string const &what, std::string const &where)
    {
        _what = what;
        _where = where;
    }

    /* ----- FUNCTIONs ----- */
    const char *Error::what() const noexcept
    {
        return _what.c_str();
    }

    const char *Error::where() const noexcept
    {
        return _where.c_str();
    }

    void Error::read() const noexcept
    {
        std::cerr << "SDL Error: " << _what << std::endl;
        std::cerr << ">> " << _where << std::endl;
    }
}; // namespace sdl
