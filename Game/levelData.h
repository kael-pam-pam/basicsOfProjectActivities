#pragma once
//заголовочные файлы представлены чтобы показать зависимости
#include <SFML/Graphics.hpp>
#include "constants.h"

const int LAST_LEVEL_NUMBER = 6;

struct EnemyStructInput
{
    sf::Vector2i cellNumber;
    int type;
};

sf::String lvl1_TileMap[MAP_HEIGHT] = {
    "###############################",
    "#  ss   s sss    sss   s      #",
    "# #s# # # #s# # # #s# # # # # #",
    "#      s             s    ss  #",
    "# # # # #s# # #s# # # # # #s# #",
    "#s   ss sss   ss       ss  s  #",
    "#s# # # #s# # #s# # # # # # # #",
    "#     s                       #",
    "# # # # #s# # # # # # #s# # # #",
    "#        sss          ss      #",
    "#s# #s# # # # # #s# # # # # # #",
    "#s   ss  sss    sss        s  #",
    "# # #s# #s#s# # #s# # # #s#s# #",
    "#             ss       sss    #",
    "# # # # # # # #s# # # #s# # # #",
    "#        ss       ss         s#",
    "#s# #s# #s# # # # #s# # #s# # #",
    "#ss      s    s    ss   sss   #",
    "###############################",
};

std::vector<EnemyStructInput> lvl1_EnemyMap = {{{1, 15}, 0}, {{7, 1}, 0}, {{13, 15}, 0}, {{25, 7}, 0}, {{29, 17}, 0}, {{27, 2}, 0}};

sf::String lvl2_TileMap[MAP_HEIGHT] = {
    "###############################",
    "#      ss     sss     ss      #",
    "# #s# #s# #s# #s# # # #s# # # #",
    "# sss                  ss  ss #",
    "# #s# # # # #s# # #s# # # # # #",
    "#        ss  s     ss         #",
    "# # # # #s# # # # #s# # # # # #",
    "#     s  s       s    s   s ss#",
    "# # # # # # #s# #s# # # # # #s#",
    "#sss        sssss        ss  s#",
    "# #s# # # # # #s# # #s# # # # #",
    "#       ss s   sss  sss       #",
    "# # # # #s# # # #s# #s# # # # #",
    "#                       s     #",
    "# # # #s# # # # # # # # # #s# #",
    "#ss  sss     s            ss  #",
    "#s# #s# # # #s# # #s# # # #s# #",
    "#      s    ss    ss  ss     s#",
    "###############################",
};

std::vector<EnemyStructInput> lvl2_EnemyMap = {{{13, 1}, 0}, {{25, 1}, 1}, {{7, 5}, 0}, {{1, 11}, 0}, {{15, 17}, 1}, {{27, 17}, 1}};

sf::String lvl3_TileMap[MAP_HEIGHT] = {
    "###############################",
    "#  ss   s  ss    ss        ss #",
    "# #s# # # #s# # # # #s# # #s# #",
    "#  s                sss   ss  #",
    "# # # #s# # # #s# # # # # # # #",
    "#s  ss ss  s   s             s#",
    "# # #s#s# # # # # # # # # # # #",
    "#   ss                s ss    #",
    "#s# # # # # #s# # #s# # #s# # #",
    "#sss     s  sss   sss         #",
    "# # #s# # # #s# # #s# # # # #s#",
    "#    ss               ss   sss#",
    "# # # # # # # # # # #s# # # # #",
    "#s      sss    s    ss        #",
    "# # # # #s# # # # # #s# # # # #",
    "# ss                       s  #",
    "# #s# # # # #s# #s# # # # #s# #",
    "#  ss  ss    s  ss    ss  ss  #",
    "###############################",
};

std::vector<EnemyStructInput> lvl3_EnemyMap = {{{5, 3}, 1}, {{10, 7}, 1}, {{3, 11}, 1}, {{15, 15}, 2}, {{22, 1}, 2}, {{29, 13}, 2}};

sf::String lvl4_TileMap[MAP_HEIGHT] = {
    "###############################",
    "#     s   ss    ss    ss    ss#",
    "# # # # # #s# # # # # #s# # # #",
    "#  ss                  s  ss  #",
    "#s#s# #s# # #s# # # # # # #s# #",
    "#     sss    sss ss      s ss #",
    "# # # # # #s# # #s# # # # # # #",
    "#   ss    sss    s            #",
    "# # #s# # #s# # # # #s# #s# # #",
    "#            s      ss  sss  s#",
    "#s# # # # # # # #s# #s# #s# # #",
    "#s    sss    s   ss           #",
    "# # # #s# # #s# #s# #s#s# # # #",
    "#           ss     sss        #",
    "# # # # # # # # # #s# # # # # #",
    "#   s                       ss#",
    "# #s#s# #s# # # # # # # #s# # #",
    "#  sss   s    ss    s   ss    #",
    "###############################",
};

std::vector<EnemyStructInput> lvl4_EnemyMap = {{{1, 5}, 2}, {{1, 17}, 2}, {{19, 1}, 3}, {{11, 17}, 3}, {{27, 16}, 3}, {{29, 3}, 4}};

sf::String lvl5_TileMap[MAP_HEIGHT] = {
    "###############################",
    "#    sss     ss    ss         #",
    "# # # #s# # #s# # #s# # # #s# #",
    "#      sss       s        sss #",
    "# # # # #s# # # #s# # # #s#s# #",
    "#            s       ss sss   #",
    "#s# # # # # #s# # # #s# #s# #s#",
    "#ss    s             ss      s#",
    "#s#s# # # # # # #s# # # # # # #",
    "#  ss      s  sssss s         #",
    "# #s# #s# # # #s#s# # # #s# # #",
    "#      s            s       ss#",
    "# # #s# # # # # # # # # # # # #",
    "#  sss     s   s              #",
    "# #s# # # #s# # # #s# #s# # # #",
    "# ss     sss          ss    s #",
    "# #s# # #s# # # # # # #s# # # #",
    "#  ss    ss     ss     ss     #",
    "###############################",
};

std::vector<EnemyStructInput> lvl5_EnemyMap = {{{1, 17}, 4}, {{9, 5}, 4}, {{18, 3}, 5}, {{11, 17}, 5}, {{29, 2}, 6}, {{26, 17}, 6}};

sf::String lvl6_TileMap[MAP_HEIGHT] = {
    "###############################",
    "#  sss      sss    ss  ss     #",
    "# #s# # #s# #s# # # # #s# #s# #",
    "#        ss            s      #",
    "# # #s# #s# # # # #s# # # # #s#",
    "#             ss   s    s  sss#",
    "# #s# # # # # #s# # # # # # # #",
    "#sss    ss           ss       #",
    "#s# # # # # # #s# # #s# # # #s#",
    "#      s      sss           ss#",
    "# #s# #s# # #s#s# #s#s# # # #s#",
    "#                  sss s      #",
    "# # #s# # # #s# # # # #s# # # #",
    "#   sss  s  ss     ss      ss #",
    "# # #s# # # # # # #s# # # # # #",
    "#  s  ss                ss    #",
    "# # # #s# # # #s# #s# # #s# # #",
    "#      s      sss        ss   #",
    "###############################",
};

std::vector<EnemyStructInput> lvl6_EnemyMap = {{{6, 17}, 5}, {{11, 1}, 5}, {{9, 9}, 6}, {{18, 17}, 6}, {{21, 2}, 7}, {{25, 7}, 7}, {{29, 15}, 7}};