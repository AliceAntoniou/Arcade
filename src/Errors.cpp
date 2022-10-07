/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Error
*/

#include "Errors.hpp"
#include <dlfcn.h>

arcade::Error::Error(std::string const &message) throw() : _message(message) {}

char const *arcade::Error::what() const throw() { return _message.data(); }

arcade::LibError::LibError(std::string const &path) throw()
    : arcade::Error("Library: " + path + " is invalid")
{
}

arcade::dlError::dlError() throw()
    : arcade::Error(
          "Library: Invalid librairy:\n  dlfcn: " + std::string{dlerror()})
{
}