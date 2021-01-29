#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "constants.h"

class Game
{
  private:
    GameStatus currentStatus, oldStatus; //текущий статус и предыдущий статус игры (для возврата из паузы)
    sf::Clock clock;                     //вспомогательный: для высчитывания dtime между кадрами

  public:
    int level; //номер уровня
    std::string userName;

    int activeMenuItem; //номер меню
    sf::Font gameFont;  //шрифт на всю игру (загрузили раз и забыли)

    std::vector<ScoreRecord> scores;

    float dtime = 0;     //время между кадрами
    float sleepTime = 0; //время на зугрузку уровня/приветствие

    Character *p = nullptr;
    Level *lvl = nullptr;

    std::vector<BonusTypes> bonusesForGame; //бонусы на игру

    ~Game()
    {
        delete p;
        delete lvl;
    }
    Game()
    {
        setStatus(GameStatus::START_GAME);
        level = 1;
        activeMenuItem = 0;

        p = new Character();

        gameFont.loadFromFile(FONT_PATH);
        initGame();
    }
    //установка свойств в зависимости от статуса
    void initGame()
    {
        switch (currentStatus)
        {
        case GameStatus::START_GAME:
            activeMenuItem = static_cast<int>(MenuItems::START);
            level = 1;

            p->init(START_USER_BOMBS, START_USER_LIVES,
                    START_USER_BOMB_POWER, 0.1, START_USER_BOMB_SPEED);

            bonusesForGame.clear();
            bonusesForGame = {
                BonusTypes::QUICK_WAIT_TIME,
                BonusTypes::QUICK_WAIT_TIME,
                BonusTypes::INCREASE_POWER_EXPLOSION,
                BonusTypes::INCREASE_POWER_EXPLOSION,
                BonusTypes::INCREASE_POWER_EXPLOSION,
                BonusTypes::ADDITIONAL_BOMB,
                BonusTypes::ADDITIONAL_BOMB,
                BonusTypes::ADDITIONAL_BOMB,
                BonusTypes::ADDITIONAL_BOMB,
                BonusTypes::INCREASE_SPEED,
                BonusTypes::INCREASE_SPEED,
                BonusTypes::INCREASE_SPEED,
                BonusTypes::ADDITIONAL_LIFE,
                BonusTypes::ADDITIONAL_LIFE,
                BonusTypes::REDUCE_POWER_EXPLOSION,
                BonusTypes::PYROMANCY,
                BonusTypes::PYROMANCY,
                BonusTypes::PYROMANCY};
            buffer_bonusesForGame = &bonusesForGame;
            break;
        case GameStatus::SCORES:
            loadScores();
            break;
        case GameStatus::INPUT_NAME:
            userName = "";
            break;
        case GameStatus::FINISH_LEVEL:
            sleepTime = 25e5f;
            clock.restart();
            break;
        case GameStatus::DIED:
            sleepTime = 25e5f;
            clock.restart();
            break;
        case GameStatus::START_LEVEL:
            sleepTime = 15e5f;
            clock.restart();
            break;
        case GameStatus::LEVEL:
            if (lvl != nullptr)
                delete lvl;
            p->setPos({1, 1});
            lvl = new Level(level);
            break;
        }
    }
    GameStatus getStatus() { return currentStatus; }
    void setStatus(GameStatus newStatus)
    {
        oldStatus = currentStatus;
        currentStatus = newStatus;
    }
    void undoStatus() { currentStatus = oldStatus; }
    void setDtime()
    {
        dtime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
    }
    void loadScores();
    void addScoreToTOP(ScoreRecord record);
    void saveScores();
};
