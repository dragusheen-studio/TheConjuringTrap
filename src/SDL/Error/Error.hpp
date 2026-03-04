/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_ERROR_HPP_ ----- */
#ifndef GRADE_DE_ERROR_HPP_
#define GRADE_DE_ERROR_HPP_

/* ----- INCLUDEs ----- */
#include <exception>
#include <iostream>
#include <string>

/* ----- CLASS ----- */
namespace sdl
{
    class Error : public std::exception
    {
        public:
            Error(std::string const &what, std::string const &where = "Unknown");
            ~Error() = default;

            const char *what() const noexcept override;
            const char *where() const noexcept;

            void read() const noexcept;

        private:
            std::string _what;
            std::string _where;
    };
}; // namespace sdl

/* ----- GRADE_DE_ERROR_HPP_ ----- */
#endif
