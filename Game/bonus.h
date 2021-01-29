#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "common.h"

//не стал разбивать на заголовочный и реализации файлы умышленно, т.к. 1) кода мало 2) захламление файлами 3) проблема с зависимостями решена.
//так же существует праблема с файлами .cpp - их надо явно подключать в main.cpp.
class Bonus : public SimpleObject
{
public:
  BonusTypes type;

  Bonus(sf::Vector2i cellNum, BonusTypes T, sf::Texture &t) : SimpleObject(cellNum, t)
  {
    type = T;
  }
  void liveCycle(float dtime)
  {
    switch (status)
    {
    case LifeCycle::LIVE:
      animation();
      break;
    case LifeCycle::DEATH:
      status = LifeCycle::ERASE;
      break;
    case LifeCycle::ERASE:
      break;
    }
  }
  void animation()
  {
    switch (type)
    {
    case BonusTypes::QUICK_WAIT_TIME:
      sprite.setTextureRect(sf::IntRect(48, 16, 16, 16));
      break;
    case BonusTypes::INCREASE_POWER_EXPLOSION:
      sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
      break;
    case BonusTypes::ADDITIONAL_BOMB:
      sprite.setTextureRect(sf::IntRect(0, 16, 16, 16));
      break;
    case BonusTypes::REDUCE_POWER_EXPLOSION:
      sprite.setTextureRect(sf::IntRect(96, 16, 16, 16));
      break;
    case BonusTypes::INCREASE_SPEED:
      sprite.setTextureRect(sf::IntRect(32, 16, 16, 16));
      break;
    case BonusTypes::ADDITIONAL_LIFE:
      sprite.setTextureRect(sf::IntRect(128, 16, 16, 16));
      break;
    case BonusTypes::PYROMANCY:
      sprite.setTextureRect(sf::IntRect(64, 16, 16, 16));
      break;
    }
  }
  void kill()
  {
    status = LifeCycle::DEATH;
  }
};