/*
** EPITECH PROJECT, 2022
** B-OOP-400-BDX-4-1-arcade-solene.lefeu
** File description:
** IWindow
*/

#pragma once

#include "IWindow.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace arcade
{
    class SFMLWindow : public IWindow {
        public:
            SFMLWindow();
            ~SFMLWindow();

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

            sf::RenderWindow win;
            sf::Font font;
    };
    extern "C"
    {
        std::unique_ptr<IWindow> createLib();
    }
} // namespace arcade
