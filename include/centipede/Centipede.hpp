/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Centipede
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include "IGame.hpp"
#include <time.h>

// extern "C"
// {
namespace arcade
{
    class Map {
        public:
            Map();
            ~Map() = default;

            void addMushroom(const vec2int &pos) { map[pos.y][pos.x] = 250; }
            bool isMushroom(const vec2int &) const;
            bool hitMushroom(const vec2int &);
            const std::array<std::array<unsigned char, 28>, 28> &get() const
            {
                return map;
            };

        private:
            std::array<std::array<unsigned char, 28>, 28> map;
    };
    class Centipede {
        public:
            Centipede(size_t size = 12);
            ~Centipede() = default;

            bool move(const Map &map);
            bool isCentipede(const vec2int &) const;
            bool live() { return !centipede.empty(); }
            arcade::Centipede splitCentipede(const vec2int &);
            const std::vector<vec2int> &get() const { return centipede; };

        private:
            enum Direction { left, right };
            Direction invertDirection(Direction);

            std::vector<vec2int> centipede;
            Direction direction = right;
    };
    class CentipedeGame : virtual public IGame {
        public:
            CentipedeGame() = default;
            ~CentipedeGame() = default;

            void exec(IWindow &, Events &event);
            int getScore() const noexcept final;
            void restart() final;
            Status getStatus(void);
            vec2int getSize() const noexcept final;

        private:
            enum move { NoMove, Up, Down, Left, Right };
            enum State { Start, Exit, Playing };

            void drawMap(IWindow &window);
            void drawCentipede(IWindow &window);
            bool movePlayer(const move &move);
            move getMove(const std::vector<Key> &keys);
            void drawScore(IWindow &window);
            int centipedesNbr();
            void shoot();
            void die();

            clock_t game_clock = clock();
            Status windowStatus = Nothing;
            clock_t centipede_clock = clock();
            State state = Start;
            vec2int player{13, 24};
            vec2int fire{13, 24};
            int score = 0;
            Map map;
            int live = 2;
            int centipede_nbr = 0;
            std::vector<Centipede> centipedes;
    };
    extern "C"
    {
        std::unique_ptr<IGame> createGame();
    }
} // namespace arcade
// }

#endif /* !CENTIPEDE_HPP_ */
