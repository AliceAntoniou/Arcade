/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** AText
*/

#include "Text.hpp"

arcade::Text::Text(const vec2int &pos, const std::string_view &txt,
    const color_uint8 &color, const color_uint8 back_color)
    : pos_(pos), txt_(txt), color_(color), back_color_(back_color){};

void arcade::Text::setString(const std::string &txt) noexcept { txt_ = txt; };

std::string arcade::Text::getString() const noexcept { return txt_; };

void arcade::Text::setColor(const color_uint8 &color) noexcept
{
    color_ = color;
};

arcade::color_uint8 arcade::Text::getColor() const noexcept { return color_; };

void arcade::Text::setBackColor(const color_uint8 &back_color) noexcept
{
    back_color_ = back_color;
};

arcade::color_uint8 arcade::Text::getBackColor() const noexcept
{
    return back_color_;
};

void arcade::Text::setPosition(const vec2int &pos) noexcept { pos_ = pos; };

arcade::vec2int arcade::Text::getPosition() const noexcept { return pos_; };