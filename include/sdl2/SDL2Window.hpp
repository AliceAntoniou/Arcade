/*
** EPITECH PROJECT, 2022
** B-OOP-400-BDX-4-1-arcade-solene.lefeu
** File description:
** IWindow
*/

#pragma once

#include "IWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace arcade
{
    class SDL2Window : public IWindow {
        public:
            SDL2Window();
            ~SDL2Window();

            void display(void);
            void clear(void);
            bool pollEvent(Events &);
            Status getStatus();
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

            SDL_Window *win;
            SDL_Renderer *renderer;
            TTF_Font *font = TTF_OpenFont("font.ttf", 24);
    };
    extern "C"
    {
        std::unique_ptr<IWindow> createLib();
    }
} // namespace arcade
