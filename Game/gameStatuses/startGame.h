#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "../constants.h"

//обработка клавиш: "вверх" и "вниз" - движение по меню, "enter" - выбор пункта меню
void startGameKeyReleasedHandle(sf::Keyboard::Key code, Game &g, sf::RenderWindow &window)
{
    if (code == sf::Keyboard::Up)
    {
        g.activeMenuItem = (g.activeMenuItem == static_cast<int>(MenuItems::START)) ? static_cast<int>(MenuItems::EXIT) : (g.activeMenuItem - 1) % 3;
    }
    if (code == sf::Keyboard::Down)
    {
        g.activeMenuItem = (g.activeMenuItem + 1) % 3;
    }
    if (code == sf::Keyboard::Return)
    {
        switch (g.activeMenuItem)
        {
        case static_cast<int>(MenuItems::START):
            g.setStatus(GameStatus::START_LEVEL);
            g.initGame();
            break;
        case static_cast<int>(MenuItems::SCORES):
            g.setStatus(GameStatus::SCORES);
            g.initGame();
            break;
        case static_cast<int>(MenuItems::EXIT):
            window.close();
            break;
        }
    }
}

//отрисовка кадра
void startGameRedrawFrame(sf::RenderWindow &window, Game &g)
{
    sf::Text gameNameCaption;
    std::array<sf::Text, 3> startGameMenu;

    gameNameCaption = sf::Text(GAME_NAME, g.gameFont, TITLE_FONT_SIZE);
    gameNameCaption.setColor(MENU_FONT_COLOR);
    gameNameCaption.setStyle(sf::Text::Bold);
    gameNameCaption.setOrigin(gameNameCaption.getLocalBounds().width / 2, gameNameCaption.getLocalBounds().height / 2);
    gameNameCaption.setPosition(window.getSize().x / 2, window.getSize().y / 3);

    for (int i = 0; i < START_GAME_MENU.size(); i++)
    {
        startGameMenu[i] = sf::Text(START_GAME_MENU[i], g.gameFont, MENU_FONT_SIZE);
        startGameMenu[i].setColor(MENU_FONT_COLOR);
        startGameMenu[i].setStyle(sf::Text::Bold);
        startGameMenu[i].setOrigin(startGameMenu[i].getLocalBounds().width / 2, startGameMenu[i].getLocalBounds().height / 2);
        if (i == 0)
            startGameMenu[i].setPosition(gameNameCaption.getPosition().x, gameNameCaption.getPosition().y + TITLE_MARGIN_BOTTOM);
        else
            startGameMenu[i].setPosition(startGameMenu[i - 1].getPosition().x, startGameMenu[i - 1].getPosition().y + MENU_MARGIN_TOP);
    }
    switch (g.activeMenuItem)
    {
    case static_cast<int>(MenuItems::START):
        startGameMenu[0].setStyle(startGameMenu[0].getStyle() | sf::Text::Underlined);
        break;
    case static_cast<int>(MenuItems::SCORES):
        startGameMenu[1].setStyle(startGameMenu[1].getStyle() | sf::Text::Underlined);
        break;
    case static_cast<int>(MenuItems::EXIT):
        startGameMenu[2].setStyle(startGameMenu[2].getStyle() | sf::Text::Underlined);
        break;
    }

    window.draw(gameNameCaption);
    for (int i = 0; i < startGameMenu.size(); i++)
    {
        window.draw(startGameMenu[i]);
    }
}