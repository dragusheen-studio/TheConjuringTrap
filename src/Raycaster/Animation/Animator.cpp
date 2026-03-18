/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Animator.hpp"
#include <iostream>
#include "SDL/TextureManager/TextureManager.hpp"
#include "Yaml/Parser/Parser.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Animator::Animator(const std::string &yamlPath, sdl::Render &render)
    {
        yaml::Parser config = yaml::Parser::load(yamlPath);
        std::shared_ptr<yaml::Node> root = config.getRoot();

        std::string texturePath = root->get("texture")->asString();
        _texture = sdl::TextureManager::get().get(render, texturePath);

        _columns = root->get("grid")->get("columns")->asInt();
        _rows = root->get("grid")->get("rows")->asInt();

        _frameWidth = _texture->getWidth() / _columns;
        _frameHeight = _texture->getHeight() / _rows;

        std::shared_ptr<yaml::Node> animationsNode = root->get("animations");
        for (auto const &[animName, animNode] : animationsNode->children) {
            AnimationData data;
            data.row = animNode->get("row")->asInt();
            data.maxFrames = animNode->get("frames")->asInt();
            data.speed = animNode->get("speed")->asDouble();

            if (animNode->has("transition"))
                data.transition = animNode->get("transition")->asString();
            else
                data.transition = "";

            _animations[animName] = data;
        }

        if (!_animations.empty()) {
            if (_animations.find("idle") != _animations.end())
                play("idle");
            else
                play(_animations.begin()->first);
        }
    }

    /* ----- FUNCTIONs ----- */
    void Animator::play(const std::string &name)
    {
        if (_animations.find(name) == _animations.end() || _currentAnim == name) return;

        _currentAnim = name;
        _currentFrame = 0;
        _timer = 0.0;
    }

    void Animator::update(double deltaTime)
    {
        if (_currentAnim.empty()) return;

        AnimationData &anim = _animations[_currentAnim];

        if (anim.speed <= 0.0) return;

        _timer += deltaTime;

        if (_timer >= anim.speed) {
            _timer -= anim.speed;
            _currentFrame++;

            if (_currentFrame >= anim.maxFrames) {
                if (!anim.transition.empty()) {
                    std::string nextAnim = anim.transition;
                    _currentAnim = "";
                    play(nextAnim);
                } else {
                    _currentFrame = 0;
                }
            }
        }
    }

    /* ----- GETTERs ----- */
    SDL_Rect Animator::getSrcRect() const
    {
        if (_currentAnim.empty()) return {0, 0, _frameWidth, _frameHeight};

        const AnimationData &anim = _animations.at(_currentAnim);

        int x = _currentFrame * _frameWidth;
        int y = anim.row * _frameHeight;

        return {x, y, _frameWidth, _frameHeight};
    }

    std::shared_ptr<sdl::Texture> Animator::getTexture() const
    {
        return _texture;
    }

    std::string Animator::getCurrentAnimation() const
    {
        return _currentAnim;
    }

}; // namespace Raycaster
