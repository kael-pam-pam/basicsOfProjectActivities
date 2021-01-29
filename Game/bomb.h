#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "common.h"
#include "constants.h"

class Bomb : public SimpleObject
{
  sf::Vector2i startSpriteCoord; //начало спрайтов: бомба
  float waitTime;                //время до детонации
public:
  bool likeBarrier; //служит препядствием для игрока и врагов

  Bomb(sf::Vector2i cellNum, float waitT, sf::Texture &t) : SimpleObject(cellNum, t)
  {
    waitTime = waitT;
    startSpriteCoord = {0, 80};
    likeBarrier = false;
  }

  void liveCycle(float dtime)
  {
    const int maxSpriteCount = 3;
    switch (status)
    {
    case LifeCycle::LIVE:
      currentFrame += 0.005 * (dtime / 800);
      if (currentFrame > maxSpriteCount)
      {
        currentFrame -= maxSpriteCount;
      }
      waitTime -= dtime;
      if (waitTime < 0)
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

  void kill()
  {
    status = LifeCycle::DEATH;
  }

  void setWaitTime(float newTime)
  {
    waitTime = newTime;
  }
};
