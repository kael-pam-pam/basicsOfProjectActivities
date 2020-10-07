#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    const int pixPerSM = 43;

    sf::RenderWindow window(sf::VideoMode({16 * pixPerSM, 15 * pixPerSM}), "House");
    window.clear(sf::Color(242, 228, 229));

    sf::RectangleShape wall;
    wall.setFillColor(sf::Color(0x40, 0x2B, 0x06));
    wall.setSize({11.3 * pixPerSM, 5.9 * pixPerSM});
    wall.setPosition({2.3 * pixPerSM, (14 - 5.9) * pixPerSM});
    window.draw(wall);

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(0x47, 0x10, 0x16));
    roof.setPosition({8 * pixPerSM, (14 - 5.9 - 3) * pixPerSM});
    roof.setPointCount(4);
    roof.setPoint(0, {-3 * pixPerSM, 0});
    roof.setPoint(1, {+3 * pixPerSM, 0});
    roof.setPoint(2, {+(3 + 4) * pixPerSM, 3 * pixPerSM});
    roof.setPoint(3, {-(3 + 4) * pixPerSM, 3 * pixPerSM});
    window.draw(roof);

    sf::RectangleShape door;
    door.setFillColor(sf::Color(15, 7, 8));
    door.setSize({1.8 * pixPerSM, 4.1 * pixPerSM});
    door.setPosition({3.4 * pixPerSM, (14 - 5.9 + 1.8) * pixPerSM});
    window.draw(door);

    sf::RectangleShape pipe1;
    pipe1.setFillColor(sf::Color(44, 47, 54));
    pipe1.setSize({0.8 * pixPerSM, 1.6 * pixPerSM});
    pipe1.setPosition({(8 + 3 - 1.1) * pixPerSM, (14 - 5.9 - 3 - 0.3) * pixPerSM});
    window.draw(pipe1);

    sf::CircleShape smoke1(0.4 * pixPerSM);
    smoke1.setFillColor(sf::Color(151, 152, 156));
    smoke1.setPosition({(8 + 3 - 1.1 - 0.3 + 0.55) * pixPerSM, (14 - 5.9 - 3 - 0.3 - 0.85 - 0.7) * pixPerSM});
    window.draw(smoke1);

    sf::CircleShape smoke2(0.45 * pixPerSM);
    smoke2.setFillColor(sf::Color(151, 152, 156));
    smoke2.setPosition({(8 + 3 - 1.1 - 0.3 + 0.55 + 0.15) * pixPerSM, (14 - 5.9 - 3 - 0.3 - 0.85 - 0.7 - 0.5) * pixPerSM});
    window.draw(smoke2);

    sf::CircleShape smoke3(0.55 * pixPerSM);
    smoke3.setFillColor(sf::Color(151, 152, 156));
    smoke3.setPosition({(8 + 3 - 1.1 - 0.3 + 0.55 + 0.15 + 0.3) * pixPerSM, (14 - 5.9 - 3 - 0.3 - 0.85 - 0.7 - 0.5 - 0.7) * pixPerSM});
    window.draw(smoke3);

    sf::CircleShape smoke4(0.65 * pixPerSM);
    smoke4.setFillColor(sf::Color(151, 152, 156));
    smoke4.setPosition({(8 + 3 - 1.1 - 0.3 + 0.55 + 0.15 + 0.3 + 0.15) * pixPerSM, (14 - 5.9 - 3 - 0.3 - 0.85 - 0.7 - 0.5 - 0.7 - 0.8) * pixPerSM});
    window.draw(smoke4);

    sf::RectangleShape pipe2;
    pipe2.setFillColor(sf::Color(44, 47, 54));
    pipe2.setSize({1.4 * pixPerSM, pixPerSM});
    pipe2.setPosition({(8 + 3 - 1.1 - 0.3) * pixPerSM, (14 - 5.9 - 3 - 0.3 - 0.85) * pixPerSM});
    window.draw(pipe2);

    window.display();

    sf::sleep(sf::seconds(5));
}
