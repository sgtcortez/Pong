#include "object/Paddle.hpp"

using namespace ramboindustries;
using namespace object;

void Paddle::limit() 
{
    const float y_position_top = this->rectangle.y;
    if (y_position_top < 0)
    {
        this->rectangle.y = 0;
    } 
    else 
    {
        this->rectangle.y = GetScreenHeight() - this->rectangle.height;
    }
}

void Paddle::render() const
{
    DrawRectangle(
        this->rectangle.x, 
        this->rectangle.y, 
        this->rectangle.width, 
        this->rectangle.height, 
        BLACK
    );
}