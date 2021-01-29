#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../constants.h"

//обработка клавиш: "Enter" - вернуться в меню
void scoresKeyReleasedHandle(sf::Keyboard::Key code, Game &g)
{
    //кнопка
    if (code == sf::Keyboard::Return)
    {
        g.setStatus(GameStatus::START_GAME);
        g.initGame();
    }
}

//отрисовка кадра
void scoresRedrawFrame(sf::RenderWindow &window, Game &g)
{
    sf::Text scoresCaption;
    std::array<sf::Text, 10> scoresText;

    scoresCaption = sf::Text("Scores:", g.gameFont, TITLE_FONT_SIZE);
    scoresCaption.setColor(MENU_FONT_COLOR);
    scoresCaption.setStyle(sf::Text::Bold);
    scoresCaption.setOrigin(scoresCaption.getLocalBounds().width / 2, scoresCaption.getLocalBounds().height / 2);
    scoresCaption.setPosition(window.getSize().x / 2, window.getSize().y / 8);

    for (int i = 0; i < g.scores.size(); i++)
    {
        std::string top = ((std::to_string(i + 1) + ".  ").substr(0, 4) + (g.scores[i].name).substr(0, 5) + "          ").substr(0, 14) + (std::to_string(g.scores[i].rating)).substr(0, 6);
        scoresText[i] = sf::Text(top, g.gameFont, MENU_FONT_SIZE);
        scoresText[i].setColor(MENU_FONT_COLOR);
        scoresText[i].setStyle(sf::Text::Bold);
        if (i == 0)
            scoresText[i].setPosition(scoresCaption.getGlobalBounds().left, scoresCaption.getGlobalBounds().top + TITLE_MARGIN_BOTTOM);
        else
            scoresText[i].setPosition(scoresText[i - 1].getPosition().x, scoresText[i - 1].getPosition().y + MENU_MARGIN_TOP);
    }

    window.draw(scoresCaption);
    for (int i = 0; i < scoresText.size(); i++)
    {
        window.draw(scoresText[i]);
    }
}