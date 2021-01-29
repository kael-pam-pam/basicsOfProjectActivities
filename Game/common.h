#pragma once

const int CELL_SIDE = 32; //высота одной плитки карты (в пикселях)
const int HEADER = 2;     //верхняя панель (в клетках)

//направление движения
enum class DirectionMove
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

//жизненный цикл
enum class LifeCycle
{
    LIVE,
    DEATH,
    ERASE
};

enum class ExplosionPart
{
    CENTER,
    MIDDLE_HORISONTAL,
    LEFT_END_HORISONTAL,
    RIGHT_END_HORISONTAL,
    MIDDLE_VERTICAL,
    UP_END_VERTICAL,
    DOWN_END_VERTICAL
};

//типы бонусов
enum class BonusTypes
{
    QUICK_WAIT_TIME,
    INCREASE_POWER_EXPLOSION,
    ADDITIONAL_BOMB,
    REDUCE_POWER_EXPLOSION,
    INCREASE_SPEED,
    ADDITIONAL_LIFE,
    PYROMANCY,
};

//очки игроков
struct ScoreRecord
{
    std::string name;
    int rating;
};

//родитель для последующих классов
//не использовал virtual override, т.к. ругалось "undefined reference to `vtable for SimpleObject'"
class SimpleObject
{
    sf::Texture *texture;

  public:
    sf::Vector2i createCellNumber; //внутри игрового поля (относительно)
    sf::Vector2i coordXY;          //внутри окна (абсолытно)
    LifeCycle status;
    sf::Sprite sprite;
    float currentFrame;

    SimpleObject(sf::Vector2i cellNum, sf::Texture &t)
    {
        texture = &t;
        createCellNumber = cellNum;
        status = LifeCycle::LIVE;
        currentFrame = 0;
        sprite.setScale(2, 2);
        sprite.setTexture(*texture);
        coordXY = {createCellNumber.x * CELL_SIDE, (createCellNumber.y + HEADER) * CELL_SIDE};
        sprite.setPosition(coordXY.x, coordXY.y);
    }
    void liveCycle(float dtime);
    void animation();
    void kill();
};

class ActiveObject : public SimpleObject
{
    sf::Vector2i leftStartSpriteCoord, //начало спрайтов: движение влево
        rightStartSpriteCoord,         //начало спрайтов: движение вправо
        upStartSpriteCoord,            //начало спрайтов: вверх
        DownStartSpriteCoord,          //начало спрайтов: вниз
        deathStartSpriteCoord;         //начало спрайтов: смерть

    float dx, dy, speed;   //смещение по осям и скорость
    DirectionMove dirMove; //направление движения
    float deathTime;       //время анимации смерти
    int rating;            //очки

    ActiveObject(sf::Vector2i cellNum, sf::Texture &t) : SimpleObject(cellNum, t){};
    void liveCycle(float dtime);
    void animation();
    void interaction();
    void kill();
};