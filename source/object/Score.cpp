#include "object/Score.hpp"
#include <raylib.h>

#include <iostream>

using namespace ramboindustries;
using namespace object;

#define FONT_SIZE 30

Score::Score(
    const int x,
    const int y
)
:
    x(x),
    y(y)
{
    value = 0;
}

void Score::render() const
{
    const char* text = TextFormat("%i", this->value);
    DrawText(
        text, 
        this->x, 
        this->y, 
        FONT_SIZE, 
        RED
    );
}

Score& Score::operator+(const int value)
{
    this->value += value;
    return *this;
}

Score& Score::operator+=(const int value)
{
    this->value += value;
    return *this;
}