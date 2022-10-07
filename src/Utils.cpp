/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Utils
*/

#include "Utils.hpp"

bool arcade::Events::isPressed(const Key key) const noexcept
{
    for (std::size_t i = 0; i < key_pressed.size(); i++)
        if (key_pressed[i] == key)
            return (true);
    return (false);
};

arcade::Status arcade::Events::getStatus() const noexcept
{
    if (isPressed(Escape))
        return Exit;
    if (isPressed(Backspace))
        return Back_to_menu;
    if (isPressed(R))
        return Restart;
    if (isPressed(P))
        return Next_game;
    if (isPressed(O))
        return Previous_game;
    if (isPressed(M))
        return Next_graphics;
    if (isPressed(L))
        return Previous_graphics;
    return Nothing;
}

arcade::Events &arcade::Events::operator<<(const Events &event)
{
    mouse.left |= event.mouse.left;
    mouse.right |= event.mouse.right;
    mouse.middle |= event.mouse.middle;
    mouse.pos = event.mouse.pos;

    for (std::size_t i = 0; i < event.key_pressed.size(); i++) {
        key_pressed.push_back(event.key_pressed[i]);
    }
    return *this;
}