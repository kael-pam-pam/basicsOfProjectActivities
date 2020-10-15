#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 300;
    int radius = 100;
    int radius2 = 180;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({600, 600}), "Ellipse",
        sf::Style::Default, settings);

    sf::ConvexShape ellipse;
    ellipse.setPosition({300, 300});
    ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    sf::Clock clock;

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

        const float time = clock.getElapsedTime().asSeconds();
        float ang = float(2 * M_PI * time) / float(200);
        const float x = radius2 * std::cos(ang * 180.f / float(M_PI));
        const float y = radius2 * std::sin(ang * 180.f / float(M_PI));
        const sf::Vector2f offset = {x, y};

        ellipse.setPointCount(pointCount);
        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            sf::Vector2f point = {
                radius * std::sin(angle) * std::sin(6 * angle),
                radius * std::cos(angle) * std::sin(6 * angle)};
            ellipse.setPoint(pointNo, point + offset);
        }

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}