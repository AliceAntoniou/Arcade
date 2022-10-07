/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Core
*/

#include "Core.hpp"
#include "Errors.hpp"
#include <dlfcn.h>
#include <filesystem>
#include <fstream>
#include <iostream>

void arcade::Core::getGraphicLib(const std::string &path)
{
    std::unique_ptr<IWindow> (*f)();

    if (window != nullptr)
        window.reset();
    if (graphic_handle != nullptr)
        dlclose(*graphic_handle);
    graphic_handle = std::make_unique<void *>(dlopen(path.c_str(), RTLD_LAZY));
    if (!graphic_handle)
        throw dlError();
    f = reinterpret_cast<std::unique_ptr<IWindow> (*)()>(
        dlsym(*graphic_handle, "createLib"));
    if (!f)
        throw dlError();
    window = std::move(f());
    window->setSize(vec2int{60, 50});
}

void arcade::Core::getGameLib(const std::string &path)
{
    std::unique_ptr<IGame> (*f)();

    if (game != nullptr)
        game.reset();
    if (game_handle != nullptr)
        dlclose(*game_handle);
    game_handle = std::make_unique<void *>(dlopen(path.c_str(), RTLD_LAZY));
    f = reinterpret_cast<std::unique_ptr<IGame> (*)()>(
        dlsym(*game_handle, "createGame"));
    if (!f)
        throw dlError();
    game = f();
}

bool isGraphic(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);

    if (!handle) {
        std::cout << dlerror() << std::endl;
        return false;
    }
    if (!dlsym(handle, "createLib")) {
        dlclose(handle);
        return false;
    }
    dlclose(handle);
    return true;
}

bool isGame(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);

    if (!handle) {
        return false;
    }
    if (!dlsym(handle, "createGame")) {
        dlclose(handle);
        return false;
    }
    dlclose(handle);
    return true;
}

arcade::Core::Core()
{
    std::ifstream score_file("assets/scores.txt");
    std::string buf;
    size_t i = 0;

    graphics.clear();
    games.clear();
    for (const auto &entry : std::filesystem::directory_iterator("lib/")) {
        if (entry.path().extension() == ".so") {
            if (isGame(entry.path().generic_string()))
                games.push_back(entry.path()
                                    .filename()
                                    .replace_extension()
                                    .generic_string());
            if (isGraphic(entry.path().generic_string()))
                graphics.push_back(entry.path()
                                       .filename()
                                       .replace_extension()
                                       .generic_string());
        }
    }
    if (!score_file.fail()) {
        while (!std::getline(score_file, buf, ':').fail()) {
            names.push_back(buf);
            scores.push_back(std::vector<int>());
            std::getline(score_file, buf, '\n');
            while (buf.size() != 0) {
                buf = buf.substr(1);
                scores[i].push_back(atoi(buf.c_str()));
                while (buf[0] != ' ' && buf[0] != '\0')
                    buf = buf.substr(1);
            }
            i++;
        }
    }
    if (names.size() == 0 || *(names.end() - 1) != "New Player") {
        scores.push_back(std::vector<int>());
        names.push_back("New Player");
        for (size_t j = 0; j < games.size(); j++)
            scores[i].push_back(0);
    }
}

arcade::Core::~Core()
{
    std::ofstream outfile("assets/scores.txt");
    size_t i = 0;

    for (const auto &name : names) {
        outfile << name << ":";
        for (const auto &score : scores[i]) {
            outfile << ' ' << score;
        }
        outfile << '\n';
        i++;
    }
}

arcade::Status arcade::Core::getStatus() { return window->getStatus(); }

const std::string arcade::Core::getSelectedLib(Events &info)
{
    while (window->pollEvent(info))
        ;
    if (select > 0 && info.isPressed(Left)) {
        select--;
        if ((select == 0 && index > graphics.size() - 1) ||
            (select == 1 && index > games.size() - 1))
            index--;
    }
    if (select < 2 && info.isPressed(Right)) {
        select++;
        if ((select == 0 && index > graphics.size() - 1) ||
            (select == 1 && index > games.size() - 1))
            index--;
    }
    if (info.isPressed(Down)) {
        if ((select == 0 && index < graphics.size() - 1) ||
            (select == 1 && index < games.size() - 1))
            index++;
        if (select == 2 && name_index < names.size() - 1)
            name_index++;
    }
    if (info.isPressed(Up)) {
        if (index > 0 && select != 2)
            index--;
        if (select == 2 && name_index > 0)
            name_index--;
    }
    if (info.isPressed(Enter)) {
        switch (select) {
            case 0:
                graphics_index = index;
                getGraphicLib(std::string{"lib/" + graphics[index] + ".so"});
                break;
            case 1:
                game_index = index;
                return std::string{"lib/" + games[index] + ".so"};
            case 2:
                if (name_index == names.size() - 1) {
                    names.push_back("New Player");
                    scores.resize(names.size());
                    for (size_t i = 0; i < games.size(); i++)
                        scores[name_index + 1].push_back(0);
                }
                names[name_index] = "";
                edit_mode = true;
                break;
            default:
                break;
        }
    }
    return "";
}

void arcade::Core::getNextGraphicLib()
{
    graphics_index++;
    if (graphics_index >= graphics.size())
        graphics_index = 0;
    getGraphicLib("lib/" + graphics[graphics_index] + ".so");
}

void arcade::Core::getPrevGraphicLib()
{
    graphics_index--;
    if (graphics_index + 1 == 0)
        graphics_index = graphics.size() - 1;
    getGraphicLib("lib/" + graphics[graphics_index] + ".so");
}

void arcade::Core::getNextGameLib()
{
    game_index++;
    if (game_index >= games.size())
        game_index = 0;
    getGameLib("lib/" + games[game_index] + ".so");
}

void arcade::Core::getPrevGameLib()
{
    game_index--;
    if (game_index + 1 == 0)
        game_index = games.size() - 1;
    getGameLib("lib/" + games[game_index] + ".so");
}

arcade::Status arcade::Core::launchGame(Events &info)
{
    Status status = Nothing;
    int tmp;

    while (status < arcade::Previous_game) {
        if (status == Next_graphics) {
            getNextGraphicLib();
            window->setSize(game->getSize());
        }
        if (status == Previous_graphics) {
            getPrevGraphicLib();
            window->setSize(game->getSize());
        }
        game->exec(*window, info);
        if ((tmp = game->getScore()) > scores[name_index][game_index])
            scores[name_index][game_index] = tmp;
        window->display();
        status = game->getStatus();
    }
    window->setSize(vec2int{60, 50});
    return status;
};

void arcade::Core::editName()
{
    arcade::Events event;
    arcade::Events info;

    while (window->pollEvent(event))
        info << event;
    if (info.isPressed(LShift) || info.isPressed(RShift))
        shift = !shift;
    for (size_t i = A; i <= Z; i++) {
        if (info.isPressed((Key) i)) {
            names[name_index].push_back(
                static_cast<char>(i + (shift ? 65 : 97)));
        }
    }
    if (info.isPressed(Backspace) && names[name_index].length() > 0)
        names[name_index].pop_back();
    edit_mode = !info.isPressed(Enter);
}

void arcade::Core::exec(IWindow &, Events &)
{
    Status status = Nothing;
    std::string path = "";
    Events info;

    switch (getStatus()) {
        case Next_game:
            getNextGameLib();
            break;
        default:
            break;
    }
    if (edit_mode == true) {
        editName();
    } else if ((path = getSelectedLib(info)) != "" || game != nullptr) {
        getGameLib(path);
        while (status < arcade::Back_to_menu) {
            if (status == Next_game)
                getNextGameLib();
            if (status == Previous_game)
                getPrevGameLib();
            status = launchGame(info);
        }
        game = nullptr;
    }
}

void arcade::Core::exe()
{
    Status status = Nothing;
    std::string path = "";
    Events info;

    switch (getStatus()) {
        case Next_game:
            getNextGameLib();
            break;
        default:
            break;
    }
    if (edit_mode == true) {
        editName();
    } else if ((path = getSelectedLib(info)) != "" || game != nullptr) {
        getGameLib(path);
        while (status < arcade::Back_to_menu) {
            window->setSize(game->getSize());
            if (status == Next_game)
                getNextGameLib();
            if (status == Previous_game)
                getPrevGameLib();
            status = launchGame(info);
        }
        game = nullptr;
    }
}

int arcade::Core::getScore() const noexcept
{
    int score = 0;
    for (const auto &i : scores[name_index]) {
        score += i;
    }
    return score;
}

void arcade::Core::restart() {}

void arcade::Core::setWindow(const std::string &path) { getGraphicLib(path); }

void arcade::Core::display()
{
    std::stringstream score;

    window->clear();
    window->draw(Text{vec2int{1, 1}, "Exit: Escp"});
    window->draw(Text{vec2int{20, 1}, "Restart: R"});
    window->draw(Text{vec2int{1, 3}, "Back to menu: BackSpace"});
    window->draw(Text{vec2int{1, 5}, "Prev graphics: L"});
    window->draw(Text{vec2int{1, 6}, "Next graphics: M"});
    window->draw(Text{vec2int{20, 5}, "Next game: O"});
    window->draw(Text{vec2int{20, 6}, "Next game: P"});
    window->draw(Text{vec2int{1, 9}, "Graphics Libraries:"});
    for (size_t i = 0; i < graphics.size(); i++) {
        window->draw(Text{vec2int{2, 11 + (int) i}, "-" + graphics[i],
            index == i && select == 0 ? BLACK_COLOR : WHITE_COLOR,
            index != i || select != 0 ? BLACK_COLOR : WHITE_COLOR});
    }
    window->draw(Text{vec2int{20, 9}, "Game Libraries:"});
    for (size_t i = 0; i < games.size(); i++) {
        window->draw(Text{vec2int{21, 11 + (int) i}, "-" + games[i],
            index == i && select == 1 ? BLACK_COLOR : WHITE_COLOR,
            index != i || select != 1 ? BLACK_COLOR : WHITE_COLOR});
    }
    window->draw(Text{vec2int{40, 9}, names[name_index],
        edit_mode == false && select == 2 ? BLACK_COLOR : WHITE_COLOR,
        edit_mode == true || select != 2 ? BLACK_COLOR : WHITE_COLOR});
    for (size_t i = 0; i < scores[name_index].size(); i++) {
        score << scores[name_index][i];
        window->draw(Text{vec2int{40, 11 + (int) i}, score.str()});
        score = std::stringstream();
    }
    window->display();
    return;
}

std::unique_ptr<arcade::IGame> arcade::createGame()
{
    return std::make_unique<arcade::Core>();
}

arcade::vec2int arcade::Core::getSize() const noexcept
{
    return vec2int{60, 50};
}
