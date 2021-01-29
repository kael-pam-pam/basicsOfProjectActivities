#pragma once

//костыль. Указатели на обьекты, которые необходимы за пределами классов.
sf::String *buffer_tileMap = nullptr;                     //карта
std::vector<BonusTypes> *buffer_bonusesForGame = nullptr; //бонусы, доступные на всю игру
std::vector<Bonus> *buffer_bonuses = nullptr;             //бонусы на карте уровня
