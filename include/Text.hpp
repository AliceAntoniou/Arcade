/*
** EPITECH PROJECT, 2022
** B-OOP-400-BDX-4-1-arcade-solene.lefeu
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "Utils.hpp"
#include <string>

namespace arcade
{
    class Text {
        public:
            Text() noexcept = default;
            /**
             * @brief Construct a new Text object
             *
             * @param pos Vector Position
             * @param txt String to be display
             * @param color Color of the string
             * @param back_color Hilight color
             */
            Text(const vec2int &pos, const std::string_view &txt,
                const color_uint8 &color = WHITE_COLOR,
                const color_uint8 back_color = BLACK_COLOR);

            Text(const Text &other) noexcept = default;
            Text(Text &&other) noexcept = default;
            ~Text() noexcept = default;

            Text &operator=(const Text &rhs) noexcept = default;
            Text &operator=(Text &&rhs) noexcept = default;

            /**
             * @brief Set the String
             *
             * @param txt String to be display
             */
            void setString(const std::string &txt) noexcept;
            /**
             * @brief Get the String
             *
             * @return std::string
             */
            std::string getString() const noexcept;
            /**
             * @brief Set the Color
             *
             * @param color Color of the string
             */
            void setColor(const color_uint8 &color) noexcept;
            /**
             * @brief Get the Color
             *
             * @return color_uint8
             */
            color_uint8 getColor() const noexcept;
            /**
             * @brief Set the Back Color object
             *
             * @param back_color Hilight color
             */
            void setBackColor(const color_uint8 &back_color) noexcept;
            /**
             * @brief Get the Hilight Color object
             *
             * @return color_uint8
             */
            color_uint8 getBackColor() const noexcept;
            /**
             * @brief Set the Position
             *
             * @param pos Vector Position
             */
            void setPosition(const vec2int &pos) noexcept;
            /**
             * @brief Get the Position
             *
             * @return vec2int
             */
            vec2int getPosition() const noexcept;

        protected:
            vec2int pos_ = {0, 0};
            std::string txt_ = "";
            color_uint8 color_ = {255, 255, 255};
            color_uint8 back_color_ = {0, 0, 0};
    };
} // namespace arcade

#endif /* !TEXT_HPP_ */