#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

/*
cmake -G "MinGW Makefiles" .
cmake --build .
*/

struct Eyes
{
    sf::Vector2f centerLeft;
    sf::ConvexShape whiteLeft;
    sf::ConvexShape pupilLeft;
    float pupilRotationLeft = 0;

    sf::Vector2f centerRight;
    sf::ConvexShape whiteRight;
    sf::ConvexShape pupilRight;
    float pupilRotationRight = 0;

    sf::Vector2f whiteRadius;
};

sf::Vector2f toEuclidean(sf::Vector2f radius, float angle)
{
    return {
        float(radius.x * cos(angle)),
        float(radius.y * sin(angle))};
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void updateEyesElements(Eyes &eyes, const sf::Vector2f &mousePosition)
{
    const sf::Vector2f pupilMoveRadius = {eyes.whiteRadius.x - 20, eyes.whiteRadius.y - 30};
    const sf::Vector2f posIn = mousePosition;

    const sf::Vector2f offsetLeft = toEuclidean(pupilMoveRadius, eyes.pupilRotationLeft);
    const sf::Vector2f posLeftOut = eyes.centerLeft + offsetLeft;

    const float dLeftOut = sqrt(pow(posLeftOut.x - eyes.centerLeft.x, 2) + pow(posLeftOut.y - eyes.centerLeft.y, 2));
    const float dLeftIn = sqrt(pow(posIn.x - eyes.centerLeft.x, 2) + pow(posIn.y - eyes.centerLeft.y, 2));

    if (dLeftOut > dLeftIn)
    {
        eyes.pupilLeft.setPosition(posIn);
    }
    else
    {
        eyes.pupilLeft.setPosition(posLeftOut);
    }

    const sf::Vector2f offsetRight = toEuclidean(pupilMoveRadius, eyes.pupilRotationRight);
    const sf::Vector2f posRightOut = eyes.centerRight + offsetRight;

    const float dRightOut = sqrt(pow(posRightOut.x - eyes.centerRight.x, 2) + pow(posRightOut.y - eyes.centerRight.y, 2));
    const float dRightIn = sqrt(pow(posIn.x - eyes.centerRight.x, 2) + pow(posIn.y - eyes.centerRight.y, 2));

    if (dRightOut > dRightIn)
    {
        eyes.pupilRight.setPosition(posIn);
    }
    else
    {
        eyes.pupilRight.setPosition(posRightOut);
    }
}

void initEyes(Eyes &eyes)
{
    const int pointCount = 200;
    const sf::Color whiteColor = sf::Color(0xFF, 0xFF, 0xFF);
    eyes.whiteRadius = {50.f, 100.f};

    const sf::Color pupilColor = sf::Color(0x0, 0x0, 0x0);
    const sf::Vector2f pupilEllipseRadius = {10.f, 20.f};

    eyes.centerLeft = {325, 300};
    eyes.whiteLeft.setPosition(eyes.centerLeft);
    eyes.whiteLeft.setFillColor(whiteColor);
    eyes.whiteLeft.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyes.whiteRadius.x * std::sin(angle),
            eyes.whiteRadius.y * std::cos(angle)};
        eyes.whiteLeft.setPoint(pointNo, point);
    }

    eyes.pupilLeft.setFillColor(pupilColor);
    eyes.pupilLeft.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilEllipseRadius.x * std::sin(angle),
            pupilEllipseRadius.y * std::cos(angle)};
        eyes.pupilLeft.setPoint(pointNo, point);
    }

    eyes.centerRight = {475, 300};
    eyes.whiteRight.setPosition(eyes.centerRight);
    eyes.whiteRight.setFillColor(whiteColor);
    eyes.whiteRight.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyes.whiteRadius.x * std::sin(angle),
            eyes.whiteRadius.y * std::cos(angle)};
        eyes.whiteRight.setPoint(pointNo, point);
    }

    eyes.pupilRight.setFillColor(pupilColor);
    eyes.pupilRight.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilEllipseRadius.x * std::sin(angle),
            pupilEllipseRadius.y * std::cos(angle)};
        eyes.pupilRight.setPoint(pointNo, point);
    }
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, Eyes &eyes)
{
    const sf::Vector2f deltaLeft = mousePosition - eyes.centerLeft;
    eyes.pupilRotationLeft = atan2(deltaLeft.y, deltaLeft.x);

    const sf::Vector2f deltaRight = mousePosition - eyes.centerRight;
    eyes.pupilRotationRight = atan2(deltaRight.y, deltaRight.x);

    updateEyesElements(eyes, mousePosition);
}

void redrawFrame(sf::RenderWindow &window, Eyes &eyes)
{
    window.clear();
    window.draw(eyes.whiteLeft);
    window.draw(eyes.pupilLeft);
    window.draw(eyes.whiteRight);
    window.draw(eyes.pupilRight);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pupils of the eyes follows mouse", sf::Style::Default, settings);

    Eyes eyes;
    sf::Vector2f mousePosition;

    initEyes(eyes);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyes);
        redrawFrame(window, eyes);
    }
}