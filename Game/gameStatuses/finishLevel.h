#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../constants.h"

void finishLevelRedrawFrame(sf::RenderWindow &window, Game &g)
{
    sf::Text wellDoneMessage, winMessage;

    wellDoneMessage = sf::Text("WELL DONE!", g.gameFont, TITLE_FONT_SIZE);
    wellDoneMessage.setColor(MENU_FONT_COLOR);
    wellDoneMessage.setStyle(sf::Text::Bold);
    wellDoneMessage.setOrigin(wellDoneMessage.getLocalBounds().width / 2, wellDoneMessage.getLocalBounds().height / 2);
    wellDoneMessage.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    window.draw(wellDoneMessage);

    if (g.level > LAST_LEVEL_NUMBER)
    {
        winMessage = sf::Text("YOU WIN THE GAME!", g.gameFont, MENU_FONT_SIZE);
        winMessage.setColor(MENU_FONT_COLOR);
        winMessage.setOrigin(winMessage.getLocalBounds().width / 2, winMessage.getLocalBounds().height / 2);
        winMessage.setPosition(wellDoneMessage.getPosition().x, wellDoneMessage.getPosition().y + TITLE_MARGIN_BOTTOM);
        window.draw(winMessage);
    }

    g.sleepTime -= g.dtime;
    if (g.sleepTime < 0)
    {
        if (g.level > LAST_LEVEL_NUMBER)
        {
            g.setStatus(GameStatus::INPUT_NAME);
            g.initGame();
            return;
        }
        g.setStatus(GameStatus::START_LEVEL);
        g.initGame();
    }
}