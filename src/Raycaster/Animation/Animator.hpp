/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- RAYCASTER_ANIMATOR_HPP_ ----- */
#ifndef RAYCASTER_ANIMATOR_HPP_
#define RAYCASTER_ANIMATOR_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <unordered_map>
#include "SDL/Render/Render.hpp"
#include "SDL/Texture/Texture.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    class Animator
    {
        public:
            Animator(const std::string &yamlPath, sdl::Render &render);
            ~Animator() = default;

            void play(const std::string &name);
            void update(double deltaTime);

            SDL_Rect getSrcRect() const;
            std::shared_ptr<sdl::Texture> getTexture() const;
            std::string getCurrentAnimation() const;

        private:
            struct _AnimationData {
                    int row;
                    int maxFrames;
                    double speed;
                    std::string transition;
                    bool loop;
            };

            std::shared_ptr<sdl::Texture> _texture;
            std::unordered_map<std::string, _AnimationData> _animations;
            std::string _currentAnim = "";

            int _columns;
            int _rows;
            int _frameWidth;
            int _frameHeight;

            int _currentFrame = 0;
            double _timer = 0.0;
    };
}; // namespace Raycaster

/* ----- RAYCASTER_ANIMATOR_HPP_ ----- */
#endif
