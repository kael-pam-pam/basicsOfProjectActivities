#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr float BALL_RADIUS = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Vector2f speed = {50.f, 0.f};

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Ball");
    sf::Clock clock;
    sf::Clock clockForMath;

    sf::CircleShape shape(BALL_RADIUS);
    shape.setPosition({WINDOW_WIDTH / 2 - BALL_RADIUS, 0});
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
        position.x += speed.x * dt;

        if ((position.x + 2 * BALL_RADIUS >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float timeSinceStart = clockForMath.getElapsedTime().asSeconds();
        const float wavePhase = timeSinceStart * float(2 * M_PI);
        const float y = (amplitudeY * std::sin(wavePhase / periodY)) + WINDOW_HEIGHT / 2 - BALL_RADIUS;

        position.y = y;
        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }
}