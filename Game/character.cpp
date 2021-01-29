#pragma once

#include "character.h"

Character::Character()
{
    imageCharacter.loadFromFile("images/character.png");       //загрузка картинки
    imageCharacter.createMaskFromColor(sf::Color(56, 135, 0)); //отсекаем зелень
    textureCharacter.loadFromImage(imageCharacter);            //заряжаем текстуру картинкой
    sprite.setScale(2, 2);                                     //растягивание текстуры (с 16 px до 32 px)
    sprite.setTexture(textureCharacter);                       //заливаем текстуру спрайтом

    leftStartSpriteCoord = {0, 0};
    rightStartSpriteCoord = {0, 16};
    upStartSpriteCoord = {48, 16};
    downStartSpriteCoord = {48, 0};
    deathStartSpriteCoord = {0, 32};
}

void Character::init(int maxBombCo, int lifeCo, int bombPow, float maxSp, float bombSp)
{
    maxBombCount = maxBombCo;
    rating = 0;
    lifeCount = lifeCo;
    bombPower = bombPow;
    maxSpeed = maxSp;
    bombSpeed = bombSp;
    bonuses.clear();
}

void Character::setPos(sf::Vector2i cellNumber)
{
    hitBox.setSize({CELL_SIDE, CELL_SIDE});
    sf::Vector2f coordinate = getAbsoluteCoordinate(cellNumber.x, cellNumber.y);
    hitBox.setPosition(coordinate);
    x = coordinate.x;
    y = coordinate.y;
    dirMove = DirectionMove::DOWN;
    flagForGame = 0;
    deathTime = 4e6f;
    currentFrame = 0;
    status = LifeCycle::LIVE;
}

void Character::up()
{
    dirMove = DirectionMove::UP;
    speed = maxSpeed;
}

void Character::down()
{
    dirMove = DirectionMove::DOWN;
    speed = maxSpeed;
}

void Character::left()
{
    dirMove = DirectionMove::LEFT;
    speed = maxSpeed;
}

void Character::right()
{
    dirMove = DirectionMove::RIGHT;
    speed = maxSpeed;
}

void Character::kill()
{
    if (status != LifeCycle::LIVE)
        return;

    lifeCount -= 1;
    currentFrame = 0;
    status = LifeCycle::DEATH;

    if (bonuses.size() == 0)
        return;

    int index = getRandNumber(0, bonuses.size() - 1);
    bonusesEffect(false, bonuses[index]);
    (*buffer_bonusesForGame).push_back(bonuses[index]);
    bonuses.erase(bonuses.cbegin() + index);
}

void Character::liveCycle(float time)
{
    float timeAnim = time / 1200;
    switch (status)
    {
    case LifeCycle::LIVE:
        move(timeAnim);
        animation();
        break;
    case LifeCycle::DEATH:
        deathTime -= time;

        currentFrame += 0.005 * time / 1400;
        if (currentFrame > 7)
        {
            currentFrame = 7;
        }

        if (deathTime < 0)
            status = LifeCycle::ERASE;
        animation();
        break;
    case LifeCycle::ERASE:
        flagForGame = 2;
        break;
    }
}

void Character::move(float timeToMove)
{
    if (speed != 0)
    {
        currentFrame += 0.005 * timeToMove;
        if (currentFrame > 3)
        {
            currentFrame -= 3;
        }
    }

    float newX, newY, dnX, dnY;
    switch (dirMove)
    {
    case DirectionMove::RIGHT:
        dx = speed;
        dy = 0;
        break;
    case DirectionMove::LEFT:
        dx = -speed;
        dy = 0;
        break;
    case DirectionMove::DOWN:
        dx = 0;
        dy = speed;
        break;
    case DirectionMove::UP:
        dx = 0;
        dy = -speed;
        break;
    }
    newX = x + (dx * timeToMove);
    newY = y + (dy * timeToMove);

    if ((dx != 0) && (speed != 0))
    {
        if (((int)floor(newY) % 32) < 9)
            dnY = -0.08;

        if (((int)floor(newY) % 32) > 23)
            dnY = 0.08;

        if (!(((int)newY % 32 <= 1) || ((int)newY % 32 >= 31)))
        {
            newX = x;
            newY += dnY;
        }
    }
    if ((dy != 0) && (speed != 0))
    {
        if (((int)floor(newX) % 32) < 9)
            dnX = -0.08;

        if (((int)floor(newX) % 32) > 23)
            dnX = 0.08;

        if (!(((int)newX % 32 <= 1) || ((int)newX % 32 >= 31)))
        {
            newX += dnX;
            newY = y;
        }
    }
    x = newX;
    y = newY;
    hitBox.setPosition(x, y);
    speed = 0;

    playerInteraction();
}

void Character::animation()
{
    switch (status)
    {
    case LifeCycle::LIVE:
    {
        switch (dirMove)
        {
        case DirectionMove::RIGHT:
            sprite.setTextureRect(sf::IntRect(rightStartSpriteCoord.x + (16 * int(currentFrame)), rightStartSpriteCoord.y, 16, 16));
            break;
        case DirectionMove::LEFT:
            sprite.setTextureRect(sf::IntRect(leftStartSpriteCoord.x + (16 * int(currentFrame)), leftStartSpriteCoord.y, 16, 16));
            break;
        case DirectionMove::DOWN:
            sprite.setTextureRect(sf::IntRect(downStartSpriteCoord.x + (16 * int(currentFrame)), downStartSpriteCoord.y, 16, 16));
            break;
        case DirectionMove::UP:
            sprite.setTextureRect(sf::IntRect(upStartSpriteCoord.x + (16 * int(currentFrame)), upStartSpriteCoord.y, 16, 16));
            break;
        }
        break;
    }
    case LifeCycle::DEATH:
    {
        sprite.setTextureRect(sf::IntRect(deathStartSpriteCoord.x + (16 * int(currentFrame)), deathStartSpriteCoord.y, 16, 16));
    }
    }
    sprite.setPosition(hitBox.getPosition().x, hitBox.getPosition().y);
}

void Character::playerInteraction()
{
    const int shiftHeader = HEADER * CELL_SIDE;
    sf::Vector2i localXY = getAbsoluteCellNumber(x, y);

    for (int i = (y - shiftHeader) / CELL_SIDE; i < (y - shiftHeader + CELL_SIDE) / CELL_SIDE; i++)
        for (int j = x / CELL_SIDE; j < (x + CELL_SIDE) / CELL_SIDE; j++)
        {
            //дверь
            if (buffer_tileMap[i][j] == 'D')
            {
                if (getRelativeCellNumber(x, y) == sf::Vector2i{j, i})
                    flagForGame = 1;
            }
            //стена/ящик
            if ((buffer_tileMap[i][j] == '#') || (buffer_tileMap[i][j] == 's') || (buffer_tileMap[i][j] == '_'))
            {
                x = localXY.x * CELL_SIDE;
                y = localXY.y * CELL_SIDE;
            }
        }

    //обработка бонусов
    for (int i = 0; i < buffer_bonuses->size(); i++)
    {
        sf::Vector2i STRONGlocalXYPlayer, STRONGlocalXYBonus;
        //sf::Vector2f bonus = {(*buffer_bonuses)[i].coordXY.x, (*buffer_bonuses)[i].coordXY.y};

        if (getSTRONGCellNumber(x, y, STRONGlocalXYPlayer) && (STRONGlocalXYPlayer.x == (*buffer_bonuses)[i].createCellNumber.x) && ((STRONGlocalXYPlayer.y - HEADER) == (*buffer_bonuses)[i].createCellNumber.y))
        {
            if ((*buffer_bonuses)[i].type == BonusTypes::PYROMANCY)
            {
                flagForGame = 4;
                (*buffer_bonuses)[i].kill();
            }
            else
            {
                bonusesEffect(true, (*buffer_bonuses)[i].type);
                bonuses.push_back((*buffer_bonuses)[i].type);
                (*buffer_bonuses)[i].kill();
            }
        }
    }
}

void Character::bonusesEffect(bool isAdd, BonusTypes bonus)
{
    int sign = (isAdd ? 1 : -1);
    switch (bonus)
    {
    case BonusTypes::QUICK_WAIT_TIME:
        bombSpeed = bombSpeed - (1e6f * sign);
        break;
    case BonusTypes::INCREASE_POWER_EXPLOSION:
        bombPower = bombPower + (1 * sign);
        break;
    case BonusTypes::ADDITIONAL_BOMB:
        maxBombCount = maxBombCount + (1 * sign);
        break;
    case BonusTypes::REDUCE_POWER_EXPLOSION:
        bombPower = bombPower - (1 * sign);
        break;
    case BonusTypes::INCREASE_SPEED:
        maxSpeed = maxSpeed + (0.01 * sign);
        break;
    case BonusTypes::ADDITIONAL_LIFE:
        lifeCount = lifeCount + (1 * sign);
        break;
    }
}