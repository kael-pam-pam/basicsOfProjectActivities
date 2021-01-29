#pragma once

#include <SFML/Graphics.hpp>
#include "common.h"
#include "constants.h"

class BombExplosion : public SimpleObject
{
    sf::Vector2i centerStartSpriteCoord, //начало спрайтов: эпицентр взрыва
        middleHorStartSpriteCoord,       //начало спрайтов: середина взрыва (горизонтальн.)
        endHorStartSpriteCoord,          //начало спрайтов: край взрыва (горизонтальн.)
        middleVerStartSpriteCoord,       //начало спрайтов: середина взрыва (верт.)
        endVerStartSpriteCoord;          //начало спрайтов: край взрыва (верт.)
  public:
    ExplosionPart type;    //тип фреймя: эпицентр, середина и конец
    bool isStartExplosion; //влияет на формирование sprite: true - начало взрыва, false - затухание
    float explosionTime;   //время анимации взрыва

    BombExplosion(sf::Vector2i cellNum, ExplosionPart part, sf::Texture &t) : SimpleObject(cellNum, t)
    {
        explosionTime = 1e6f; //1 сек.
        isStartExplosion = true;
        type = part;
        centerStartSpriteCoord = {0, 32};
        middleHorStartSpriteCoord = {0, 16};
        endHorStartSpriteCoord = {0, 0};
        middleVerStartSpriteCoord = {0, 64};
        endVerStartSpriteCoord = {0, 48};
    }
    void liveCycle(float dtime)
    {
        const int maxSpriteCount = 4;
        switch (status)
        {
        case LifeCycle::LIVE:
            if (isStartExplosion)
            {
                currentFrame += 0.005 * (dtime / 600);
                if (currentFrame > maxSpriteCount)
                    isStartExplosion = false;
            }
            else
            {
                currentFrame -= 0.005 * (dtime / 600);
            }
            explosionTime -= dtime;
            if (explosionTime < 0)
            {
                status = LifeCycle::ERASE;
            }
            animation();
            break;
        case LifeCycle::ERASE:
            break;
        }
    }
    void animation()
    {
        switch (type)
        {
        case ExplosionPart::CENTER:
            sprite.setTextureRect(sf::IntRect(centerStartSpriteCoord.x + (16 * int(currentFrame)), centerStartSpriteCoord.y, 16, 16));
            break;
        case ExplosionPart::MIDDLE_HORISONTAL:
            sprite.setTextureRect(sf::IntRect(middleHorStartSpriteCoord.x + (16 * int(currentFrame)), middleHorStartSpriteCoord.y, 16, 16));
            break;
        case ExplosionPart::RIGHT_END_HORISONTAL:
            sprite.setTextureRect(sf::IntRect(endHorStartSpriteCoord.x + (16 * int(currentFrame + 1)), endHorStartSpriteCoord.y, -16, 16));
            break;
        case ExplosionPart::LEFT_END_HORISONTAL:
            sprite.setTextureRect(sf::IntRect(endHorStartSpriteCoord.x + (16 * int(currentFrame)), endHorStartSpriteCoord.y, 16, 16));
            break;
        case ExplosionPart::MIDDLE_VERTICAL:
            sprite.setTextureRect(sf::IntRect(middleVerStartSpriteCoord.x + (16 * int(currentFrame)), middleVerStartSpriteCoord.y, 16, 16));
            break;
        case ExplosionPart::DOWN_END_VERTICAL:
            sprite.setTextureRect(sf::IntRect(endVerStartSpriteCoord.x + (16 * int(currentFrame)), endVerStartSpriteCoord.y + 16, 16, -16));
            break;
        case ExplosionPart::UP_END_VERTICAL:
            sprite.setTextureRect(sf::IntRect(endVerStartSpriteCoord.x + (16 * int(currentFrame)), endVerStartSpriteCoord.y, 16, 16));
            break;
        }
    }
};
