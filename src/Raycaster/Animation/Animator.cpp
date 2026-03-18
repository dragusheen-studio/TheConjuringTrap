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

        int currentRow = 0;
        std::string firstAnimName = "";

        for (const std::string &animName : animationsNode->keys) {
            std::shared_ptr<yaml::Node> animNode = animationsNode->get(animName);

            _AnimationData data;
            data.row = currentRow++;
            data.maxFrames = animNode->has("frames") ? animNode->get("frames")->asInt() : _columns;
            data.speed = animNode->has("speed") ? animNode->get("speed")->asDouble() : 0.15;
            data.transition = animNode->has("transition") ? animNode->get("transition")->asString() : "";
            data.loop = animNode->has("loop") ? animNode->get("loop")->asBool() : true;

            _animations[animName] = data;
            if (firstAnimName.empty()) firstAnimName = animName;
        }

        if (!_animations.empty()) {
            if (root->has("default_animation")) {
                play(root->get("default_animation")->asString());
            } else {
                play(firstAnimName);
            }
        }
    }

    /* ----- GETTERs ----- */
    SDL_Rect Animator::getSrcRect() const
    {
        if (_currentAnim.empty()) return {0, 0, _frameWidth, _frameHeight};

        const _AnimationData &anim = _animations.at(_currentAnim);

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

        _AnimationData &anim = _animations[_currentAnim];

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
                } else if (anim.loop) {
                    _currentFrame = 0;
                } else {
                    _currentFrame = anim.maxFrames - 1;
                }
            }
        }
    }
}; // namespace Raycaster
