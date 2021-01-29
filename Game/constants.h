#pragma once

//константы
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <random>

const int MAP_HEIGHT = 19;                //высота карты (в клетках)
const int MAP_WIDTH = 31;                 //ширина карты (в клетках)
const sf::String GAME_NAME = "Bomberman"; //заголовок окна (название игры)

//игрок
const std::string EMPTY_USER_NAME = "HERO"; //пустое имя игрока (инициализзация)
const int START_USER_LIVES = 3;             //количество жизней игрока в начале игры
const int START_USER_BOMBS = 1;             //количество бомб игрока в начале игры
const int START_USER_BOMB_POWER = 2;        //сила взрыва бомб игрока в начале игры
const float START_USER_BOMB_SPEED = 3e6f;   //время детонации бомб игрока в начале игры
const int START_USER_SPEED = 1;             //скорость игрока в начале игры

//текст
const std::string FONT_PATH = "fonts/CourierWINCTT Bold.ttf"; //"fonts/Arame-Bold.ttf"; //"fonts/18685.ttf";  //шрифт игры
const int TITLE_FONT_SIZE = 80;                               //размер шрифта заголовка
const int TITLE_MARGIN_BOTTOM = 120;                          //отступ от заголовка
const int MENU_FONT_SIZE = 30;                                //размер шрифта меню
const int MENU_MARGIN_TOP = 40;                               //отступ от пункта меню
const sf::Color MENU_FONT_COLOR = sf::Color::Red;             //цвет шрифта меню

const std::array<std::string, 3> PAUSE_TEXT_LINES = {"Pause", "Press <ESC> to return to the game", "Press <ENTER> to exit to the menu"};
//меню
const std::array<std::string, 3> START_GAME_MENU = {"Start", "Scores", "Exit"}; //пункты главного меню
enum class MenuItems
{
    START,
    SCORES,
    EXIT
};
//топ очков
const std::string SCORES_PATH = "scores/scores";                    //путь к файлу с очками
const std::string FORMAT_SCORES_FILE = "^(\[A-Z]{1,})\\s([0-9]*)$"; //формат записи в файле с очками

const int SPEED_ANIMATION = 1200;

//статусы игры
enum class GameStatus
{
    START_GAME,
    SCORES,
    INPUT_NAME,
    START_LEVEL,
    LEVEL,
    PAUSE,
    FINISH_LEVEL,
    DIED,
};

std::mt19937 genRandNum(time(0)); //для генерации рандомных чисел

//получить номер клетки, в которой находится большая часть персонажа (абсолютный)
sf::Vector2i getAbsoluteCellNumber(float pixX, float pixY)
{
    return {floor((pixX + CELL_SIDE / 2) / CELL_SIDE),
            floor((pixY + CELL_SIDE / 2) / CELL_SIDE)};
}

//получить номер клетки, в которой находится большая часть персонажа (относительно игрового поля)
sf::Vector2i getRelativeCellNumber(float pixX, float pixY)
{
    sf::Vector2i r = getAbsoluteCellNumber(pixX, pixY);
    return {r.x, r.y - HEADER};
}

sf::Vector2f getAbsoluteCoordinate(float cellX, float cellY)
{
    return {cellX * CELL_SIDE, (cellY + HEADER) * CELL_SIDE};
}

bool getSTRONGCellNumber(float pX, float pY, sf::Vector2i &cN)
{
    sf::Vector2i res = {0, 0};
    if (((int)pX % CELL_SIDE == 0) && ((int)pY % CELL_SIDE == 0))
        res = {floor(pX / CELL_SIDE), floor(pY / CELL_SIDE)};
    cN = res;
    return (((int)pX % CELL_SIDE == 0) && ((int)pY % CELL_SIDE == 0));
}

int getRandNumber(int min, int max)
{
    std::uniform_int_distribution<> uid(min, max);
    return uid(genRandNum);
}

int countTypeTileMap(sf::String tm[], char t)
{
    int count = 0;
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (tm[i][j] == t)
                count++;
        }
    return count;
}

bool toCreateBonus(sf::String tm[])
{
    int forGoodLuck = 3;
    int count = countTypeTileMap(tm, 's');
    return (count < (getRandNumber(0, count) + forGoodLuck));
}