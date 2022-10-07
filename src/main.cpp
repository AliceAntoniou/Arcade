/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** main
*/

#include "Core.hpp"
#include <iostream>

int startArcade(const std::string &lib_filename)
{
    arcade::Status status = arcade::Nothing;
    arcade::Core core;

    try {
        core.setWindow(lib_filename);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 84;
    }
    while (status < arcade::Exit) {
        core.exe();
        core.display();
        status = core.getStatus();
    }
    return 0;
}

int main(int ac, char const *av[])
{
    if (ac != 2)
        return 84;
    return startArcade(av[1]);
}
