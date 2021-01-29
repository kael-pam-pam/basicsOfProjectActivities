#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../constants.h"

//обработка клавиш: "Enter" - отмена паузы
void pauseKeyReleasedHandle(sf::Keyboard::Key code, Game &g)
{
    if (code == sf::Keyboard::Escape)
    {
        g.undoStatus();
    }
    if (code == sf::Keyboard::Return)
    {
        g.setStatus(GameStatus::START_GAME);
        g.initGame();
    }
}

void pauseRedrawFrame(sf::RenderWindow &window, Game &g)
{
    sf::Text pauseCaption, helpMessage1, helpMessage2;

    pauseCaption = sf::Text(PAUSE_TEXT_LINES[0], g.gameFont, TITLE_FONT_SIZE);
    pauseCaption.setColor(MENU_FONT_COLOR);
    pauseCaption.setStyle(sf::Text::Bold);
    pauseCaption.setOrigin(pauseCaption.getLocalBounds().width / 2, pauseCaption.getLocalBounds().height / 2);
    pauseCaption.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    helpMessage1 = sf::Text(PAUSE_TEXT_LINES[1], g.gameFont, MENU_FONT_SIZE);
    helpMessage1.setColor(MENU_FONT_COLOR);
    helpMessage1.setOrigin(helpMessage1.getLocalBounds().width / 2, helpMessage1.getLocalBounds().height / 2);
    helpMessage1.setPosition(pauseCaption.getPosition().x, pauseCaption.getPosition().y + TITLE_MARGIN_BOTTOM);

    helpMessage2 = sf::Text(PAUSE_TEXT_LINES[2], g.gameFont, MENU_FONT_SIZE);
    helpMessage2.setColor(MENU_FONT_COLOR);
    helpMessage2.setOrigin(helpMessage2.getLocalBounds().width / 2, helpMessage2.getLocalBounds().height / 2);
    helpMessage2.setPosition(helpMessage1.getPosition().x, helpMessage1.getPosition().y + MENU_MARGIN_TOP);

    window.draw(pauseCaption);
    window.draw(helpMessage1);
    window.draw(helpMessage2);
}