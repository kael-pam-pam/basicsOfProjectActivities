#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../constants.h"

//обработка клавиш: буквы, "Backspace" и "Enter" - ввод, редактирование и подтверждение псевдонима пользователя
void inputNameKeyReleasedHandle(sf::Keyboard::Key code, Game &g)
{
    const int NAME_MAX_LENGTH = 5;
    if (code == sf::Keyboard::BackSpace)
    {
        if (g.userName.length() > 0)
        {
            g.userName = g.userName.substr(0, g.userName.length() - 1);
        }
    }
    if ((code >= sf::Keyboard::A) && (code <= sf::Keyboard::Z))
    {
        if (g.userName.length() < NAME_MAX_LENGTH)
        {
            g.userName += static_cast<char>('A' + code);
        }
    }
    if (code == sf::Keyboard::Return)
    {
        if (g.userName == "")
        {
            g.userName = EMPTY_USER_NAME;
        }

        g.loadScores();
        g.addScoreToTOP({g.userName, g.p->rating});
        g.saveScores();

        g.setStatus(GameStatus::START_GAME);
        g.initGame();
    }
}

//отрисовка кадра
void inputNameRedrawFrame(sf::RenderWindow &window, Game &g)
{
    sf::Text inputNameCaption, userName;

    inputNameCaption = sf::Text("Input name", g.gameFont, TITLE_FONT_SIZE);
    inputNameCaption.setColor(MENU_FONT_COLOR);
    inputNameCaption.setStyle(sf::Text::Bold);
    inputNameCaption.setOrigin(inputNameCaption.getLocalBounds().width / 2, inputNameCaption.getLocalBounds().height / 2);
    inputNameCaption.setPosition(window.getSize().x / 2, window.getSize().y / 3);

    userName = sf::Text(g.userName, g.gameFont, MENU_FONT_SIZE);
    userName.setColor(MENU_FONT_COLOR);
    userName.setStyle(sf::Text::Bold);
    userName.setOrigin(userName.getLocalBounds().width / 2, userName.getLocalBounds().height / 2);
    userName.setPosition(inputNameCaption.getPosition().x, inputNameCaption.getPosition().y + TITLE_MARGIN_BOTTOM);

    window.draw(inputNameCaption);
    window.draw(userName);
}