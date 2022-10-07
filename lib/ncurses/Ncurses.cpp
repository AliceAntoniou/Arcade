/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** NcursesWindow
*/

#include "math.h"
#include "ncurses/NcursesWindow.hpp"

constexpr int PIXEL_SIZE = 1;

arcade::NcursesWindow::NcursesWindow()
{
    initscr();
    start_color();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

arcade::NcursesWindow::~NcursesWindow() { endwin(); }

short arcade::NcursesWindow::getColor(const color_uint8 &color)
{
    for (size_t i = 0; i < colors.size(); i++) {
        if (color.r == colors[i].r && color.g == colors[i].g &&
            color.b == colors[i].b) {
            return i;
        }
    }
    colors.push_back(color);
    init_color(colors.size() - 1, (color.r * 1000) / 255,
        (color.g * 1000) / 255, (color.b * 1000) / 255);
    return colors.size() - 1;
}

int arcade::NcursesWindow::getPair(short color_front, short color_back)
{
    for (size_t i = 0; i < pairs.size(); i++) {
        if (color_front == pairs[i][0] && color_back == pairs[i][1]) {
            return i;
        }
    }
    pairs.push_back({color_front, color_back});
    init_pair(pairs.size() - 1, color_front, color_back);
    return pairs.size() - 1;
}

void arcade::NcursesWindow::setSize(const vec2int &size_) { size = size_; }

void arcade::NcursesWindow::setFramerate(int) noexcept {};

void arcade::NcursesWindow::setTitle(const std::string &) {}

constexpr int ncurses_key[arcade::KeyCount] = {'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    27, BUTTON_CTRL, BUTTON_SHIFT, BUTTON_ALT, -1, BUTTON_CTRL, BUTTON_SHIFT,
    BUTTON_ALT, -1, -1, '[', ']', ';', ',', '.', '\'', '/', '\\', '~', '=',
    '-', ' ', '\n', KEY_BACKSPACE, '\t', KEY_NPAGE, KEY_PPAGE, KEY_END,
    KEY_HOME, KEY_PRINT, -1, '+', '-', '*', '/', KEY_LEFT, KEY_RIGHT, KEY_UP,
    KEY_DOWN, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, KEY_F(1), KEY_F(2),
    KEY_F(3), KEY_F(4), KEY_F(5), KEY_F(6), KEY_F(7), KEY_F(8), KEY_F(9),
    KEY_F(10), KEY_F(11), KEY_F(12), KEY_F(13), KEY_F(14), KEY_F(15), -1};

bool arcade::NcursesWindow::pollEvent(Events &events_arcade)
{
    int chr = wgetch(stdscr);
    if (chr == -1)
        return false;
    for (size_t i = 0; i != Key::KeyCount; i++) {
        if (chr == ncurses_key[i])
            events_arcade.key_pressed.push_back((arcade::Key) i);
    }
    status = events_arcade.getStatus();
    return true;
}

void arcade::NcursesWindow::display()
{
    colors.clear();
    pairs.clear();
}

void arcade::NcursesWindow::draw(const Line &line)
{
    float size_x = line.getLineEnd().x - line.getPosition().x;
    float size_y = line.getLineEnd().y - line.getPosition().y;
    float x = line.getPosition().x;
    float y = line.getPosition().y;

    if (line.getPosition().x == line.getLineEnd().x ||
        line.getPosition().y == line.getLineEnd().y) {
        this->drawRectangleFill(Rectangle{line.getPosition(),
            vec2int{line.getLineEnd().x - line.getPosition().x,
                line.getLineEnd().y - line.getPosition().y + 1},
            line.getColor()});
        return;
    }
    if (size_x <= size_y) {
        for (int i = 0; i <= size_y; i++) {
            this->draw(Point{
                vec2int{(int) round(x), (int) round(y)}, line.getColor()});
            y++;
            x += size_x / size_y;
        }
        return;
    }
    for (int i = 0; i <= size_x; i++) {
        this->draw(
            Point{vec2int{(int) round(x), (int) round(y)}, line.getColor()});
        x++;
        y += size_y / size_x;
    }
}

void arcade::NcursesWindow::drawRectangleFill(const Rectangle &rectangle)
{
    int color = getColor(rectangle.getColor());
    int pair = getPair(color, color);

    attron(COLOR_PAIR(pair));
    for (int y = 0; y < rectangle.getSize().y; y++) {
        for (int x = 0; x < rectangle.getSize().x; x++) {
            mvaddch(y + rectangle.getPosition().y,
                x + rectangle.getPosition().x, ' ');
        }
    }
    attroff(COLOR_PAIR(color));
}

void arcade::NcursesWindow::drawRectangleEmpty(const Rectangle &rectangle)
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

void arcade::NcursesWindow::draw(const Rectangle &rectangle)
{
    switch (rectangle.getFillValue()) {
        case true:
            return drawRectangleFill(rectangle);
        case false:
            return drawRectangleEmpty(rectangle);
    }
}

void arcade::NcursesWindow::draw(const Point &point)
{
    short color = getColor(point.getColor());
    int pair = getPair(color, color);

    attron(COLOR_PAIR(pair));
    mvaddch(point.getPosition().y, point.getPosition().x, ' ');
    attroff(COLOR_PAIR(color));
}

void arcade::NcursesWindow::draw(const Text &txt)
{
    short color_front = getColor(txt.getColor());
    short color_back = getColor(txt.getBackColor());
    int pair = getPair(color_front, color_back);

    attron(COLOR_PAIR(pair));
    for (size_t i = 0; i < txt.getString().size(); i++) {
        mvaddch(txt.getPosition().y, txt.getPosition().x + i,
            txt.getString().c_str()[i]);
    }
    attroff(COLOR_PAIR(pair));
}

void arcade::NcursesWindow::clear(void)
{
    int color = getColor(BLACK_COLOR);
    int color_2 = getColor(WHITE_COLOR);
    int pair = getPair(color_2, color);

    attron(COLOR_PAIR(pair));
    erase();
    attroff(COLOR_PAIR(pair));
}

arcade::Status arcade::NcursesWindow::getStatus()
{
    Status tmp = status;
    if (tmp < Exit)
        status = Nothing;
    return tmp;
}

extern "C"
{
    std::unique_ptr<arcade::IWindow> arcade::createLib()
    {
        return std::make_unique<NcursesWindow>();
    };
}