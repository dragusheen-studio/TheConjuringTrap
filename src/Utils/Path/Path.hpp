/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- UTILS_PATH_HPP_ ----- */
#ifndef UTILS_PATH_HPP_
#define UTILS_PATH_HPP_

/* ----- INCLUDEs ----- */
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

/* ----- CLASS ----- */
namespace utils
{
    class Path
    {
        public:
            static void init();
            static std::string getAssetsPath();

        private:
            static std::string _assetsPath;
    };
}; // namespace utils

/* ----- UTILS_PATH_HPP_ ----- */
#endif
