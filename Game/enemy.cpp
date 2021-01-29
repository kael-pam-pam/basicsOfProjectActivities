#pragma once

#include "enemy.h"

Enemy::Enemy(sf::Vector2i cellNumber, int typeEnemy, sf::Texture &t)
{
    type = typeEnemy;
    currentFrame = 0;
    status = LifeCycle::LIVE;
    initWithType();
    dirMove = static_cast<DirectionMove>(getRandNumber(0, 3));
    upDownStartSpriteCoord = (getRandNumber(0, 3) == 0) ? rightStartSpriteCoord : leftStartSpriteCoord;
    texture = &t;
    sprite.setScale(2, 2);       //растягивание текстуры (с 16 px до 32 px)
    sprite.setTexture(*texture); //заливаем спрайт текстурой
    hitBox.setSize({CELL_SIDE, CELL_SIDE});
    sf::Vector2f coordinate = getAbsoluteCoordinate(cellNumber.x, cellNumber.y);
    hitBox.setPosition(coordinate);
}

void Enemy::initWithType()
{
    switch (type)
    {
    case 0:
        speed = 0.07;
        rating = 100;
        maxTimeToThink = 10e6f;
        leftStartSpriteCoord = {48, 0};
        rightStartSpriteCoord = {0, 0};
        deathStartSpriteCoord = {96, 0};
        break;
    case 1:
        speed = 0.08;
        rating = 200;
        maxTimeToThink = 9e6f;
        leftStartSpriteCoord = {48, 16};
        rightStartSpriteCoord = {0, 16};
        deathStartSpriteCoord = {96, 16};
        break;
    case 2:
        speed = 0.09;
        rating = 250;
        maxTimeToThink = 8e6f;
        leftStartSpriteCoord = {48, 32};
        rightStartSpriteCoord = {0, 32};
        deathStartSpriteCoord = {96, 32};
        break;
    case 3:
        speed = 0.095;
        rating = 300;
        maxTimeToThink = 7e6f;
        leftStartSpriteCoord = {48, 48};
        rightStartSpriteCoord = {0, 48};
        deathStartSpriteCoord = {96, 48};
        break;
    case 4:
        speed = 0.1;
        rating = 400;
        maxTimeToThink = 7e6f;
        leftStartSpriteCoord = {48, 64};
        rightStartSpriteCoord = {0, 64};
        deathStartSpriteCoord = {96, 64};
        break;
    case 5:
        speed = 0.1;
        rating = 450;
        maxTimeToThink = 6e6f;
        leftStartSpriteCoord = {48, 80};
        rightStartSpriteCoord = {0, 80};
        deathStartSpriteCoord = {96, 80};
        break;
    case 6:
        speed = 0.11;
        rating = 500;
        maxTimeToThink = 6e6f;
        leftStartSpriteCoord = {48, 96};
        rightStartSpriteCoord = {0, 96};
        deathStartSpriteCoord = {96, 96};
        break;
    case 7:
        speed = 0.12;
        rating = 600;
        maxTimeToThink = 5e6f;
        leftStartSpriteCoord = {48, 112};
        rightStartSpriteCoord = {0, 112};
        deathStartSpriteCoord = {96, 112};
        break;
    }
    timeToThink = maxTimeToThink;
}

void Enemy::liveCycle(float time)
{
    float timeAnim = time / SPEED_ANIMATION;
    currentFrame += 0.005 * timeAnim;
    switch (status)
    {
    case LifeCycle::LIVE:
        timeToThink -= time;
        if (currentFrame > 3)
            currentFrame -= 3;
        move(timeAnim);
        animation();
        break;
    case LifeCycle::DEATH:
        deathTime -= time;
        if (deathTime < 0)
            status = LifeCycle::ERASE;
        animation();
        break;
    case LifeCycle::ERASE:
        break;
    }
}

void Enemy::move(float timeToMove)
{
    float x = hitBox.getPosition().x, y = hitBox.getPosition().y;
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
    hitBox.setPosition(x + dx * timeToMove, y + dy * timeToMove);
    enemyInteraction();
}

void Enemy::animation()
{
    switch (status)
    {
    case LifeCycle::LIVE:
        animationMove();
        break;
    case LifeCycle::DEATH:
        animationDeath();
        break;
    }
}

void Enemy::animationMove()
{
    switch (dirMove)
    {
    case DirectionMove::RIGHT:
        sprite.setTextureRect(sf::IntRect(rightStartSpriteCoord.x + (16 * int(currentFrame)), rightStartSpriteCoord.y, 16, 16));
        upDownStartSpriteCoord = rightStartSpriteCoord;
        break;
    case DirectionMove::LEFT:
        sprite.setTextureRect(sf::IntRect(leftStartSpriteCoord.x + (16 * int(currentFrame)), leftStartSpriteCoord.y, 16, 16));
        upDownStartSpriteCoord = leftStartSpriteCoord;
        break;
    case DirectionMove::UP:
    case DirectionMove::DOWN:
        sprite.setTextureRect(sf::IntRect(upDownStartSpriteCoord.x + (16 * int(currentFrame)), upDownStartSpriteCoord.y, 16, 16));
        break;
    }
    sprite.setPosition(hitBox.getPosition());
}

void Enemy::animationDeath()
{
    sprite.setTextureRect(sf::IntRect(deathStartSpriteCoord.x + (16 * int(currentFrame)), deathStartSpriteCoord.y, 16, 16));
    sprite.setPosition(hitBox.getPosition().x, hitBox.getPosition().y);
}

void Enemy::enemyInteraction()
{
    const int shiftHeader = HEADER * CELL_SIDE;
    float x = hitBox.getPosition().x, y = hitBox.getPosition().y;
    sf::Vector2i localXY = getAbsoluteCellNumber(x, y);

    for (int i = (y - shiftHeader) / CELL_SIDE; i < (y - shiftHeader + CELL_SIDE) / CELL_SIDE; i++)
        for (int j = x / CELL_SIDE; j < (x + CELL_SIDE) / CELL_SIDE; j++)
        {
            //встреча с препядствием
            //стена/ящик
            if ((buffer_tileMap[i][j] == '#') || (buffer_tileMap[i][j] == 's') || (buffer_tileMap[i][j] == '_'))
            {
                x = localXY.x * CELL_SIDE;
                y = localXY.y * CELL_SIDE;
                hitBox.setPosition({x, y});
                //dirMove = getMoveBackDirection();
                dirMove = getFreeRandomDirection();
            }
            else if (timeToThink < 0)
            {
                std::vector<DirectionMove> moves = getFreeDirections();
                if (moves.size() > 2)
                {
                    dirMove = moves[getRandNumber(0, moves.size() - 1)];
                    timeToThink = maxTimeToThink;
                    std::cout << "change " << x << ":" << y << std::endl;
                }
            }
        }
}

DirectionMove Enemy::getMoveBackDirection()
{
    switch (dirMove)
    {
    case DirectionMove::RIGHT:
        return DirectionMove::LEFT;
    case DirectionMove::LEFT:
        return DirectionMove::RIGHT;
    case DirectionMove::DOWN:
        return DirectionMove::UP;
    case DirectionMove::UP:
        return DirectionMove::DOWN;
    }
}

std::vector<DirectionMove> Enemy::getFreeDirections()
{
    std::vector<DirectionMove> moves;
    sf::Vector2i STRONGlocalXY;
    float x = hitBox.getPosition().x, y = hitBox.getPosition().y;
    if (getSTRONGCellNumber(x, y, STRONGlocalXY))
    {
        STRONGlocalXY.y -= HEADER;
        if (buffer_tileMap[STRONGlocalXY.y][STRONGlocalXY.x + 1] == ' ')
            moves.push_back(DirectionMove::RIGHT);
        if (buffer_tileMap[STRONGlocalXY.y][STRONGlocalXY.x - 1] == ' ')
            moves.push_back(DirectionMove::LEFT);
        if (buffer_tileMap[STRONGlocalXY.y - 1][STRONGlocalXY.x] == ' ')
            moves.push_back(DirectionMove::UP);
        if (buffer_tileMap[STRONGlocalXY.y + 1][STRONGlocalXY.x] == ' ')
            moves.push_back(DirectionMove::DOWN);
        return moves;
    }
    else
    {
        moves.push_back(dirMove);
        return moves;
    }
}

DirectionMove Enemy::getFreeRandomDirection()
{
    std::vector<DirectionMove> moves = getFreeDirections();
    return moves[getRandNumber(0, moves.size() - 1)];
}

void Enemy::kill()
{
    status = LifeCycle::DEATH;
    currentFrame = 0;
    deathTime = 1e6f;
    speed = 0;
}