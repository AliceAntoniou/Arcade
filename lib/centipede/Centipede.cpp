/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Centipede
*/

#include "centipede/Centipede.hpp"
#include <sstream>

arcade::Centipede::Centipede(size_t size)
{
    centipede.resize(size);
    for (size_t i = 0; i < size; i++) {
        centipede[i].x = 13;
        centipede[i].y = 0;
    }
}

arcade::Centipede::Direction arcade::Centipede::invertDirection(
    Direction direction)
{
    if (direction == right)
        return left;
    return right;
}

bool arcade::Centipede::move(const Map &map)
{
    for (size_t i = centipede.size() - 1; i >= 1; i--) {
        centipede[i].x = centipede[i - 1].x;
        centipede[i].y = centipede[i - 1].y;
    }
    switch (direction) {
        case left:
            centipede[0].x--;
            break;
        case right:
            centipede[0].x++;
    }
    if (map.isMushroom(centipede[0]) || centipede[0].x > 26 ||
        centipede[0].x < 1) {
        centipede[0].y++;
        direction = invertDirection(direction);
        switch (direction) {
            case left:
                centipede[0].x--;
                break;
            case right:
                centipede[0].x++;
        }
    }
    if (centipede[0].y == 26) {
        centipede.clear();
        return true;
    }
    return false;
}

bool arcade::Centipede::isCentipede(const vec2int &pos) const
{
    for (size_t i = 0; i < centipede.size(); i++) {
        if (pos.x == centipede[i].x && pos.y == centipede[i].y) {
            return true;
        }
    }
    return false;
}

void arcade::CentipedeGame::restart()
{
    game_clock = clock();
    windowStatus = Nothing;
    centipede_clock = clock();
    state = Start;
    player = {13, 24};
    fire = {13, 24};
    score = 0;
    map = Map();
    live = 2;
    centipede_nbr = 0;
    centipedes = {};
}

arcade::Centipede arcade::Centipede::splitCentipede(const vec2int &pos)
{
    Centipede new_centipede{0};
    std::vector<vec2int> tmp(0, vec2int{0, 0});

    new_centipede.direction = direction;
    if (centipede[0].x == pos.x && centipede[0].y == pos.y) {
        for (size_t i = 0; i < centipede.size(); i++)
            tmp.push_back(centipede[i]);
        centipede.resize(tmp.size() - 1);
        for (size_t i = 1; i < tmp.size(); i++) {
            centipede[i - 1] = tmp[i];
        }
        new_centipede.centipede.resize(0);
        return new_centipede;
    }
    for (size_t i = centipede.size() - 1;
         centipede[i].x != pos.x || centipede[i].y != pos.y; i--) {
        tmp.push_back(centipede[i]);
        centipede.pop_back();
    }
    centipede.pop_back();
    for (int i = tmp.size() - 1; i >= 0; i--) {
        new_centipede.centipede.push_back(tmp[i]);
    }
    return new_centipede;
}

arcade::Map::Map()
{
    for (size_t i = 0; i < 27; i++) {
        map[i].fill(0);
    }
    for (size_t y = 0; y < 20; y++) {
        for (size_t x = 0; x < 27; x++) {
            if (rand() % 7 == 0)
                map[y][x] = 250;
        }
    }
}

bool arcade::Map::hitMushroom(const vec2int &pos)
{
    if (map[pos.y][pos.x] == 0)
        return false;
    map[pos.y][pos.x] -= 50;
    return true;
}

bool arcade::Map::isMushroom(const vec2int &pos) const
{
    if (map[pos.y][pos.x] == 0)
        return false;
    return true;
}

arcade::Status arcade::CentipedeGame::getStatus()
{
    Status status_ = windowStatus;

    if (status_ < Back_to_menu && state == Exit)
        status_ = arcade::Back_to_menu;
    return status_;
}

void arcade::CentipedeGame::drawCentipede(IWindow &window)
{
    for (size_t j = 0; j < centipedes.size(); j++) {
        if (centipedes[j].live()) {
            for (size_t i = 1; i < centipedes[j].get().size(); i++) {
                window.draw(Point{arcade::vec2int{centipedes[j].get()[i].x,
                                      centipedes[j].get()[i].y + 1},
                    arcade::color_uint8{200, 0, 0}});
            }
            window.draw(Point{arcade::vec2int{centipedes[j].get()[0].x,
                                  centipedes[j].get()[0].y + 1},
                arcade::color_uint8{200, 100, 100}});
        }
    }
}

void arcade::CentipedeGame::drawMap(IWindow &window)
{
    for (int y = 0; y < 27; y++) {
        for (int x = 0; x < 27; x++) {
            window.draw(Point{vec2int{x, y + 1},
                color_uint8{
                    map.get()[y][x], map.get()[y][x], map.get()[y][x]}});
        }
    }
}

void arcade::CentipedeGame::drawScore(IWindow &window)
{
    std::stringstream score_txt;
    color_uint8 color{0, 255, 255};

    score_txt << score;

    window.draw(Text{vec2int{0, 0}, score_txt.str(), color});
    for (int i = 0; i < live; i++) {
        window.draw(Point{vec2int{26 - i, 0}, color_uint8{200, 100, 100}});
    }
}

void arcade::CentipedeGame::shoot()
{
    fire.y--;
    if (fire.y < 0 || map.hitMushroom(fire)) {
        fire = player;
        score++;
    }
    for (size_t i = 0; i < centipedes.size(); i++) {
        if (centipedes[i].isCentipede(fire)) {
            score += 10;
            map.addMushroom(fire);
            centipedes.push_back(centipedes[i].splitCentipede(fire));
            fire = player;
            return;
        }
    }
}

arcade::CentipedeGame::move arcade::CentipedeGame::getMove(
    const std::vector<arcade::Key> &keys)
{
    for (int i = keys.size() - 1; i >= 0; i--) {
        switch (keys[i]) {
            case Key::Up:
                return move::Up;
            case Key::Down:
                return move::Down;
            case Key::Left:
                return move::Left;
            case Key::Right:
                return move::Right;
            default:
                break;
        }
    }
    return NoMove;
}

bool arcade::CentipedeGame::movePlayer(const move &move)
{
    switch (move) {
        case move::Up:
            if (player.y - 1 >= 20)
                player.y--;
            break;
        case move::Down:
            if (player.y + 1 <= 26)
                player.y++;
            break;
        case move::Left:
            if (player.x - 1 >= 0)
                player.x--;
            break;
        case move::Right:
            if (player.x + 1 < 27)
                player.x++;
        default:
            break;
    }
    return true;
}

int arcade::CentipedeGame::centipedesNbr()
{
    int nbr;

    for (size_t i = 0; i < centipedes.size(); i++) {
        if (centipedes[i].live())
            nbr++;
    }
    return nbr;
}

void arcade::CentipedeGame::die()
{
    centipedes.clear();
    if (live-- == 0)
        state = Exit;
    centipedes.push_back(Centipede());
    player = {13, 24};
}

void arcade::CentipedeGame::exec(IWindow &window, Events &)
{
    Events event;
    Events info;

    if (state == Start) {
        centipedes.push_back(Centipede());
        srand(game_clock);
        state = Playing;
        window.setSize(vec2int{27, 28});
        window.setTitle("Centipede");
    }
    if ((((float) clock()) - game_clock) / CLOCKS_PER_SEC > 0.03) {
        while (window.pollEvent(event)) {
            info << event;
        }
        movePlayer(getMove(info.key_pressed));
        for (size_t i = 0; i < centipedes.size(); i++) {
            if (centipedes[i].isCentipede(player)) {
                die();
            }
        }
        shoot();
        if (map.isMushroom(player))
            die();
        game_clock = clock();
    }
    if ((((float) clock()) - centipede_clock) / CLOCKS_PER_SEC > 0.15) {
        for (size_t i = 0; i < centipedes.size(); i++) {
            if (centipedes[i].live())
                if (centipedes[i].move(map))
                    score -= 100;
        }
        if (centipedesNbr() == 0) {
            if (centipede_nbr++ == 10) {
                map = Map();
                centipede_nbr = 0;
            }
            centipedes.push_back(Centipede());
        }
        centipede_clock = clock();
    }
    window.draw(Rectangle{vec2int{0, 0}, vec2int{27, 28}, BLACK_COLOR});
    drawMap(window);
    window.draw(
        Text{vec2int{fire.x, fire.y + 1}, "|", color_uint8{200, 200, 0}});
    window.draw(
        Point{vec2int{player.x, player.y + 1}, color_uint8{0, 25, 220}});
    drawCentipede(window);
    drawScore(window);
    window.display();
    windowStatus = window.getStatus();
}

int arcade::CentipedeGame::getScore() const noexcept { return score; }

std::unique_ptr<arcade::IGame> arcade::createGame()
{
    return std::make_unique<CentipedeGame>();
};

arcade::vec2int arcade::CentipedeGame::getSize() const noexcept
{
    return vec2int{27, 28};
}
