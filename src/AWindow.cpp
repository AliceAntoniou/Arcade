/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** IWindow
*/

#include "IWindow.hpp"

arcade::Status arcade::IWindow::getStatus()
{
    Status tmp = status;

    if (status < Exit)
        status = Nothing;
    return tmp;
}
