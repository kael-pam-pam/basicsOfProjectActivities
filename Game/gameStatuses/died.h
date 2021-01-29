#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../constants.h"

//отрисовка кадра
void diedRedrawFrame(sf::RenderWindow &window, Game &g)
{
    sf::Text diedMessage, loseMessage;

    diedMessage = sf::Text("YOU DIED", g.gameFont, TITLE_FONT_SIZE);
    diedMessage.setColor(MENU_FONT_COLOR);
    diedMessage.setStyle(sf::Text::Bold);
    diedMessage.setOrigin(diedMessage.getLocalBounds().width / 2, diedMessage.getLocalBounds().height / 2);
    diedMessage.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    window.draw(diedMessage);

    if (g.p->lifeCount <= 0)
    {
        loseMessage = sf::Text("AND LOSE THE GAME...", g.gameFont, MENU_FONT_SIZE);
        loseMessage.setColor(MENU_FONT_COLOR);
        loseMessage.setOrigin(loseMessage.getLocalBounds().width / 2, loseMessage.getLocalBounds().height / 2);
        loseMessage.setPosition(diedMessage.getPosition().x, diedMessage.getPosition().y + TITLE_MARGIN_BOTTOM);
        window.draw(loseMessage);
    }

    g.sleepTime -= g.dtime;
    if (g.sleepTime < 0)
    {
        if (g.p->lifeCount <= 0)
        {
            g.setStatus(GameStatus::INPUT_NAME);
            g.initGame();
            return;
        }

        g.setStatus(GameStatus::START_LEVEL);
        g.initGame();
    }
}