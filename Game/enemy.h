#pragma once

#include <SFML/Graphics.hpp>
#include "common.h"
#include "constants.h"

class Enemy
{
    sf::Texture *texture;              //текстура
    sf::Vector2i leftStartSpriteCoord, //начало спрайтов: движение влево
        rightStartSpriteCoord,         //начало спрайтов: движение вправо
        deathStartSpriteCoord,         //начало спрайтов: смерть
        upDownStartSpriteCoord;        //начало спрайтов предущей анимации

  public:
    float dx, dy, speed;               //смещение по осям и скорость
    DirectionMove dirMove;             //направление движения
    sf::RectangleShape hitBox;         //"глобус"
    float currentFrame;                //для высчитывания текущего спрайта
    float deathTime;                   //время анимации смерти
    float maxTimeToThink, timeToThink; //время "на подумать"

    int type;          //тип врага
    sf::Sprite sprite; //спрайт
    LifeCycle status;  //жизненный статус
    int rating;        //даваемые очки за уничтожение

    Enemy(sf::Vector2i cellNumber, int T, sf::Texture &t);
    void initWithType();
    void liveCycle(float time);
    void move(float timeToMove);
    void animation();
    void animationMove();
    void animationDeath();
    void enemyInteraction();
    DirectionMove getMoveBackDirection();
    std::vector<DirectionMove> getFreeDirections();
    DirectionMove getFreeRandomDirection();
    void kill();
};