/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_AUDIO_MANAGER_HPP_ ----- */
#ifndef GRADE_DE_AUDIO_MANAGER_HPP_
#define GRADE_DE_AUDIO_MANAGER_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL_mixer.h>
#include <memory>
#include <string>
#include <unordered_map>
#include "SDL/Error/Error.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class AudioManager
    {
        public:
            static AudioManager &get();
            ~AudioManager();

            void playMusic(const std::string &path);
            void stopMusic();

            void playSound(const std::string &path, int volumeAttenuation = -1);

            void setVolume(int volume);
            int getVolume();

        private:
            int _volume;
            std::string _prefix;
            std::string _musicPrefix;
            std::string _soundPrefix;
            std::unordered_map<std::string, std::shared_ptr<Mix_Music>> _musics;
            std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> _sounds;

            AudioManager();
    };
}; // namespace sdl

/* ----- GRADE_DE_AUDIO_MANAGER_HPP_ ----- */
#endif
