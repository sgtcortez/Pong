#include "object/VisibleWall.hpp"

using namespace ramboindustries;
using namespace object;

VisibleWall::VisibleWall(const Rectangle rectamgle)
:
    Wall(rectamgle)
{}

void VisibleWall::render() const
{
    DrawRectangle(
        this->rectangle.x, 
        this->rectangle.y, 
        this->rectangle.width, 
        this->rectangle.height, 
        GREEN
    );
}