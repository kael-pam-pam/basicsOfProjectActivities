#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "common.h"
#include "constants.h"

class ExplosionWall : public SimpleObject
{
    sf::Vector2i startSpriteCoord; //начало спрайтов
    float animationTime;           //время на анимацию

  public:
    ExplosionWall(sf::Vector2i cellNum, sf::Texture &t) : SimpleObject(cellNum, t)
    {
        animationTime = 1e6f;
        startSpriteCoord = {32, 0};
    }

    void liveCycle(float dtime)
    {
        const int maxSpriteCount = 5;
        switch (status)
        {
        case LifeCycle::LIVE:
            currentFrame += 0.005 * (dtime / 800);
            if (currentFrame > maxSpriteCount)
            {
                currentFrame = maxSpriteCount;
            }
            animationTime -= dtime;
            if (animationTime < 0)
            {
                status = LifeCycle::DEATH;
            }
            animation();
            break;
        case LifeCycle::DEATH:
            status = LifeCycle::ERASE;
        case LifeCycle::ERASE:
            break;
        }
    }

    void animation()
    {
        switch (status)
        {
        case LifeCycle::LIVE:
            sprite.setTextureRect(sf::IntRect(startSpriteCoord.x + (16 * int(currentFrame)), startSpriteCoord.y, 16, 16));
            break;
        case LifeCycle::DEATH:
            break;
        case LifeCycle::ERASE:
            break;
        }
    }
};