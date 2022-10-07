/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <string>

namespace arcade
{
    class Error : public std::exception {
        public:
            Error(std::string const &message) throw();
            virtual char const *what() const throw();

        protected:
            std::string _message;
    };
    class LibError : public arcade::Error {
        public:
            LibError(std::string const &message) throw();
    };
    class dlError : public arcade::Error {
        public:
            dlError() throw();
    };
}

#endif /* !ERRORS_HPP_ */