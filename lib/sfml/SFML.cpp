/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** arcadeSFML
*/

#include "sfml/SFMLWindow.hpp"
#include <math.h>

constexpr int PIXEL_SIZE = 21;

arcade::SFMLWindow::SFMLWindow() : win(sf::VideoMode(1, 1), "arcade")
{
    font.loadFromFile("assets/font.ttf");
    win.setFramerateLimit(60);
}

arcade::SFMLWindow::~SFMLWindow()
{
    win.close();
};

void arcade::SFMLWindow::setTitle(const std::string &title)
{
    win.setTitle(title);
}

void arcade::SFMLWindow::setSize(const vec2int &size)
{
    win.create(sf::VideoMode{(unsigned int) size.x * PIXEL_SIZE,
                   (unsigned int) size.y * PIXEL_SIZE},
        "uwu");
}

void arcade::SFMLWindow::setFramerate(int framerate) noexcept
{
    win.setFramerateLimit(framerate);
};

arcade::Status arcade::SFMLWindow::getStatus()
{
    Status tmp = status;
    if (!win.isOpen())
        tmp = Exit;
    if (tmp < Exit)
        status = Nothing;
    return tmp;
}

bool arcade::SFMLWindow::pollEvent(arcade::Events &events_arcade)
{
    sf::Event event_sf;

    if (!win.pollEvent(event_sf))
        return false;
    if (event_sf.type == event_sf.KeyPressed) {
        if (event_sf.mouseButton.button == sf::Mouse::Left)
            events_arcade.mouse.left = true;
        if (event_sf.mouseButton.button == sf::Mouse::Right)
            events_arcade.mouse.right = true;
        if (event_sf.mouseButton.button == sf::Mouse::Middle)
            events_arcade.mouse.middle = true;
        for (size_t i = 0; i != sf::Keyboard::KeyCount; i++) {
            if (event_sf.key.code == (sf::Keyboard::Key) i)
                events_arcade.key_pressed.push_back((arcade::Key) i);
        }
    }
    events_arcade.mouse.pos = (vec2int){
        sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y};
    status = events_arcade.getStatus();
    if (event_sf.type == sf::Event::Closed) {
        win.close();
        status = Exit;
    }
    return true;
}

void arcade::SFMLWindow::display() { win.display(); }

void arcade::SFMLWindow::draw(const Line &line)
{
    float size_x = line.getLineEnd().x - line.getPosition().x;
    float size_y = line.getLineEnd().y - line.getPosition().y;
    float x = line.getPosition().x;
    float y = line.getPosition().y;
    Rectangle rect(line.getPosition(), vec2int{(int) size_x, (int) size_y + 1},
        line.getColor(), true);
    Point point(line.getPosition(), line.getColor());

    if (line.getPosition().x == line.getLineEnd().x ||
        line.getPosition().y == line.getLineEnd().y) {
        draw(rect);
        return;
    }
    if (size_x <= size_y) {
        for (int i = 0; i <= size_y; i++) {
            point.setPosition(vec2int{(int) round(x), (int) round(y)});
            draw(point);
            y++;
            x += size_x / size_y;
        }
        return;
    }
    for (int i = 0; i <= size_x; i++) {
        point.setPosition(vec2int{(int) round(x), (int) round(y)});
        draw(point);
        x++;
        y += size_y / size_x;
    }
}

void arcade::SFMLWindow::drawRectangleFill(const Rectangle &rectangle)
{
    sf::RectangleShape rect(sf::Vector2f(rectangle.getSize().x * PIXEL_SIZE,
        rectangle.getSize().y * PIXEL_SIZE));

    rect.setFillColor(sf::Color{rectangle.getColor().r, rectangle.getColor().g,
        rectangle.getColor().b});
    rect.setPosition(rectangle.getPosition().x * PIXEL_SIZE,
        rectangle.getPosition().y * PIXEL_SIZE);
    win.draw(rect);
}

void arcade::SFMLWindow::drawRectangleEmpty(const Rectangle &rectangle)
{
    Rectangle rect(rectangle);

    rect.setSize(vec2int{1, rectangle.getSize().y});
    drawRectangleFill(rect);
    rect.setSize(vec2int{rectangle.getSize().x, 1});
    drawRectangleFill(rect);
    rect.setPosition(vec2int{rectangle.getPosition().x,
        rectangle.getPosition().y + rectangle.getSize().y - 1});
    drawRectangleFill(rect);
    rect.setPosition(
        vec2int{rectangle.getPosition().x + rectangle.getSize().x - 1,
            rectangle.getPosition().y});
    rect.setSize(vec2int{1, rectangle.getSize().y});
    drawRectangleFill(rect);
}

void arcade::SFMLWindow::draw(const Rectangle &rectangle)
{
    switch (rectangle.getFillValue()) {
        case true:
            return drawRectangleFill(rectangle);
        case false:
            return drawRectangleEmpty(rectangle);
    }
}

void arcade::SFMLWindow::draw(const Point &point)
{
    sf::RectangleShape rect(sf::Vector2f{PIXEL_SIZE, PIXEL_SIZE});

    rect.setFillColor(
        sf::Color{point.getColor().r, point.getColor().g, point.getColor().b});
    rect.setPosition(sf::Vector2f{(float) point.getPosition().x * PIXEL_SIZE,
        (float) point.getPosition().y * PIXEL_SIZE});
    win.draw(rect);
}

void arcade::SFMLWindow::draw(const Text &text)
{
    sf::Text txt(text.getString(), font, PIXEL_SIZE * 3);
    txt.setOutlineColor(sf::Color(text.getBackColor().r, text.getBackColor().g, text.getBackColor().b));
    txt.setOutlineThickness(1);

    txt.setPosition(sf::Vector2f{(float) text.getPosition().x * PIXEL_SIZE,
        (float) (text.getPosition().y - 2) * PIXEL_SIZE});
    txt.setFillColor(
        sf::Color{text.getColor().r, text.getColor().g, text.getColor().b});
    win.draw(txt);
}

void arcade::SFMLWindow::clear(void) { win.clear(); }

std::unique_ptr<arcade::IWindow> arcade::createLib()
{
    return std::make_unique<SFMLWindow>();
};