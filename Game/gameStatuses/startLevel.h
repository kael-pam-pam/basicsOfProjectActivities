#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../constants.h"

//отрисовка кадра
void startLevelRedrawFrame(sf::RenderWindow &window, Game &g)
{
    sf::Text level;

    level = sf::Text("LEVEL " + std::to_string(g.level), g.gameFont, TITLE_FONT_SIZE);
    level.setColor(MENU_FONT_COLOR);
    level.setStyle(sf::Text::Bold);
    level.setOrigin(level.getLocalBounds().width / 2, level.getLocalBounds().height / 2);
    level.setPosition(window.getSize().x / 2, window.getSize().y / 3);
    window.draw(level);

    g.sleepTime -= g.dtime;
    if (g.sleepTime < 0)
    {
        g.setStatus(GameStatus::LEVEL);
        g.initGame();
    }
}