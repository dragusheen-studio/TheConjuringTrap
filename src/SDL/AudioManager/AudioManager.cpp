/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./AudioManager.hpp"
#include <iostream>

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    AudioManager::AudioManager()
        : _prefix("./assets/audio/"), _musicPrefix("music/"), _soundPrefix("sound/"), _volume(128)
    {
        int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
        if ((Mix_Init(flags) & flags) != flags)
            throw Error(std::string("Attention: Tous les décodeurs audio n'ont pas pu charger: ") + Mix_GetError(), "AudioManager::init");

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            throw Error(std::string("Erreur initialisation SDL_mixer: ") + Mix_GetError(), "AudioManager::init");
    }

    AudioManager::~AudioManager()
    {
        _musics.clear();
        _sounds.clear();

        Mix_CloseAudio();
        Mix_Quit();
    }

    AudioManager &AudioManager::get()
    {
        static AudioManager instance;
        return instance;
    }

    /* ----- GETTERs ----- */
    int AudioManager::getVolume()
    {
        return _volume;
    }

    /* ----- SETTERs ----- */
    void AudioManager::setVolume(int volume)
    {
        _volume = volume;
        Mix_VolumeMusic(_volume);
    }

    /* ----- FUNCTIONs ----- */
    void AudioManager::playMusic(const std::string &path)
    {
        const std::string finalPath = _prefix + _musicPrefix + path;

        if (_musics.find(finalPath) == _musics.end()) {
            Mix_Music *raw = Mix_LoadMUS(finalPath.c_str());
            if (!raw) throw Error(std::string("Erreur chargement musique: ") + finalPath, "AudioManager::playMusic");
            _musics[finalPath] = std::shared_ptr<Mix_Music>(raw, Mix_FreeMusic);
        }

        Mix_VolumeMusic(_volume);
        Mix_PlayMusic(_musics[finalPath].get(), -1);
    }

    void AudioManager::stopMusic()
    {
        Mix_HaltMusic();
    }

    void AudioManager::playSound(const std::string &path)
    {
        const std::string finalPath = _prefix + _soundPrefix + path;

        if (_sounds.find(finalPath) == _sounds.end()) {
            Mix_Chunk *raw = Mix_LoadWAV(finalPath.c_str());
            if (!raw) throw Error(std::string("Erreur chargement son: ") + finalPath, "AudioManager::playSound");
            _sounds[finalPath] = std::shared_ptr<Mix_Chunk>(raw, Mix_FreeChunk);
        }

        Mix_VolumeChunk(_sounds[finalPath].get(), _volume);
        Mix_PlayChannel(-1, _sounds[finalPath].get(), 0);
    }
}; // namespace sdl
