#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../common.h"
#include "../constants.h"
#include "../character.h"
#include "../lvl.h"
#include <iostream>

void dropBomb(Game &g)
{
    if (g.lvl->bombs.size() >= g.p->maxBombCount)
    {
        return;
    }

    //в одну ячейку одну бомбу
    sf::Vector2i currentCellNumber = getRelativeCellNumber(g.p->x, g.p->y);
    if (g.lvl->tileMap[currentCellNumber.y][currentCellNumber.x] != ' ')
    {
        return;
    }

    for (int i = 0; i < g.lvl->bombs.size(); i++)
    {
        if (currentCellNumber == g.lvl->bombs[i].createCellNumber)
        {
            return;
        }
    }
    g.lvl->bombs.push_back(Bomb(currentCellNumber, g.p->bombSpeed, g.lvl->textureExplosion));
}

void levelKeyPressedHandle(Game &g)
{
    //движение персонажа
    if (g.p->status != LifeCycle::LIVE)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        g.p->left();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        g.p->right();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        g.p->up();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        g.p->down();
    }
}

void drawMap(sf::RenderWindow &window, Game &g)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            switch (g.lvl->tileMap[i][j])
            {
            case ' ':
            case '_':
                g.lvl->sprite.setTextureRect(sf::IntRect(0, 32, 16, 16));
                break;
            case '#':
                g.lvl->sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
                break;
            case 's':
                g.lvl->sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
                break;
            case 'D':
                g.lvl->sprite.setTextureRect(sf::IntRect(128, 0, 16, 16));
                break;
            }
            g.lvl->sprite.setPosition(j * CELL_SIDE, (i + HEADER) * CELL_SIDE);
            window.draw(g.lvl->sprite);
        }
    }
}

void drawBonusesInfo(sf::RenderWindow &window, Game &g)
{
    int maxVisibleBonusesCount = 17;
    //собранные бонусы
    for (int i = 0; i < g.p->bonuses.size(); i++)
    {
        if (i > maxVisibleBonusesCount)
        {
            break;
        }
        Bonus characterBonus = Bonus(sf::Vector2i{6 + (i % 9), -1 - (i / 9)}, g.p->bonuses[i], g.lvl->textureField);
        characterBonus.liveCycle(0);
        window.draw(characterBonus.sprite);
    }
    //оставшиеся бонусы
    for (int i = 0; i < (*buffer_bonusesForGame).size(); i++)
    {
        if (i > maxVisibleBonusesCount)
        {
            break;
        }
        Bonus remaindedBonus = Bonus(sf::Vector2i{17 + (i % 9), -1 - (i / 9)}, (*buffer_bonusesForGame)[i], g.lvl->textureField);
        remaindedBonus.liveCycle(0);
        window.draw(remaindedBonus.sprite);
    }
}

void drawHeader(sf::RenderWindow &window, Game &g)
{
    drawBonusesInfo(window, g);

    const int paddingTop = 10, paddingLeftRight = 20;
    sf::Text timeCaption, userRatingCaption, lifesCaption;

    timeCaption = sf::Text("Time " + std::to_string(static_cast<int>(g.lvl->timeRemaind / 1e6f)), g.gameFont, MENU_FONT_SIZE);
    timeCaption.setColor(MENU_FONT_COLOR);
    timeCaption.setStyle(sf::Text::Bold);
    timeCaption.setPosition(paddingLeftRight, paddingTop);
    window.draw(timeCaption);

    userRatingCaption = sf::Text(std::to_string(g.p->rating), g.gameFont, MENU_FONT_SIZE);
    userRatingCaption.setColor(MENU_FONT_COLOR);
    userRatingCaption.setStyle(sf::Text::Bold);
    userRatingCaption.setOrigin(userRatingCaption.getLocalBounds().width / 2, 0);
    userRatingCaption.setPosition(window.getSize().x / 2, paddingTop);
    window.draw(userRatingCaption);

    lifesCaption = sf::Text("Lifes " + std::to_string(g.p->lifeCount), g.gameFont, MENU_FONT_SIZE);
    lifesCaption.setColor(MENU_FONT_COLOR);
    lifesCaption.setStyle(sf::Text::Bold);
    lifesCaption.setPosition(window.getSize().x - lifesCaption.getLocalBounds().width - paddingLeftRight, paddingTop);
    window.draw(lifesCaption);
}

void drawPlayer(sf::RenderWindow &window, Game &g)
{
    g.p->liveCycle(g.dtime);
    window.draw(g.p->sprite);
}

bool isDestroyedBonus(Game &g, sf::Vector2i cellNum, ExplosionPart endPart)
{
    for (int k = 0; k < g.lvl->bonuses.size(); k++)
    {
        if (g.lvl->bonuses[k].createCellNumber == cellNum)
        {
            g.bonusesForGame.push_back(g.lvl->bonuses[k].type);
            g.lvl->bonuses[k].kill();
            g.lvl->explosions.push_back(BombExplosion(cellNum, endPart, g.lvl->textureExplosion));
            return true;
        }
    }
    return false;
}

bool isDestroyedBomb(Game &g, sf::Vector2i cellNum)
{
    for (int k = 0; k < g.lvl->bombs.size(); k++)
    {
        if (g.lvl->bombs[k].createCellNumber == cellNum)
        {
            g.lvl->bombs[k].setWaitTime(3e5f);
            return true;
        }
    }
    return false;
}

void createExplosions(sf::Vector2i centerCellNumber, Game &g)
{
    g.lvl->explosions.push_back(BombExplosion(centerCellNumber, ExplosionPart::CENTER, g.lvl->textureExplosion));

    ExplosionPart typeExpl, middlePart, endPart;
    sf::Uint32 *cell;
    sf::Vector2i cellShift;
    int sides = 4;

    for (int j = 0; j < sides; j++)
    {
        switch (j)
        {
        case 0:
            cellShift = {-1, 0};
            middlePart = ExplosionPart::MIDDLE_HORISONTAL;
            endPart = ExplosionPart::LEFT_END_HORISONTAL;
            break;
        case 1:
            cellShift = {1, 0};
            middlePart = ExplosionPart::MIDDLE_HORISONTAL;
            endPart = ExplosionPart::RIGHT_END_HORISONTAL;
            break;
        case 2:
            cellShift = {0, -1};
            middlePart = ExplosionPart::MIDDLE_VERTICAL;
            endPart = ExplosionPart::UP_END_VERTICAL;
            break;
        case 3:
            cellShift = {0, 1};
            middlePart = ExplosionPart::MIDDLE_VERTICAL;
            endPart = ExplosionPart::DOWN_END_VERTICAL;
            break;
        }
        sf::Vector2i cellNumber;

        for (int i = 1; i <= g.p->bombPower; i++)
        {
            cellNumber = {centerCellNumber.x + (cellShift.x * i), centerCellNumber.y + (cellShift.y * i)};
            cell = &g.lvl->tileMap[cellNumber.y][cellNumber.x];

            //бонусы
            if (isDestroyedBonus(g, cellNumber, endPart))
            {
                break;
            }

            //бомбы
            if (isDestroyedBomb(g, cellNumber))
            {
                break;
            }

            //блок
            if (*cell == '#')
            {
                break;
            }

            //стена
            if (*cell == 's')
            {
                g.lvl->walls.push_back(ExplosionWall(cellNumber, g.lvl->textureField));
                *cell = '_';
                break;
            }

            //дверь
            if (*cell == 'D')
            {
                g.p->kill();
                break;
            }
            else
                *cell = ' ';
            typeExpl = (i == g.p->bombPower) ? endPart : middlePart;
            g.lvl->explosions.push_back(BombExplosion(cellNumber, typeExpl, g.lvl->textureExplosion));
        }
    }
}

bool makePyromancyByBonus(Game &g)
{
    if (g.p->flagForGame == 4)
    {
        g.p->flagForGame = 0;
        if (g.lvl->enemies.size() == 0)
        {
            return false;
        }

        for (int i = 0; i < g.lvl->enemies.size(); i++)
        {
            if (g.lvl->enemies[i].status != LifeCycle::LIVE)
            {
                continue;
            }
            sf::Vector2f coordXY = g.lvl->enemies[i].hitBox.getPosition();
            sf::Vector2i cellNumber = getRelativeCellNumber(coordXY.x, coordXY.y);
            createExplosions(cellNumber, g);
            return true;
        }
        return false;
    }
    return false;
}

void levelKeyReleasedHandle(sf::Keyboard::Key code, Game &g)
{
    if (code == sf::Keyboard::Escape)
    {
        g.setStatus(GameStatus::PAUSE);
    }

    if (g.p->status != LifeCycle::LIVE)
    {
        return;
    }

    if (code == sf::Keyboard::A)
    {
        dropBomb(g);
    }

    if (code == sf::Keyboard::F)
    {
        g.p->flagForGame = 4;
        makePyromancyByBonus(g);
    }
}

void drawBombs(sf::RenderWindow &window, Game &g)
{
    for (int i = 0; i < g.lvl->bombs.size(); i++)
    {
        g.lvl->bombs[i].liveCycle(g.dtime);
        switch (g.lvl->bombs[i].status)
        {
        case LifeCycle::LIVE:
            window.draw(g.lvl->bombs[i].sprite);
            break;
        case LifeCycle::DEATH:
            createExplosions(g.lvl->bombs[i].createCellNumber, g);
            break;
        case LifeCycle::ERASE:
            if (g.lvl->bombs[i].likeBarrier)
            {
                g.lvl->tileMap[g.lvl->bombs[i].createCellNumber.y][g.lvl->bombs[i].createCellNumber.x] = ' ';
            }
            g.lvl->bombs.erase(g.lvl->bombs.cbegin() + i);
            break;
        }
    }
}

void drawExplosions(sf::RenderWindow &window, Game &g)
{
    for (int i = 0; i < g.lvl->explosions.size(); i++)
    {
        g.lvl->explosions[i].liveCycle(g.dtime);
        switch (g.lvl->explosions[i].status)
        {
        case LifeCycle::LIVE:
            window.draw(g.lvl->explosions[i].sprite);
            break;
        case LifeCycle::ERASE:
            g.lvl->explosions.erase(g.lvl->explosions.cbegin() + i);
            break;
        }
    }
}

void drawEnemies(sf::RenderWindow &window, Game &g)
{
    for (int i = 0; i < g.lvl->enemies.size(); i++)
    {
        g.lvl->enemies[i].liveCycle(g.dtime);
        switch (g.lvl->enemies[i].status)
        {
        case LifeCycle::LIVE:
        case LifeCycle::DEATH:
            window.draw(g.lvl->enemies[i].sprite);
            break;
        case LifeCycle::ERASE:
            g.lvl->enemies.erase(g.lvl->enemies.cbegin() + i);
            break;
        }
    }
}

void drawBonuses(sf::RenderWindow &window, Game &g)
{
    for (int i = 0; i < g.lvl->bonuses.size(); i++)
    {
        g.lvl->bonuses[i].liveCycle(0);
        switch (g.lvl->bonuses[i].status)
        {
        case LifeCycle::LIVE:
        case LifeCycle::DEATH:
            window.draw(g.lvl->bonuses[i].sprite);
            break;
        case LifeCycle::ERASE:
            g.lvl->bonuses.erase(g.lvl->bonuses.cbegin() + i);
            break;
        }
    }
}

void drawExplosionWalls(sf::RenderWindow &window, Game &g)
{
    for (int i = 0; i < g.lvl->walls.size(); i++)
    {
        g.lvl->walls[i].liveCycle(g.dtime);
        switch (g.lvl->walls[i].status)
        {
        case LifeCycle::LIVE:
        case LifeCycle::DEATH:
            window.draw(g.lvl->walls[i].sprite);
            break;
        case LifeCycle::ERASE:
            sf::Vector2i wallCellNumber = g.lvl->walls[i].createCellNumber;
            g.lvl->tileMap[wallCellNumber.y][wallCellNumber.x] = ' ';
            g.lvl->walls.erase(g.lvl->walls.cbegin() + i);

            if (!(g.lvl->maybeCreateDoor(wallCellNumber)))
            {
                g.lvl->maybeCreateBonus(wallCellNumber);
            }
            break;
        }
    }
}

void killsAndDeathsCollision(sf::RenderWindow &window, Game &g)
{
    sf::Vector2f xyEnemy, xyCharacter = g.p->hitBox.getPosition();
    float xL, yL, rL;
    for (int i = 0; i < g.lvl->explosions.size(); i++)
    {
        //взрыв и игрок
        xL = std::fabs(xyCharacter.x - g.lvl->explosions[i].coordXY.x);
        yL = std::fabs(xyCharacter.y - g.lvl->explosions[i].coordXY.y);
        rL = sqrt(pow(xL, 2) + pow(yL, 2));
        if ((rL < 22) && (g.p->status == LifeCycle::LIVE)) //чуть поддаемся
        {
            g.p->kill();
        }

        //взрыв и противник
        for (int j = 0; j < g.lvl->enemies.size(); j++)
        {
            if (g.lvl->enemies[j].status != LifeCycle::LIVE)
                continue;

            xyEnemy = g.lvl->enemies[j].hitBox.getPosition();
            xL = std::fabs(xyEnemy.x - g.lvl->explosions[i].coordXY.x);
            yL = std::fabs(xyEnemy.y - g.lvl->explosions[i].coordXY.y);
            rL = sqrt(pow(xL, 2) + pow(yL, 2));
            if (rL < 22) //чуть поддаемся
            {
                g.lvl->enemies[j].kill();
                g.p->rating += g.lvl->enemies[j].rating;
            }
        }
    }

    if (g.p->status != LifeCycle::LIVE)
        return;

    //противник и игрок
    for (int i = 0; i < g.lvl->enemies.size(); i++)
    {
        if (g.lvl->enemies[i].status != LifeCycle::LIVE)
            continue;

        xyEnemy = g.lvl->enemies[i].hitBox.getPosition();
        xL = std::fabs(xyEnemy.x - xyCharacter.x);
        yL = std::fabs(xyEnemy.y - xyCharacter.y);
        rL = sqrt(pow(xL, 2) + pow(yL, 2));
        if (rL < 22) //чуть поддаемся
        {
            g.p->kill();
        }
    }
}

void spawnPenaltyEnemies(Game &g)
{
    int countEnemies = 5, minTypeEnemy = 0, maxTypeEnemy = 7;
    sf::Vector2i spawnEnemiesCellNumber = g.lvl->findSpawnCellNumber();
    for (int i = 0; i < countEnemies; i++)
    {
        g.lvl->enemies.push_back(Enemy(spawnEnemiesCellNumber, getRandNumber(minTypeEnemy, maxTypeEnemy), g.lvl->textureEnemy));
    }
}

void countdown(Game &g)
{
    if (g.lvl->timeRemaind > 0)
    {
        g.lvl->timeRemaind -= g.dtime;
    }
    else if (g.lvl->timeRemaind < 0)
    {
        g.lvl->timeRemaind = 0;
        spawnPenaltyEnemies(g);
    }
}

bool gotoNextLevel(Game &g)
{
    const int LEVEL_MAX_NUMBER = 6;
    //проход через дверь
    if (g.p->flagForGame == 1)
    {
        if (g.lvl->enemies.size() != 0)
        {
            g.p->flagForGame = 0;
        }
        else
        {
            g.level++;
            g.setStatus(GameStatus::FINISH_LEVEL);
            g.initGame();
            return true;
        }
    }
    return false;
}

bool gotoRestartLevel(Game &g)
{
    //в случае смерти
    if (g.p->flagForGame == 2)
    {
        g.setStatus(GameStatus::DIED);
        g.initGame();
        return true;
    }
    return false;
}

void updateBombsBarrier(Game &g)
{
    sf::Vector2f xyCharacter = g.p->hitBox.getPosition();
    float xL, yL, rL;
    for (int i = 0; i < g.lvl->bombs.size(); i++)
    {
        if (g.lvl->bombs[i].likeBarrier)
            continue;

        xL = std::fabs(xyCharacter.x - g.lvl->bombs[i].coordXY.x);
        yL = std::fabs(xyCharacter.y - g.lvl->bombs[i].coordXY.y);
        rL = sqrt(pow(xL, 2) + pow(yL, 2));
        if (rL > CELL_SIDE)
        {
            g.lvl->bombs[i].likeBarrier = true;
            g.lvl->tileMap[g.lvl->bombs[i].createCellNumber.y][g.lvl->bombs[i].createCellNumber.x] = '_';
        }
    }
}

void levelRedrawFrame(sf::RenderWindow &window, Game &g)
{
    if (gotoNextLevel(g))
    {
        return;
    }

    if (gotoRestartLevel(g))
    {
        return;
    }

    makePyromancyByBonus(g);

    updateBombsBarrier(g);

    drawHeader(window, g);
    drawMap(window, g);
    drawBonuses(window, g);
    drawBombs(window, g);
    drawExplosions(window, g);
    drawEnemies(window, g);
    drawPlayer(window, g);
    drawExplosionWalls(window, g);
    killsAndDeathsCollision(window, g);

    countdown(g);
}
