/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Nibbler
*/

#include "nibbler/Nibbler.hpp"
#include <sstream>

static char maps[LEVEL_NBR][18][18] = {
    {".................", ".................", ".................",
        ".................", ".................", ".................",
        ".................", ".................", ".................",
        ".................", ".................", ".................",
        ".................", ".................", ".................",
        ".................", "................."},
    {"..O...O...O...O..", ".XXX.X.XXX.X.XXX.", "OX.XOX.....XOX.XO",
        ".XXX.X.X.X.X.XXX.", ".....XOX.XOX.....", ".XXXXX.X.X.XXXXX.",
        "OX.O.........O.XO", ".X.XXXXXOXXXXX.X.", "...O.........O...",
        ".XXXXX.XXX.XXXXX.", "..O....X.X....O..", ".XXX.X.XXX.X.XXX.",
        ".X.X.X..O..X.X.X.", "OXXXOXOXXXOXOXXXO", ".....X.X.X.X.....",
        "OXXXXX.XXX.XXXXXO", "................."},
    {"..O...O...O...O..", ".XXXXX.X.X.XXXXX.", "O...O..X.X..O...O",
        ".XXX.XXX.XXX.XXX.", ".X.X..O...O..X.X.", ".XXX.XXXXXXX.XXX.",
        "O..O.........O..O", "XX.XXXXXOXXXXX.XX", "...O.........O...",
        ".XXXXXXX.XXXXXXX.", "..O....X.X....O..", ".XXXXX.X.X.XXXXX.",
        ".....X..O..X.....", "OX.XOXOX.X.XOXOXO", ".X.X...X.X...X.X.",
        "OX.XXXXX.XXXXX.XO", "................."},
    {"..O...O...O...O..", ".X.X.X.X.X.X.X.X.", "O...O.......O...O",
        ".X.X.X.X.X.X.X.X.", "......O...O......", ".X.X.X.X.X.X.X.X.",
        "O...O.......O...O", ".X.X.X.XOX.X.X.X.", "....O.......O....",
        ".X.X.X.X.X.X.X.X.", "..O...........O..", ".X.X.X.XOX.X.X.X.",
        ".................", "OX.XOXOX.XOXOX.XO", ".................",
        "OX.X.X.X.X.X.X.XO", "................."},
    {"..O.....O.....O..", ".XXX.XOXXXOX.XXX.", "..O..X..O..X..O..",
        ".XXX.X.XXX.X.XXX.", "OXO.....O.....OXO", ".X.XXXOXXXOXXX.X.",
        "...X...X.X...X...", ".X.X.X.XXX.X.X.X.", "....OX..O..XO....",
        ".X.X.X.XXX.X.X.X.", "...X...X.X...X...", ".X.XXXOXXXOXXX.X.",
        "OX......O......XO", ".XXXOX.XXX.XOXXX.", "..O..X..O..X..O..",
        ".XXX.X.XXX.X.XXX.", "................."},
    {"..O...O...O...O..", ".X.X.X.X.X.X.X.X.", "O...O.......O...O",
        ".X.X.X.X.X.X.X.X.", "......O...O......", ".X.X.X.X.X.X.X.X.",
        "O...O.......O...O", ".X.X.X.XOX.X.X.X.", "....O.......O....",
        ".X.X.X.X.X.X.X.X.", "..O...........O..", ".X.X.X.XOX.X.X.X.",
        ".................", "OX.XOXOX.XOXOX.XO", ".................",
        "OX.X.X.X.X.X.X.XO", "................."}};

arcade::Status arcade::Nibbler::getStatus()
{
    Status status_ = windowStatus;

    if (status_ < Back_to_menu && game == Exit)
        status_ = arcade::Back_to_menu;
    return status_;
}

void arcade::Nibbler::readMap(size_t idx)
{
    for (int y = 0; y < 17; y++) {
        for (int x = 0; x < 17; x++) {
            map[y][x] = maps[idx][y][x] == 'X' ? true : false;
            if (maps[idx][y][x] == 'O')
                fruits.push_back(vec2int{x, y});
        }
    }
}

arcade::Nibbler::Nibbler() {}

void arcade::Nibbler::drawMap(IWindow &window)
{
    window.draw(Rectangle{vec2int{0, 3}, vec2int{19, 19}, wall_color, false});
    for (int y = 0; y < 17; y++) {
        for (int x = 0; x < 17; x++) {
            if (map[y][x])
                window.draw(Point{vec2int{x + 1, y + 4}, wall_color});
        }
    }
    for (size_t i = 0; i < fruits.size(); i++) {
        window.draw(Point{vec2int{fruits[i].x + 1, fruits[i].y + 4},
            color_uint8{0, 255, 0}});
    }
}

static bool isSnake(
    const std::vector<arcade::vec2int> &snake, const arcade::vec2int &pos)
{
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].x == pos.x && snake[i].y == pos.y)
            return true;
    }
    return false;
}

arcade::Nibbler::move arcade::Nibbler::getMove(
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
    return last_move;
}

static void moveSnakeTail(std::vector<arcade::vec2int> &snake)
{
    for (size_t i = snake.size(); i >= 1; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
}

bool arcade::Nibbler::moveSnake(const move &new_move, IWindow &window)
{
    switch (new_move) {
        case move::Up:
            if (last_move == move::Down || snake[0].y - 1 < 0 ||
                map[snake[0].y - 1][snake[0].x]) {
                if (last_move != move::Down && game == Snake) {
                    die(window);
                    return true;
                }
                return false;
            }
            moveSnakeTail(snake);
            snake[0].y--;
            if (isSnake(snake, vec2int{snake[0].x, snake[0].y})) {
                die(window);
                return true;
            }
            last_move = new_move;
            return true;
        case move::Down:
            if (last_move == move::Up || snake[0].y + 1 > 16 ||
                map[snake[0].y + 1][snake[0].x]) {
                if (last_move != move::Up && game == Snake) {
                    die(window);
                    return true;
                }
                return false;
            }
            moveSnakeTail(snake);
            snake[0].y++;
            if (isSnake(snake, vec2int{snake[0].x, snake[0].y})) {
                die(window);
                return true;
            }
            last_move = new_move;
            return true;
        case move::Left:
            if (last_move == move::Right || snake[0].x - 1 < 0 ||
                map[snake[0].y][snake[0].x - 1]) {
                if (last_move != move::Right && game == Snake) {
                    die(window);
                    return true;
                }
                return false;
            }
            moveSnakeTail(snake);
            snake[0].x--;
            if (isSnake(snake, vec2int{snake[0].x, snake[0].y})) {
                die(window);
                return true;
            }
            last_move = new_move;
            return true;
        case move::Right:
            if (last_move == move::Left || snake[0].x + 1 > 16 ||
                map[snake[0].y][snake[0].x + 1]) {
                if (last_move != move::Left && game == Snake) {
                    die(window);
                    return true;
                }
                return false;
            }
            moveSnakeTail(snake);
            snake[0].x++;
            if (isSnake(snake, vec2int{snake[0].x, snake[0].y})) {
                die(window);
                return true;
            }
            last_move = new_move;
    }
    return true;
}

void arcade::Nibbler::spawnFruit()
{
    vec2int vec;

    do {
        vec = {rand() % 17, rand() % 17};
    } while (isSnake(snake, vec));
    fruits.push_back(vec);
}

void arcade::Nibbler::eatFruit()
{
    for (std::vector<arcade::vec2int>::iterator i = fruits.begin();
         i != fruits.end(); i++) {
        if (i->x == snake[0].x && i->y == snake[0].y) {
            fruits.erase(i);
            score += 10 * (level + 1);
            for (size_t i = 0; i < (level + 2) / 2; i++) {
                snake.push_back(snake[snake.size() - 1]);
            }
            if (game == Snake)
                spawnFruit();
            return;
        }
    }
}

void arcade::Nibbler::start(const vec2int &pos, IWindow &window)
{
    snake.clear();
    window.draw(Rectangle{vec2int{0, 3}, vec2int{19, 20}, BLACK_COLOR});
    for (int i = 4; i >= 0; i--) {
        snake.push_back(vec2int{pos.x + i, pos.y});
        while ((((float) clock()) - game_clock) / CLOCKS_PER_SEC < 0.4)
            ;
        drawSnake(window);
        window.display();
        game_clock = clock();
    }
    time = 990;
    last_move = Right;
}

bool arcade::Nibbler::die(IWindow &window)
{
    for (int i = snake.size() - 1; i >= 0; i--) {
        window.draw(
            Rectangle{vec2int{0, 3}, vec2int{19, 20}, color_uint8{0, 0, 0}});
        while ((((float) clock()) - game_clock) / CLOCKS_PER_SEC <
            1.0 / snake.size())
            ;
        snake.pop_back();
        drawSnake(window);
        window.display();
        game_clock = clock();
    }
    if (!lives) {
        game = Menu;
        fruits.clear();
        return true;
    }
    lives--;
    start(vec2int{5, 16}, window);
    return false;
}

void arcade::Nibbler::drawSnake(IWindow &window)
{
    for (size_t i = 1; i < snake.size(); i++) {
        window.draw(Point{arcade::vec2int{snake[i].x + 1, snake[i].y + 4},
            arcade::color_uint8{200, 0, 0}});
    }
    window.draw(Point{arcade::vec2int{snake[0].x + 1, snake[0].y + 4},
        arcade::color_uint8{200, 100, 100}});
}

void arcade::Nibbler::timeToScore(IWindow &window)
{
    std::stringstream score_str;
    std::stringstream time_str;
    std::stringstream lives_str;

    lives_str << lives;
    while (time != 0) {
        while ((((float) clock()) - game_clock) / CLOCKS_PER_SEC < 8.0 / time)
            ;
        window.clear();
        drawSnake(window);
        if (time >= 10) {
            score += 10;
            time -= 10;
        } else {
            score += time;
            time = 0;
        }
        score_str << score;
        window.draw(Text{vec2int{0, 0}, "SCORE:", WHITE_COLOR});
        window.draw(Text{vec2int{0, 2}, score_str.str(), WHITE_COLOR});
        time_str << time;
        window.draw(Text{vec2int{12, 2}, "TIME", WHITE_COLOR});
        window.draw(Text{vec2int{16, 2}, time_str.str(), WHITE_COLOR});
        window.draw(Text{vec2int{14, 0}, "LEFT", WHITE_COLOR});
        window.draw(Text{vec2int{18, 0}, lives_str.str(), WHITE_COLOR});
        window.display();
        score_str.str("");
        score_str.clear();
        time_str.str("");
        time_str.clear();
        game_clock = clock();
    }
}

void arcade::Nibbler::gameNibbler(IWindow &window)
{
    move new_move;
    std::stringstream score_str;
    std::stringstream time_str;
    std::stringstream lives_str;
    Events info;

    if (!fruits.size()) {
        if (++level == LEVEL_NBR) {
            game = Menu;
            return;
        }
        timeToScore(window);
        readMap(level);
        start(vec2int{5, 16}, window);
    }
    window.clear();
    drawMap(window);
    if ((((float) clock()) - game_clock) / CLOCKS_PER_SEC > 0.15) {
        while (window.pollEvent(info))
            ;
        new_move = getMove(info.key_pressed);
        if (!moveSnake(new_move, window)) {
            moveSnake(last_move, window);
        }
        if (time-- == 0 && die(window))
            return;
        eatFruit();
        game_clock = clock();
    }
    drawSnake(window);
    score_str << score;
    window.draw(Text{vec2int{0, 0}, "SCORE:", WHITE_COLOR});
    window.draw(Text{vec2int{0, 2}, score_str.str(), WHITE_COLOR});
    time_str << time;
    window.draw(Text{vec2int{12, 2}, "TIME", WHITE_COLOR});
    window.draw(Text{vec2int{16, 2}, time_str.str(), WHITE_COLOR});
    lives_str << lives;
    window.draw(Text{vec2int{14, 0}, "LEFT", WHITE_COLOR});
    window.draw(Text{vec2int{18, 0}, lives_str.str(), WHITE_COLOR});
    window.display();
}

void arcade::Nibbler::gameSnake(IWindow &window)
{
    move new_move;
    std::stringstream score_str;
    Events info;

    window.clear();
    drawMap(window);
    if ((((float) clock()) - game_clock) / CLOCKS_PER_SEC > 0.15) {
        while (window.pollEvent(info))
            ;
        new_move = getMove(info.key_pressed);
        moveSnake(new_move, window);
        eatFruit();
        game_clock = clock();
    }
    score_str << score;
    for (size_t i = 0; i < fruits.size(); i++) {
        window.draw(Point{vec2int{fruits[i].x + 1, fruits[i].y + 4},
            color_uint8{0, 255, 0}});
    }
    drawSnake(window);
    window.draw(Text{vec2int{0, 0}, "SCORE:", WHITE_COLOR});
    window.draw(Text{vec2int{0, 2}, score_str.str(), WHITE_COLOR});
    window.display();
}

int arcade::Nibbler::menu(IWindow &window)
{
    Events info;

    if ((((float) clock()) - game_clock) / CLOCKS_PER_SEC > 0.1) {
        while (window.pollEvent(info))
            ;
        last_move = getMove(info.key_pressed);
        switch (last_move) {
            case move::Down:
                last_move = move::Right;
                if (mode != 4)
                    mode += 2;
                break;
            case move::Up:
                last_move = move::Right;
                if (mode != 0)
                    mode -= 2;
                break;
            default:
                break;
                for (size_t i = 0; i < info.key_pressed.size(); i++) {
                    printf("%d, ", info.key_pressed[i]);
                }
                printf("\n");
        }
        if (info.isPressed(Key::Enter)) {
            return mode / 2;
        }
        game_clock = clock();
    }
    window.clear();
    window.draw(Text{vec2int{5, 8 + mode}, ">", color_uint8{100, 100, 255}});
    window.draw(Text{vec2int{7, 8}, "Nibbler", color_uint8{100, 100, 255}});
    window.draw(Text{vec2int{7, 10}, "Snake", color_uint8{100, 100, 255}});
    window.draw(Text{vec2int{7, 12}, "Exit", color_uint8{100, 100, 255}});
    window.display();
    windowStatus = window.getStatus();
    return -1;
}

int arcade::Nibbler::getScore() const noexcept { return score; }

void arcade::Nibbler::restart()
{
    game_clock = clock();
    windowStatus = Nothing;
    game = Start;
    last_move = move::Right;
    level = 1;
    map = {};
    snake = {};
    fruits = {};
    wall_color = {255, 0, 0};
    score = 0;
    lives = 2;
    time = 990;
    hard_mode = false;
    mode = 0;
}

void arcade::Nibbler::exec(IWindow &window, Events &)
{
    if (game == Start) {
        window.setSize(vec2int{19, 22});
        window.setTitle("Nibbler");
        game = Menu;
    }
    if (game == Menu) {
        switch (menu(window)) {
            case 2:
                game = Exit;
                return;
            case 0:
                readMap(1);
                start(vec2int{5, 16}, window);
                game = Nib;
                lives = 2;
                score = 0;
                break;
            case 1:
                readMap(0);
                start(vec2int{5, 7}, window);
                game = Snake;
                spawnFruit();
                spawnFruit();
                lives = 0;
                score = 0;
                break;
            default:
                return;
        }
    }
    if (game == Nib)
        gameNibbler(window);
    if (game == Snake)
        gameSnake(window);
    windowStatus = window.getStatus();
}

extern "C"
{
    std::unique_ptr<arcade::IGame> arcade::createGame()
    {
        return std::make_unique<Nibbler>();
    };
}

arcade::vec2int arcade::Nibbler::getSize() const noexcept
{
    return vec2int{19, 22};
}