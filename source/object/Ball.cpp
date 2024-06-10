#include "object/Ball.hpp"

#include <raymath.h>

using namespace ramboindustries;
using namespace component;
using namespace object;
using namespace shape;

Ball::Ball(
    const Vector2 center, 
    const float radius
)
{
    this->center = center;
    this->radius = radius;    
    this->speed.x = 250;
    this->speed.y = 250;
}

void Ball::update(const float delta_time) 
{
    const Vector2 temp = Vector2Scale(speed, delta_time);
    center = Vector2Add(center, temp);    
}

void Ball::render() const
{
    DrawCircle(center.x, center.y, radius, YELLOW);    
}

void Ball::reverse_x()
{
    this->speed.x = this->speed.x * -1;
}

void Ball::reverse_y()
{
    this->speed.y = this->speed.y * -1;
}

void Ball::recenter()
{
    reverse_x();
    reverse_y();
    center.x = (float) GetScreenWidth() / 2;
    center.y = (float) GetScreenHeight() / 2;
}