#include <SFML/Graphics.hpp>
#include "common.h"
#include "constants.h"
#include "bonus.h"
#include "explosion.h"
#include "bomb.h"
#include "explosionWall.h"

#include "enemy.h"
#include "commonArrays.h"
#include "character.h"

#include "lvl.h"
#include "game.h"
#include "score.h"

#include "gameStatuses/startGame.h"
#include "gameStatuses/scores.h"
#include "gameStatuses/inputName.h"
#include "gameStatuses/startLevel.h"
#include "gameStatuses/finishLevel.h"
#include "gameStatuses/died.h"
#include "gameStatuses/level.h"
#include "gameStatuses/pause.h"
#include "windows.h"

#include "character.cpp"
#include "enemy.cpp"

void buttonDown(Game &g, sf::RenderWindow &window)
{
    if (window.hasFocus())
        switch (g.getStatus())
        {
        case GameStatus::LEVEL:
            levelKeyPressedHandle(g);
            break;
        }
}

void pollEvents(sf::RenderWindow &window, Game &g)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        //закрытие окна
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased)
        {
            //обработка "отжатия" клавиш
            switch (g.getStatus())
            {
            case GameStatus::START_GAME:
                startGameKeyReleasedHandle(event.key.code, g, window);
                break;
            case GameStatus::SCORES:
                scoresKeyReleasedHandle(event.key.code, g);
                break;
            case GameStatus::INPUT_NAME:
                inputNameKeyReleasedHandle(event.key.code, g);
                break;
            case GameStatus::LEVEL:
                levelKeyReleasedHandle(event.key.code, g);
                break;
            case GameStatus::PAUSE:
                pauseKeyReleasedHandle(event.key.code, g);
                break;
            }
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Game &g)
{
    window.clear();
    switch (g.getStatus())
    {
    case GameStatus::START_GAME:
        startGameRedrawFrame(window, g);
        break;
    case GameStatus::SCORES:
        scoresRedrawFrame(window, g);
        break;
    case GameStatus::INPUT_NAME:
        inputNameRedrawFrame(window, g);
        break;
    case GameStatus::START_LEVEL:
        startLevelRedrawFrame(window, g);
        break;
    case GameStatus::LEVEL:
        levelRedrawFrame(window, g);
        break;
    case GameStatus::PAUSE:
        pauseRedrawFrame(window, g);
        break;
    case GameStatus::FINISH_LEVEL:
        finishLevelRedrawFrame(window, g);
        break;
    case GameStatus::DIED:
        diedRedrawFrame(window, g);
        break;
    }
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = MAP_WIDTH * CELL_SIDE;
    constexpr unsigned WINDOW_HEIGHT = (HEADER + MAP_HEIGHT) * CELL_SIDE;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME, sf::Style::Close);

    Game g;

    while (window.isOpen())
    {
        g.setDtime();

        //обработка событий - закрытие окна, "отжатие" клавиш
        pollEvents(window, g);
        //в зависимости от статуса игры реализуется разный набор кнопок и их действия
        buttonDown(g, window);
        //отрисовка кадра
        redrawFrame(window, g);
    }
    return 0;
}
