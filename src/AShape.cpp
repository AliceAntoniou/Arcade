/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** Shape
*/

#include "Shape.hpp"

arcade::Shape::Shape(const vec2int &pos, const color_uint8 &color)
    : shapePosition(pos), shapeColor(color){};

void arcade::Shape::setPosition(const vec2int &newPosition)
{
    shapePosition = newPosition;
}

void arcade::Shape::setColor(const color_uint8 &newColor)
{
    shapeColor = newColor;
}

arcade::color_uint8 arcade::Shape::getColor() const { return (shapeColor); }

arcade::vec2int arcade::Shape::getPosition() const { return (shapePosition); }

arcade::Rectangle::Rectangle(const vec2int &pos, const vec2int &newSize,
    const color_uint8 &color, bool filled)
    : Shape(pos, color), isFilled(filled), size(newSize){};

void arcade::Rectangle::setSize(const vec2int &newSize) { size = newSize; }

arcade::vec2int arcade::Rectangle::getSize() const { return (size); }

void arcade::Rectangle::setFillValue(bool newValue) { isFilled = newValue; }

bool arcade::Rectangle::getFillValue() const { return (isFilled); }

arcade::Point::Point(const vec2int &position, const color_uint8 &color)
    : Shape(position, color){};

arcade::Line::Line(const vec2int &positionStart, const vec2int &positionEnd,
    const color_uint8 &color)
    : Shape(positionStart, color), endLinePosition(positionEnd){};

void arcade::Line::setLineEnd(const vec2int &newPosition)
{
    endLinePosition = newPosition;
}

arcade::vec2int arcade::Line::getLineEnd() const { return (endLinePosition); }
