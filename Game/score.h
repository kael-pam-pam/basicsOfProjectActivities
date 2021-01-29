#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <fstream> //работа с файлами
#include <regex>   //регулярные выражения (парсим файл)

void Game::loadScores()
{
    const int MAX_SCORES_COUNT = 10;

    std::ifstream fin;
    std::string readedString;
    std::smatch resultSearch;

    const std::regex searchScore(FORMAT_SCORES_FILE);

    scores.clear();
    fin.open(SCORES_PATH);

    int i = 0;
    if (!fin)
    {
        while (i < MAX_SCORES_COUNT)
        {
            scores.push_back({EMPTY_USER_NAME, 0});
            i++;
        }
        return;
    }

    if (i < MAX_SCORES_COUNT)
    {
        while (getline(fin, readedString))
        {
            if (std::regex_match(readedString, resultSearch, searchScore))
            {
                scores.push_back({resultSearch[1], std::stoi(resultSearch[2])});
                i++;
                if (i >= MAX_SCORES_COUNT)
                {
                    break;
                }
            }
        }
    }
    while (i < MAX_SCORES_COUNT)
    {
        scores.push_back({EMPTY_USER_NAME, 0});
        i++;
    }
    fin.close();
}

void Game::addScoreToTOP(ScoreRecord record)
{
    for (int i = 0; i < scores.size(); i++)
    {
        if (scores[i].rating <= record.rating)
        {
            scores.emplace(scores.cbegin() + i, record);
            scores.pop_back();
            return;
        }
    }
}

void Game::saveScores()
{
    std::ofstream fout;
    fout.open(SCORES_PATH, std::ios_base::out | std::ios_base::trunc);
    if (!fout)
    {
        return;
    }
    for (int i = 0; i < scores.size(); i++)
    {
        fout << scores[i].name << " " << scores[i].rating << std::endl;
    }
    fout.close();
}
