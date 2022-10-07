/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGame.hpp"
#include <array>
#include <time.h>

constexpr int LEVEL_NBR = 6;

namespace arcade
{
    class Nibbler : virtual public IGame {
        public:
            Nibbler();
            ~Nibbler() = default;

            void exec(IWindow &, Events &event);
            Status getStatus(void);
            int getScore() const noexcept final;
            vec2int getSize() const noexcept final;
            void restart() final;

        private:
            enum move { Up, Down, Left, Right };
            enum games { Start, Exit, Menu, Nib, Snake };

            int menu(IWindow &);
            void gameNibbler(IWindow &);
            void gameSnake(IWindow &);
            void drawMap(IWindow &);
            void drawSnake(IWindow &);
            void timeToScore(IWindow &);
            bool moveSnake(const move &, IWindow &);
            move getMove(const std::vector<arcade::Key> &key);
            void readMap(size_t idx);
            void eatFruit();
            void spawnFruit();
            void start(const vec2int &pos, IWindow &window);
            bool die(IWindow &window);

            clock_t game_clock = clock();
            Status windowStatus = Nothing;
            games game = Start;
            move last_move = move::Right;
            size_t level = 1;
            std::array<std::array<bool, 17>, 17> map;
            std::vector<vec2int> snake;
            std::vector<vec2int> fruits;
            color_uint8 wall_color = {255, 0, 0};
            size_t score = 0;
            size_t lives = 2;
            size_t time = 990;
            bool hard_mode = false;
            int mode = 0;
    };
    extern "C"
    {
        std::unique_ptr<IGame> createGame();
    }
}

#endif /* !NIBBLER_HPP_ */
