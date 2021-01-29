#pragma once

#include <SFML/Graphics.hpp>
#include "common.h"
#include "constants.h"

class Character
{
    sf::Image imageCharacter;          //объект изображения
    sf::Texture textureCharacter;      //текстура
    sf::Vector2i leftStartSpriteCoord, //начало спрайтов: движение влево
        rightStartSpriteCoord,         //начало спрайтов: движение вправо
        upStartSpriteCoord,            //начало спрайтов: движение вверх
        downStartSpriteCoord,          //начало спрайтов: движение вниз
        deathStartSpriteCoord;         //начало спрайтов: смерть

  public:
    float x, y, dx, dy, speed = 0;
    DirectionMove dirMove; //направление движения

    sf::RectangleShape hitBox; //квадрат
    float currentFrame;

    float deathTime; //время анимации смерти

    int maxBombCount;                //количество бомб
    int rating;                      //набранные очки
    int lifeCount;                   //жизни
    int bombPower;                   //сила/длина взрыва
    float maxSpeed;                  //скорость передвижения
    float bombSpeed;                 //задержка бомбы перед детонацией
    std::vector<BonusTypes> bonuses; //бонусы

    int flagForGame;

    sf::Sprite sprite; //спрайт
    LifeCycle status;  //жизненный статус

    Character();
    void init(int maxBombCo, int lifeCo, int bombPow, float maxSp, float bombSp);
    void setPos(sf::Vector2i cellNumber);
    void liveCycle(float time);
    void move(float timeToMove);
    void animation();
    void playerInteraction();
    void up();
    void down();
    void left();
    void right();
    void kill();
    void bonusesEffect(bool isAdd, BonusTypes bonus);
};
