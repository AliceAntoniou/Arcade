/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** core
*/

#pragma once

#include "IGame.hpp"
#include <string>

namespace arcade
{
    class Core : virtual public IGame {
        public:
            Core();
            ~Core();

            void exec(IWindow &, Events &event);
            void exe();
            void setWindow(const std::string &path);
            int getScore() const noexcept final;
            vec2int getSize() const noexcept final;
            void restart() final;

            void display();
            Status getStatus();

        private:
            const std::string getSelectedLib(Events &);
            Status launchGame(Events &);
            void getGraphicLib(const std::string &path);
            void getGameLib(const std::string &path);
            void getNextGraphicLib();
            void getPrevGraphicLib();
            void getNextGameLib();
            void getPrevGameLib();
            void editName();

            int select = 0;
            size_t index = 0;
            size_t graphics_index = 0;
            size_t game_index = 0;
            std::unique_ptr<IWindow> window = nullptr;
            std::unique_ptr<IGame> game = nullptr;
            std::vector<std::string> graphics;
            std::vector<std::string> games;
            std::unique_ptr<void *> graphic_handle = nullptr;
            std::unique_ptr<void *> game_handle = nullptr;
            std::vector<std::vector<int>> scores;
            std::vector<std::string> names;
            size_t name_index = 0;
            bool edit_mode = false;
            bool shift = false;
    };
    extern "C"
    {
        std::unique_ptr<IGame> createGame();
    }
}

std::unique_ptr<arcade::IWindow> &&getGraphicLib(const std::string_view &path);
std::unique_ptr<arcade::IGame> &&getGameLib(const std::string_view &path);
