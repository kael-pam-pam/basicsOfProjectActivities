#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "levelData.h"

class Level
{
    int number;

    //текстуры
    sf::Image imageField, imageEnemy, imageExplosion; //объект изображения

    void copyTileMap(sf::String from[], sf::String to[])
    {
        for (int i = 0; i < MAP_HEIGHT; i++)
            to[i] = from[i];
    }

  public:
    float timeRemaind;                     //обратный отсчет уровня
    sf::String tileMap[MAP_HEIGHT];        //карта
    sf::Sprite sprite;                     //спрайт
    std::vector<Bonus> bonuses;            //бонусы
    std::vector<Bomb> bombs;               //установленные бомбы
    std::vector<Enemy> enemies;            //враги
    std::vector<BombExplosion> explosions; //взрывы
    std::vector<ExplosionWall> walls;      //анимации взрыва стены
    int bonusRemaind;                      //ограничение на количество выпадаемых бонусов на уровень
    bool isCreatedDoor;                    //создан выход с уровня

    sf::Texture textureField;     //текстура
    sf::Texture textureEnemy;     //текстуры врагов
    sf::Texture textureExplosion; //текстуры бомбы и взрывов

    Level(int n)
    {
        number = n;

        imageField.loadFromFile("images/field.png");           //загрузка картинки
        imageField.createMaskFromColor(sf::Color(56, 135, 0)); //отсекаем зелень
        textureField.loadFromImage(imageField);                //заряжаем текстуру картинкой

        imageEnemy.loadFromFile("images/enemies.png");         //загрузка картинки
        imageEnemy.createMaskFromColor(sf::Color(56, 135, 0)); //отсекаем зелень
        textureEnemy.loadFromImage(imageEnemy);                //заряжаем текстуру картинкой

        imageExplosion.loadFromFile("images/explosion.png");       //загрузка картинки
        imageExplosion.createMaskFromColor(sf::Color(56, 135, 0)); //отсекаем зелень
        textureExplosion.loadFromImage(imageExplosion);            //заряжаем текстуру картинкой

        sprite.setScale(2, 2);           //растягивание текстуры (с 16 px до 32 px)
        sprite.setTexture(textureField); //заливаем текстуру спрайтом

        bonusRemaind = 3; //бонусы не восстанавливаются
        initLevel();
    }
    void initLevel()
    {
        timeRemaind = 200e6f;
        isCreatedDoor = false;
        switch (number)
        {
        case 1:
            copyTileMap(lvl1_TileMap, tileMap);
            for (int i = 0; i < lvl1_EnemyMap.size(); i++)
            {
                enemies.push_back(Enemy(lvl1_EnemyMap[i].cellNumber, lvl1_EnemyMap[i].type, textureEnemy));
            }
            break;
        case 2:
            copyTileMap(lvl2_TileMap, tileMap);
            for (int i = 0; i < lvl2_EnemyMap.size(); i++)
            {
                enemies.push_back(Enemy(lvl2_EnemyMap[i].cellNumber, lvl2_EnemyMap[i].type, textureEnemy));
            }
            break;
        case 3:
            copyTileMap(lvl3_TileMap, tileMap);
            for (int i = 0; i < lvl3_EnemyMap.size(); i++)
            {
                enemies.push_back(Enemy(lvl3_EnemyMap[i].cellNumber, lvl3_EnemyMap[i].type, textureEnemy));
            }
            break;
        case 4:
            copyTileMap(lvl4_TileMap, tileMap);
            for (int i = 0; i < lvl4_EnemyMap.size(); i++)
            {
                enemies.push_back(Enemy(lvl4_EnemyMap[i].cellNumber, lvl4_EnemyMap[i].type, textureEnemy));
            }
            break;
        case 5:
            copyTileMap(lvl5_TileMap, tileMap);
            for (int i = 0; i < lvl5_EnemyMap.size(); i++)
            {
                enemies.push_back(Enemy(lvl5_EnemyMap[i].cellNumber, lvl5_EnemyMap[i].type, textureEnemy));
            }
            break;
        case 6:
            copyTileMap(lvl6_TileMap, tileMap);
            for (int i = 0; i < lvl6_EnemyMap.size(); i++)
            {
                enemies.push_back(Enemy(lvl6_EnemyMap[i].cellNumber, lvl6_EnemyMap[i].type, textureEnemy));
            }
            break;
        }

        buffer_tileMap = tileMap; //для доступа экземплярам других классов
        buffer_bonuses = &bonuses;
    }
    bool maybeCreateDoor(sf::Vector2i cellNumber)
    {
        if (!isCreatedDoor && (toCreateBonus(tileMap)))
        {
            tileMap[cellNumber.y][cellNumber.x] = 'D';
            isCreatedDoor = true;
            return true;
        }
        return false;
    }

    bool maybeCreateBonus(sf::Vector2i cellNumber)
    {
        if ((bonusRemaind > 0) && (toCreateBonus(tileMap)))
        {
            if ((*buffer_bonusesForGame).size() == 0)
                return false;

            int index = getRandNumber(0, (*buffer_bonusesForGame).size() - 1);
            bonuses.push_back(Bonus(cellNumber, (*buffer_bonusesForGame)[index], textureField));
            (*buffer_bonusesForGame).erase((*buffer_bonusesForGame).cbegin() + index);
            bonusRemaind -= 1;
            return true;
        }
        return false;
    }

    bool findDoorCellNumber(sf::Vector2i &cellNumber)
    {
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                if (tileMap[i][j] == 'D')
                {
                    cellNumber = sf::Vector2i{j, i};
                    return true;
                }
            }
        }
        return false;
    }

    bool findRandEmptyCellNumber(sf::Vector2i &cellNumber)
    {
        std::vector<sf::Vector2i> emptyCells;
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                if (tileMap[i][j] == ' ')
                {
                    emptyCells.push_back(sf::Vector2i{j, i});
                }
            }
        }
        if (emptyCells.size() == 0)
        {
            return false;
        }
        else
        {
            cellNumber = emptyCells[getRandNumber(0, emptyCells.size() - 1)];
            return true;
        }
    }

    sf::Vector2i findSpawnCellNumber()
    {
        sf::Vector2i spawnCellNumber = {1, 1};
        if (!findDoorCellNumber(spawnCellNumber))
        {
            findRandEmptyCellNumber(spawnCellNumber);
            tileMap[spawnCellNumber.y][spawnCellNumber.x] = 'D';
            isCreatedDoor = true;
        }
        return spawnCellNumber;
    }
};