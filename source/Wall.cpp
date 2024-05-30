#include "pong/Wall.hpp"
#include <raylib.h>

using namespace ramboindustries;

Wall::Wall(Rectangle rectangle)
{
    this->rectangle = rectangle;
}

ObjectType Wall::get_object_type() const
{
    return ObjectType::RECTANGLE;
}

VisibleWall::VisibleWall(Rectangle rectamgle)
:
    Wall(rectamgle)
{
}


void VisibleWall::draw()
{
    DrawRectangle(this->rectangle.x, this->rectangle.y, this->rectangle.width, this->rectangle.height, GREEN);
}





