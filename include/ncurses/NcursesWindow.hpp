/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** arcadeNcurse
*/

#pragma once

#include "IWindow.hpp"
#include <ncurses.h>

namespace arcade
{
    class NcursesWindow : virtual public IWindow {
        public:
            NcursesWindow();
            ~NcursesWindow();

            void display(void);
            void clear(void);
            bool pollEvent(Events &);
            Status getStatus(void);
            void setTitle(const std::string &title);
            void setSize(const vec2int &size);
            void setFramerate(int framerate) noexcept;

            void draw(const Line &);
            void draw(const Point &);
            void draw(const Rectangle &);
            void draw(const Text &);
            void play(const ASound &){};

        private:
            void drawRectangleFill(const Rectangle &);
            void drawRectangleEmpty(const Rectangle &);
            short getColor(const color_uint8 &);
            int getPair(short, short);

            vec2int size = {0, 0};
            std::vector<color_uint8> colors;
            std::vector<std::array<short, 2>> pairs;
    };
    extern "C"
    {
        std::unique_ptr<IWindow> createLib();
    }
} // namespace arcade