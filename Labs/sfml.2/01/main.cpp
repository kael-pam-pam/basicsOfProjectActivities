#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    constexpr float BALL_RADIUS = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Vector2f speed = {50.f, 15.f};

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Ball");
    sf::Clock clock;

    sf::CircleShape shape(BALL_RADIUS);
    shape.setPosition({200, 120});
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        sf::Vector2f position = shape.getPosition();
        position += speed * dt;

        if ((position.x + 2 * BALL_RADIUS >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * BALL_RADIUS >= WINDOW_HEIGHT) && (speed.y > 0))
        {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0))
        {
            speed.y = -speed.y;
        }
        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }
}