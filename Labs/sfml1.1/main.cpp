#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({120, 300}), "Rectangles and circle");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({100, 280});
    shape1.setPosition({10, 10});
    shape1.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape1);

    sf::CircleShape shape2(40);
    shape2.setPosition({20, 20});
    shape2.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(40);
    shape3.setPosition({20, 110});
    shape3.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(shape3);

    sf::CircleShape shape4(40);
    shape4.setPosition({20, 200});
    shape4.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}
