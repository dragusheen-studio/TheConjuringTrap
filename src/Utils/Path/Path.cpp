/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Path.hpp"

/* ----- CLASS ----- */
namespace utils
{
    /* ----- DEFAULTs ----- */
    std::string Path::_assetsPath = "./assets/";

    void Path::init()
    {
        char result[4096];
        std::string path = "";

#ifdef _WIN32
        GetModuleFileName(NULL, result, sizeof(result));
        path = std::string(result);
#else
        ssize_t count = readlink("/proc/self/exe", result, sizeof(result));
        if (count != -1) path = std::string(result, count);
#endif

        size_t lastSlash = path.find_last_of("\\/");
        if (lastSlash != std::string::npos) _assetsPath = path.substr(0, lastSlash + 1) + "assets/";
    }

    /* ----- GETTERs ----- */
    std::string Path::getAssetsPath()
    {
        return _assetsPath;
    }
}; // namespace utils
