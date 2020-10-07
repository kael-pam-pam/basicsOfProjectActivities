#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({420, 170}), "FIO");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({100, 25});
    shape1.setPosition({10, 10});
    shape1.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({25, 150});
    shape2.setPosition({48, 10});
    shape2.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({100, 25});
    shape3.setPosition({160, 10});
    shape3.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({25, 150});
    shape4.setPosition({160, 10});
    shape4.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({25, 150});
    shape5.setPosition({235, 10});
    shape5.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({25, 150});
    shape6.setPosition({310, 10});
    shape6.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({100, 25});
    shape7.setPosition({310, 10});
    shape7.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({100, 25});
    shape8.setPosition({310, 72});
    shape8.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape8);

    sf::RectangleShape shape9;
    shape9.setSize({25, 150});
    shape9.setPosition({385, 10});
    shape9.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape9);

    sf::RectangleShape shape10;
    shape10.setSize({100, 25});
    shape10.setPosition({310, 137});
    shape10.setFillColor(sf::Color(0x2F, 0x2F, 0x2F));
    window.draw(shape10);

    window.display();

    sf::sleep(sf::seconds(5));
}
